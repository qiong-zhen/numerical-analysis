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
    double c; // midpoint
    double fa = F(a);
    double fb = F(b);

    // Check if the function has opposite signs at the endpoints
    if (fa * fb > 0) {
        throw std::runtime_error("Same signs at endpoints.");
    }

    int iter = 0; 

    // Main loop until the interval is sufficiently small
    while ((b - a) / 2.0 > eps) {
        if (iter >= Maxiter) {
            throw std::runtime_error("Maximum iteration limit reached.");
        }
        
        c = a + (b - a) / 2.0; // Calculate the midpoint
        double fc = F(c); // Function value at midpoint

        // Check for convergence
        if (fabs(fc) < delta || (b - a) < eps) {
            return c;
        }

        // Narrow down the interval based on the sign of f(c)
        if (fa * fc < 0) {
            b = c; // root is in left half
            fb = fc;
        } else {
            a = c; // root is in right half
            fa = fc;
        }
        
        iter++; 
    }

    return (a + b) / 2.0; 
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
    double x = x0, fx, dfx;
    int iter = 0;

    do {
        fx = F(x);
        if (fabs(fx) <= eps) break;

        dfx = F.derivative(x);
        if (fabs(dfx) < eps) {
            throw std::runtime_error("Derivative value is excessively small.");
        }

        x -= fx / dfx;
        iter++;
        if (iter > Maxiter) {
            throw std::runtime_error("Maximum iteration limit reached.");
        }
    } while (true);
    
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
        if (iter++ > Maxiter) {
            throw std::runtime_error("Maximum iteration limit reached.");
        }

        if (fabs(fx0 - fx1) < eps) {
            throw std::runtime_error("Values are too close.");
        }

        x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        x0 = x1; fx0 = fx1;
        x1 = x2; fx1 = F(x2);

        if (fabs(fx1) <= eps) break;
    }
    
    return x1;
}

};


#endif