#ifndef BSPLINES_H
#define BSPLINES_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <Eigen/Dense>

class CubicBsplines {
private:
    std::vector<double> nodes;
    std::vector<double> coefficients;
    
    // 用于定理3.57的系数计算
    void computeCoeffs357(const std::vector<double>& x, 
                         const std::vector<double>& y,
                         const std::vector<double>& boundary) {
        int N = x.size();
        Eigen::MatrixXd M(N, N);
        Eigen::VectorXd b(N);
        
        // 构造矩阵M
        M.setZero();
        M(0, 0) = 2; M(0, 1) = 1;
        M(N-1, N-2) = 1; M(N-1, N-1) = 2;
        
        for(int i = 1; i < N-1; ++i) {
            M(i, i-1) = 1;
            M(i, i) = 4;
            M(i, i+1) = 1;
        }
        
        // 构造向量b
        b(0) = 3*y[0] + boundary[0];  // 使用给定的导数边界条件
        for(int i = 1; i < N-1; ++i) {
            b(i) = 6*y[i];
        }
        b(N-1) = 3*y[N-1] - boundary[1];  // 使用给定的导数边界条件
        
        // 求解线性系统
        Eigen::VectorXd a = M.colPivHouseholderQr().solve(b);
        
        // 计算完整的系数，包括a_{-1}和a_N
        coefficients.resize(N+2);
        coefficients[0] = a(0) - 2*boundary[0];  // a_{-1}
        for(int i = 0; i < N; ++i) {
            coefficients[i+1] = a(i);
        }
        coefficients[N+1] = a(N-1) + 2*boundary[1];  // a_N
    }
    
    // 用于定理3.58的系数计算
    void computeCoeffs358(const std::vector<double>& x, 
                         const std::vector<double>& y) {
        int N = x.size();
        Eigen::MatrixXd M(N, N);
        Eigen::VectorXd b(N);
        
        // 构造矩阵M（使用自然边界条件）
        M.setZero();
        M(0, 0) = 4; M(0, 1) = 1;
        M(N-1, N-2) = 1; M(N-1, N-1) = 4;
        
        for(int i = 1; i < N-1; ++i) {
            M(i, i-1) = 1;
            M(i, i) = 4;
            M(i, i+1) = 1;
        }
        
        // 构造向量b
        for(int i = 0; i < N; ++i) {
            b(i) = 6*y[i];
        }
        
        // 求解线性系统
        Eigen::VectorXd a = M.colPivHouseholderQr().solve(b);
        
        // 存储系数
        coefficients = std::vector<double>(a.data(), a.data() + a.size());
    }

public:
    // 使用定理3.57的插值（完整边界条件）
    void interpolate357(const std::vector<double>& x, 
                       const std::vector<double>& y,
                       const std::vector<double>& boundary) {
        if(x.size() != y.size() || boundary.size() != 2) {
            throw std::invalid_argument("Invalid input sizes");
        }
        nodes = x;
        computeCoeffs357(x, y, boundary);
    }
    
    // 使用定理3.58的插值（自然边界条件）
    void interpolate358(const std::vector<double>& x, 
                       const std::vector<double>& y) {
        if(x.size() != y.size()) {
            throw std::invalid_argument("Invalid input sizes");
        }
        nodes = x;
        computeCoeffs358(x, y);
    }
    
    // 评估B样条在点x处的值
    double evaluate(double x) const {
        // 找到x所在的区间
        auto it = std::lower_bound(nodes.begin(), nodes.end(), x);
        if(it == nodes.end()) {
            throw std::out_of_range("x is outside the interpolation range");
        }
        
        int i = std::distance(nodes.begin(), it);
        if(i > 0) i--;
        
        // 计算局部坐标
        double t = (x - nodes[i]) / (nodes[i+1] - nodes[i]);
        
        // 使用B样条基函数计算值
        double result = 0.0;
        for(int j = -1; j <= 2; ++j) {
            if(i+j >= 0 && i+j < coefficients.size()) {
                result += coefficients[i+j] * B3(j+1-t);
            }
        }
        return result;
    }
    
    // B样条基函数
    static double B3(double t) {
        if(t < 0 || t > 4) return 0;
        if(t <= 1) return t*t*t/6;
        if(t <= 2) return (-3*t*t*t + 12*t*t - 12*t + 4)/6;
        if(t <= 3) return (3*t*t*t - 24*t*t + 60*t - 44)/6;
        return (4 - t)*(4 - t)*(4 - t)/6;
    }
    
    // 打印B样条信息
    void print() const {
        std::cout << "Coefficients: ";
        for(double c : coefficients) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
};

#endif // BSPLINES_H