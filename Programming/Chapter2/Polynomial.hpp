#ifndef POLYNOMIAL_HPP  
#define POLYNOMIAL_HPP  

#include <iostream>  
#include <vector>  
#include <algorithm>  
  
class Polynomial {  
public:  
    Polynomial(const std::vector<double>& coeffs = {}) : coeffs(coeffs) {}  

    Polynomial operator+(const Polynomial& other) const {  
        std::vector<double> result(std::max(coeffs.size(), other.coeffs.size()), 0.0);  
        for (size_t i = 0; i < coeffs.size(); ++i) {  
            result[i] += coeffs[i];  
        }  
        for (size_t i = 0; i < other.coeffs.size(); ++i) {  
            result[i] += other.coeffs[i];  
        }  
        while (result.size() > 1 && result.back() == 0.0) {  
            result.pop_back();  
        }  
        return Polynomial(result);  
    }  
  
    Polynomial operator*(double scalar) const {  
        std::vector<double> result(coeffs.size(), 0.0);  
        for (size_t i = 0; i < coeffs.size(); ++i) {  
            result[i] = coeffs[i] * scalar;  
        }  
        return Polynomial(result);  
    }  
  
    Polynomial operator*(const Polynomial& other) const {  
        std::vector<double> result(coeffs.size() + other.coeffs.size() + 1, 0.0);  
        for (size_t i = 0; i < coeffs.size(); i++) {  
            for (size_t j = 0; j < other.coeffs.size(); j++) {  
                result[i + j] += coeffs[i] * other.coeffs[j];  
            }  
        }  
        while (result.size() > 1 && result.back() == 0.0) {  
            result.pop_back();  
        }  
        return Polynomial(result);  
    }  
  
    double evaluate(double x) const {  
        double result = 0.0;  
        double power = 1.0;  
        for (auto coeff : coeffs) {  
            result += coeff * power;  
            power *= x;  
        }  
        return result;  
    }  
  
    void print() const {  
        for (auto it = coeffs.begin(); it != coeffs.end(); ++it) {  
            if (it != coeffs.begin() && *it >= 0) {  
                std::cout << " + ";  
            }  
            if (*it != 0.0 || it == coeffs.begin()) {  
                if (*it == -1.0 && it != coeffs.begin()) {  
                    std::cout << "-";  
                } else if (*it != 1.0 || it == coeffs.begin() && *it == 1.0 && coeffs.size() > 1) {  
                    std::cout << *it;  
                }  
                if (std::distance(coeffs.begin(), it) > 0) {  
                    std::cout << "x^";  
                    std::cout << std::distance(coeffs.begin(), it);  
                }  
            }  
        }  
        std::cout << std::endl;  
    }  
  
private:  
    std::vector<double> coeffs;  
};  


#endif //POLYNOMIAL_HPP
