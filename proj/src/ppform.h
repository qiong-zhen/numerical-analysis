#ifndef _PPFORM_H_
#define _PPFORM_H_

#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>
#include <limits>
#include <Eigen/Dense>



/*
基类，多项式样条
*/
class pp_form{
protected:
    size_t n; // 节点数
    std::vector<double> knots; // 节点
    std::vector<double> coeffs; // 系数

    // 添加计算多项式值的辅助函数
    double evaluate_polynomial(const std::vector<double>& coef, double x, size_t degree) const {
        double result = 0.0;
        for(size_t i = 0; i <= degree; ++i) {
            result += coef[i] * std::pow(x, i);
        }
        return result;
    }

public:
    pp_form() : n(0){}

    pp_form(const std::vector<double>& nodes){
        if (nodes.size() < 2) {
            throw std::invalid_argument("至少需要两个节点");
        }

        for(size_t i = 0; i < nodes.size() - 1; ++i) {
            if (nodes[i] >= nodes[i + 1]) {
                throw std::invalid_argument("节点必须按升序排列");
            }
        }
        knots = nodes;
        n = knots.size()-1;
    }
    
    //copy constructor
    pp_form(const pp_form& other) : n(other.n), knots(other.knots), coeffs(other.coeffs) {}

    virtual ~pp_form() = default;

    //elevate
    double operator()(const double& x) const {
        if (n==0){
            throw std::runtime_error("未初始化pp_form对象");
        }

        if (x < knots.front() || x > knots.back()) {
            throw std::out_of_range("x超出范围");
        }

        for (size_t i = 0; i < n; ++i) {
            if (x >= knots[i] && x <= knots[i+1]) {
                // 线性样条用2个系数，三次样条用4个系数
                size_t degree = coeffs.size()/n - 1;
                return evaluate_polynomial(
                    std::vector<double>(coeffs.begin() + i*(degree+1), 
                                      coeffs.begin() + (i+1)*(degree+1)), 
                    x, 
                    degree
                );
            }
        }
        return evaluate_polynomial(
            std::vector<double>(coeffs.begin() + (n-1)*(coeffs.size()/n), 
                              coeffs.end()), 
            x, 
            coeffs.size()/n - 1
        );
    }
    
    virtual void compute_Interpolation(const std::vector<double>& x, const std::vector<double>& y) = 0;

    size_t get_n() const {
        return n;
    }

    const std::vector<double>& get_knots() const {
        return knots;
    }
    
    const std::vector<double>& get_coeffs() const {
        return coeffs;
    }


    virtual void print_Expression() const = 0;

protected:
    void validate_input(const std::vector<double>& x, const std::vector<double>& y) const{
        if (x.size() != y.size() || x.size() < 2) {
            throw std::invalid_argument("x和y的尺寸必须相同，且至少包含两个元素");
        }
        
        if(x.size()<2){
            throw std::invalid_argument("至少需要两个节点");
        }
        for(size_t i = 0; i < x.size() - 1; ++i) {
            if (x[i] >= x[i + 1]) {
                throw std::invalid_argument("节点必须按升序排列");
            }
        }
    }

};

class pp_form_linear : public pp_form {
public:
    // 通过节点和函数值构造
    pp_form_linear(const std::vector<double>& x, const std::vector<double>& f) : pp_form(x) {
        validate_input(x, f);
        compute_Interpolation(x, f);
    }

    // 计算插值
    void compute_Interpolation(const std::vector<double>& x, const std::vector<double>& f) override{
        coeffs.clear();
        for(size_t i = 0; i < n; ++i) {
            // 计算线性插值系数
            double dx = x[i+1] - x[i];
            double dy = f[i+1] - f[i];
            double slope = dy / dx;
            double intercept = f[i] - slope * x[i];
            coeffs.push_back(intercept);
            coeffs.push_back(slope);
        }
    }

    // 打印表达式
    void print_Expression() const override {
        for(size_t i = 0; i < n; ++i) {
            std::cout << "区间 [" << knots[i] << ", " << knots[i+1] << "] 上的线性多项式：\n";
            std::cout << coeffs[2*i] << " + " << coeffs[2*i+1] << "x\n";
        }
    }
};

