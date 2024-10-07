#ifndef EQUATIONSOLVER
#define EQUATIONSOLVER

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
    double c, fc;
    double fa = F(a), fb = F(b);
    if (fa * fb > 0) {
        throw std::runtime_error("Function has same signs at endpoints.");
    }
    int iter = 0;
    while ((b - a) / 2 > eps) {
        iter++;
        if (iter > Maxiter) throw std::runtime_error("Maximum iterations exceeded.");
        
        c = (a + b) / 2;
        fc = F(c);
        
        if (fabs(fc) < delta || (b - a) / 2 < eps) {
            return c;
        }
        
        if (fc * fa < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }
    return (a + b) / 2;
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
    double x = x0, fx = F(x), dfx;
    int iter = 0;
    while (fabs(fx) > eps) {
        iter++;
        if (iter > Maxiter) throw std::runtime_error("Maximum iterations exceeded.");

        dfx = F.derivative(x);
        if (fabs(dfx) < eps) {
            throw std::runtime_error("Derivative too small.");
        }

        x -= fx / dfx;
        fx = F(x);
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
        double x2, fx0 = F(x0), fx1 = F(x1);
        int iter = 0;
        while (fabs(x1 - x0) > eps) {
            iter++;
            if (iter > Maxiter) throw std::runtime_error("Maximum iterations exceeded.");

            if (fabs(fx0 - fx1) < eps) {
                throw std::runtime_error("Function values are too close.");
            }

            x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
            x0 = x1;
            x1 = x2;
            fx0 = fx1;
            fx1 = F(x1);

            if (fabs(fx1) < eps) break;
        }
        return x1;
    }
};


#endif