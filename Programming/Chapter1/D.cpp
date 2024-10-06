
#include "Function.hpp"
#include "EquationSolver.hpp"
#include <iostream>
#include <cmath>


//--------------------------------------------------------------D-------------------------------------------------------------------
// f(x) = sin(x/2) - 1
class F6 : public Function {
public:
	double operator() (double x) const {
		return sin(x / 2) - 1;
	}
};

// f(x) = e^x - tan(x)
class F7 : public Function {
public:
	double operator() (double x) const {
		return exp(x) - tan(x);
	}
};

// f(x) = x^3 - 12x^2 + 3x + 1
class F8 : public Function {
public:
	double operator() (double x) const {
		return x * x * x - 12 * x * x + 3 * x + 1;
	}
};

void solve_f6() {
	std::cout << "Solving sin(x/2) - 1 using Secant Method" << std::endl;
	Secant_Method solver_f6(F6(), 0, M_PI / 2);
	double x = solver_f6.solve();
	std::cout << "A root is: " << x << std::endl;
}

void solve_f7() {
	std::cout << "Solving e^x - tan(x) using Secant Method" << std::endl;
	Secant_Method solver_f7(F7(), 1, 1.4);
	double x = solver_f7.solve();
	std::cout << "A root is: " << x << std::endl;
}

void solve_f8() {
	std::cout << "Solving x^3 - 12x^2 + 3x + 1 using Secant Method" << std::endl;
	Secant_Method solver_f8(F8(), 0, -0.5);
	double x = solver_f8.solve();
	std::cout << "A root is: " << x << std::endl;
}

int main() {

	//--------------------------------------------------------------D-------------------------------------------------------------------
	solve_f6();
	solve_f7();
	solve_f8();
	

	return 0;
}

