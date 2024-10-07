#ifndef EQUATIONSOLVER
#define EQUATIONSOLVER

#include <iostream>
#include <stdexcept>
#include <cmath>

#include "Function.hpp"

class EquationSolver{
protected:
    const Function & F;
public:
    EquationSolver(const Function& F) : F(F) {}
    virtual double solve() = 0;
};

class Bisection_Method : public EquationSolver {
private:
    double a, b;
    double eps, delta;
    int Maxiter;
public:
    Bisection_Method(const Function &F, double a, double b, 
        double eps = 1e-7, double delta = 1e-6, int Maxiter = 50) :
        EquationSolver(F), 
		a(a), 
		b(b), 
		eps(eps), 
		delta(delta), 
		Maxiter(Maxiter) {}
    
        virtual double solve() {
    if (F(a) * F(b) >= 0) {
            throw std::invalid_argument("Function values at the endpoints must have different signs.");
        }

        double c;
        for (int iter = 0; iter < Maxiter; ++iter) {
            c = (a + b) / 2.0; // Midpoint
            if (std::abs(F(c)) < eps || (b - a) < eps) {
                return c; 
            }
            if (F(c) * F(a) < 0) {
                b = c; // Root is in the left half
            } else {
                a = c; // Root is in the right half
            }
        }
        return c; 
    }
};

class Newton_Method : public EquationSolver {
private:
    double x0;
    double eps;
    double Maxiter;
public:
    Newton_Method(const Function &F, double x0, 
        double eps = 1e-7, double Maxiter = 8) :
        EquationSolver(F), x0(x0), eps(eps),Maxiter(Maxiter) {}
    
    virtual double solve() {
double x = x0;

        for (int iter = 0; iter < Maxiter; ++iter) {
            double fx = F(x);
            double dfx = F.derivative(x); // Assuming Function class has a derivative method
            
            if (std::abs(fx) < eps) {
                return x; 
            }
            if (std::abs(dfx) < eps) {
                throw std::runtime_error("Derivative is zero. No solution found.");
            }
            x = x - fx / dfx; // Newton's update
        }
        return x; 
    }
};

class Secant_Method : public EquationSolver {
private:
    double x0, x1;
    double eps;
    int Maxiter;
public:
    Secant_Method(const Function &F, double x0, double x1, 
                  double eps = 1e-7, int Maxiter = 50) :
        EquationSolver(F), x0(x0), x1(x1), eps(eps), Maxiter(Maxiter) {}

    virtual double solve() {
    for (int iter = 0; iter < Maxiter; ++iter) {
            double f0 = F(x0);
            double f1 = F(x1);
            
            if (std::abs(f1 - f0) < eps) {
                throw std::runtime_error("Function values are too close. No solution found.");
            }
            double x2 = x1 - f1 * (x1 - x0) / (f1 - f0); 
            
            if (std::abs(F(x2)) < eps) {
                return x2; 
            }
            
            x0 = x1; 
            x1 = x2; 
        }
        return x1; 
    }
};

#endif