class pp_form_cubic : public pp_form {
private:
    void setup_basic_system(Eigen::MatrixXd& A, Eigen::VectorXd& b, 
                          const std::vector<double>& x, const std::vector<double>& f) {
        // 对于n个区间，我们需要4n个未知系数
        size_t system_size = 4 * n;
        A = Eigen::MatrixXd::Zero(system_size, system_size);
        b = Eigen::VectorXd::Zero(system_size);

        // 1. 插值条件：2n个方程
        for(size_t i = 0; i < n; ++i) {
            double xl = x[i];    // 左端点
            double xr = x[i+1];  // 右端点
            
            // 左端点条件
            A(2*i, 4*i) = 1.0;
            A(2*i, 4*i+1) = xl;
            A(2*i, 4*i+2) = xl*xl;
            A(2*i, 4*i+3) = xl*xl*xl;
            b(2*i) = f[i];
            
            // 右端点条件
            A(2*i+1, 4*i) = 1.0;
            A(2*i+1, 4*i+1) = xr;
            A(2*i+1, 4*i+2) = xr*xr;
            A(2*i+1, 4*i+3) = xr*xr*xr;
            b(2*i+1) = f[i+1];
        }

        // 2. 内部节点处的一阶导数连续性：n-1个方程
        for(size_t i = 0; i < n-1; ++i) {
            double x_joint = x[i+1];
            // S'_{i}(x_{i+1}) = S'_{i+1}(x_{i+1})
            A(2*n+i, 4*i+1) = 1.0;
            A(2*n+i, 4*i+2) = 2*x_joint;
            A(2*n+i, 4*i+3) = 3*x_joint*x_joint;
            A(2*n+i, 4*(i+1)+1) = -1.0;
            A(2*n+i, 4*(i+1)+2) = -2*x_joint;
            A(2*n+i, 4*(i+1)+3) = -3*x_joint*x_joint;
        }

        // 3. 内部节点处的二阶导数连续性：n-1个方程
        for(size_t i = 0; i < n-1; ++i) {
            double x_joint = x[i+1];
            // S''_{i}(x_{i+1}) = S''_{i+1}(x_{i+1})
            A(3*n-1+i, 4*i+2) = 2.0;
            A(3*n-1+i, 4*i+3) = 6*x_joint;
            A(3*n-1+i, 4*(i+1)+2) = -2.0;
            A(3*n-1+i, 4*(i+1)+3) = -6*x_joint;
        }

        // 4. 自然边界条件：2个方程
        // S''_{0}(x_0) = 0
        A(4*n-2, 2) = 2.0;
        A(4*n-2, 3) = 6*x[0];

        // S''_{n-1}(x_n) = 0
        A(4*n-1, 4*(n-1)+2) = 2.0;
        A(4*n-1, 4*(n-1)+3) = 6*x[n];
    }

public:
    // 构造函数
    pp_form_cubic(const std::vector<double>& x, const std::vector<double>& f, 
                  const std::string& boundary = "natural") : pp_form(x) {
        validate_input(x, f);
        compute_Interpolation(x, f);
    }

    // 计算插值
    void compute_Interpolation(const std::vector<double>& x, const std::vector<double>& f) override {
        Eigen::MatrixXd A;
        Eigen::VectorXd b;
        setup_basic_system(A, b, x, f);

        // 使用QR分解求解线性方程组
        Eigen::VectorXd solution = A.colPivHouseholderQr().solve(b);

        // 保存系数
        coeffs.resize(4 * n);
        for(size_t i = 0; i < 4 * n; ++i) {
            coeffs[i] = solution(i);
        }
    }

    // 打印表达式
    void print_Expression() const override {
        for(size_t i = 0; i < n; ++i) {
            std::cout << "区间 [" << knots[i] << ", " << knots[i+1] << "] 上的三次多项式：\n";
            std::cout << coeffs[4*i] << " + " 
                     << coeffs[4*i+1] << "x + "
                     << coeffs[4*i+2] << "x^2 + "
                     << coeffs[4*i+3] << "x^3\n";
        }
    }
};


#endif // MACRO
