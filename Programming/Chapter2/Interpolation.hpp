// Interpolation.hpp  
#ifndef INTERPOLATION_HPP  
#define INTERPOLATION_HPP  
  
#include <iostream>  
#include <cmath>  
#include <vector>  
#include <functional>  
#include "Polynomial.hpp"
#include "Function.hpp"
#include <cassert>  
class ProblemFunction:public Function{
private:
    double a;
public:
    ProblemFunction(double aa){a=aa;};
    double operator() (double x) const override
    {
        return 1.0 / (1.0 + a * x * x);
    }
};

class Interpolation
{
// private:
//     /* data */
private:
    std::vector<double>x_points;
    std::vector<double>y_pre;
    int N;
    double st,ed;
public:
    Interpolation(const int N,const double st,const double ed)
    {
        for(int i = 0;i <= N;i ++)
        {
            x_points.push_back(st +(ed - st) * i / N);
        }
    };
    std::vector<double> getY_pre() const{
        return y_pre;
    }
    void setY_pre(std::vector<double> Y_pre)
    {
        y_pre = Y_pre;
        return;
    }
    std::vector<double>get_Xpoints() const{
        return x_points;
    }

};


class NewtonInterpolation:public Interpolation{  
public:  
    NewtonInterpolation(const int N,const double st,const double ed):Interpolation(N,st,ed){};
    void newtonInterpolation(const std::vector<double>& x, const std::vector<double>& y) {  
        int n = x.size();  
        std::vector<std::vector<double>> table = dividedDifferenceTable(x, y);  
        int n_points = get_Xpoints().size();
        std::vector<double> results;
        for(int j = 0;j < n_points;j ++)
        {
            double result = table[0][0];  
            double productTerm = 1.0;  
    
            for (int i = 1; i < n; ++i) 
            {  
                productTerm *= (get_Xpoints()[j] - x[i - 1]);  
                result += productTerm * table[0][i];  
            }  
            results.push_back(result);
        }
        setY_pre(results);
    }  
    void newtonInterpolation(const std::vector<double>& x, ProblemFunction f) {  
        int n = x.size();  
        std::vector<double> y;
        for(int i = 0;i < n;i ++)y.push_back(f(x[i]));
        std::vector<std::vector<double>> table = dividedDifferenceTable(x, y);  
        int n_points = get_Xpoints().size();
        std::vector<double> results;
        for(int j = 0;j < n_points;j ++)
        {
            double result = table[0][0];  
            double productTerm = 1.0;  
    
            for (int i = 1; i < n; ++i) 
            {  
                productTerm *= (get_Xpoints()[j] - x[i - 1]);  
                result += productTerm * table[0][i];  
            }  
            results.push_back(result);
        }
        setY_pre(results);
    }  
    
private:
    std::vector<std::vector<double>> dividedDifferenceTable(const std::vector<double>& x, const std::vector<double>& y) {  
        int n = x.size();  
        std::vector<std::vector<double>> table(n, std::vector<double>(n, 0.0));  
        for (int i = 0; i < n; ++i) {  
            table[i][0] = y[i];  
        }  
        for (int j = 1; j < n; ++j) {  
            for (int i = 0; i < n - j; ++i) {  
                table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);  
            }  
        }  
    
        return table;  
    }  
};  

class HermiteInterpolator:public Interpolation{  
public:  
    HermiteInterpolator(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& y_prime, int N, double st, double ed)  
        : Interpolation(N, st, ed), x(x), y(y), y_prime(y_prime)  {  
        computeHermitePolynomial();  
    }
  
    Polynomial getPolynomial() const {  
        return polynomial;  
    }  
    
    double getPointValue(double x_val){
        return getPolynomial().evaluate(x_val);
    }

    std::vector<double> getPointsValue(){
        std::vector<double> results(get_Xpoints().size());
        for(size_t i = 0;i < get_Xpoints().size(); i ++)results[i] = getPointValue(get_Xpoints()[i]);
        return results;
    }
private:  

    std::vector<double> x, y, y_prime;  
    Polynomial polynomial;  


    void computeHermitePolynomial() {  
        size_t nx = x.size();
        std::vector<double> hx,hy;
        for(size_t i = 0;i < nx;i ++)
        {
            hx.push_back(x[i]);
            hx.push_back(x[i]);
            hy.push_back(y[i]);
            hy.push_back(y_prime[i]);
        }

        size_t n = hx.size();
        std::vector<std::vector<double>> dft(n, std::vector<double>(n + 1, 0.0));  
        for (size_t i = 0; i < n; i++) {  
            dft[i][0] = hx[i];  
        }  
        for (size_t i = 0; i < n; i += 2) {  
            dft[i][1] = hy[i];  
            if (i + 1 < n) {  
                dft[i + 1][1] = hy[i];  
                dft[i + 1][2] = hy[i + 1];  
            }  
        }  
        
        for (size_t i = 2; i < n; i += 2) {  
            dft[i][2] = (dft[i][1] - dft[i - 1][1]) / (dft[i][0] - dft[i - 1][0]);
        } 
        for (size_t c = 3; c <= n; c++) {  
            for (size_t r = c - 1; r < n; r++) {  
                dft[r][c] = (dft[r][c - 1] - dft[r - 1][c - 1]) / (dft[r][0] - dft[r - c + 1][0]);  
            }  
        }  
        Polynomial p({1});
        Polynomial H({0});  
        for (size_t i = 0; i < n; i++) {  
            H = H + p * Polynomial({dft[i][i + 1]});
            p = Polynomial({-hx[i],1}) * p;  
        }  
        polynomial = H;
    }  

};  
#endif // INTERPOLATION_HPP
