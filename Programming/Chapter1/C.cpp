
#include "Function.hpp"
#include "EquationSolver.hpp"
#include <iostream>
#include <cmath>



//--------------------------------------------------------------C-------------------------------------------------------------------

// f(x) = x - tan(x)
class F5 : public Function {
public:
	double operator() (double x) const {
		return x - tan(x);
	}
};

void solve_f5(double initial_guess) {
	std::cout << "Solving x = tan(x) using Newton's Method with initial guess: " << initial_guess << std::endl;
	Newton_Method solver_f5(F5(), initial_guess);
	double x = solver_f5.solve();
	std::cout << "A root is: " << x << std::endl;
}


int main() {

	
	//--------------------------------------------------------------C-------------------------------------------------------------------
	// Find roots close to 4.5 and 7.7
	solve_f5(4.5);
	solve_f5(7.7);

	return 0;
}

