#include "Function.hpp"
#include "EquationSolver.hpp"
#include <iostream>
#include <cmath>

const double L = 10.0;
const double r = 1.0;
const double V_target = 12.4;

// 方程 f(h) = 0 的定义
class VolumeFunction : public Function {
public:
	double operator() (double h) const {
		return L * (0.5 * M_PI * r * r - r * r * asin(h / r) - h * sqrt(r * r - h * h)) - V_target;
	}
};

// 二分法求解
void solve_bisection() {
	std::cout << "Solving using Bisection Method..." << std::endl;
	Bisection_Method solver_bisection(VolumeFunction(), 0.0, r, 1e-7, 1e-6);
	double h = solver_bisection.solve();
	std::cout << "Bisection Method result: h = " << h << " ft" << std::endl;
}

// 牛顿法求解
void solve_newton() {
	std::cout << "Solving using Newton's Method..." << std::endl;
	Newton_Method solver_newton(VolumeFunction(), 0.5);  // 初始猜测值 h = 0.5
	double h = solver_newton.solve();
	std::cout << "Newton's Method result: h = " << h << " ft" << std::endl;
}

// 割线法求解
void solve_secant() {
	std::cout << "Solving using Secant Method..." << std::endl;
	Secant_Method solver_secant(VolumeFunction(), 0.1, 0.9);  // 初始猜测值 h0 = 0.1, h1 = 0.9
	double h = solver_secant.solve();
	std::cout << "Secant Method result: h = " << h << " ft" << std::endl;
}

int main() {

	solve_bisection();
	solve_newton();
	solve_secant();

	return 0;
}

