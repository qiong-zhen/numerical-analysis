#include "Function.hpp"
#include "EquationSolver.hpp"
#include <iostream>
#include <cmath>

const double pi = acos(-1.0);

// 将角度转换为弧度
double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

// 定义非线性方程 f(α)
class AlphaEquation : public Function {
private:
	double A, B, C, E;
public:
	AlphaEquation(double l, double h, double D, double beta1_deg) {
		double beta1 = degrees_to_radians(beta1_deg);  // 转换为弧度
		A = l * sin(beta1);
		B = l * cos(beta1);
		C = (h + 0.5 * D) * sin(beta1) - 0.5 * D * tan(beta1);
		E = (h + 0.5 * D) * cos(beta1) - 0.5 * D;
	}
	
	double operator() (double alpha_deg) const {
		double alpha = degrees_to_radians(alpha_deg);
		return A * sin(alpha) * cos(alpha) + B * sin(alpha) * sin(alpha) - C * cos(alpha) - E * sin(alpha);
	}
};

// 牛顿法求解
void solve_newton(double l, double h, double D, double beta1, double initial_guess_deg) {
	std::cout << "Solving using Newton's Method with D = " << D << " and initial guess: " << initial_guess_deg << " degrees" << std::endl;
	AlphaEquation eq(l, h, D, beta1);
	Newton_Method solver_newton(eq, initial_guess_deg);  // 初始猜测值以角度为单位
	double alpha = solver_newton.solve();
	std::cout << "Newton's Method result: alpha = " << alpha << " degrees" << std::endl;
}

// 割线法求解
void solve_secant(double l, double h, double D, double beta1, double initial_guess_deg_1, double initial_guess_deg_2) {
	std::cout << "Solving using Secant Method with D = " << D << " and initial guesses: " 
	<< initial_guess_deg_1 << " degrees, " << initial_guess_deg_2 << " degrees" << std::endl;
	AlphaEquation eq(l, h, D, beta1);
	Secant_Method solver_secant(eq, initial_guess_deg_1, initial_guess_deg_2);
	double alpha = solver_secant.solve();
	std::cout << "Secant Method result: alpha = " << alpha << " degrees" << std::endl;
}
int main() {

	// 参数设置
	double l = 89;       // in
	double h = 49;       // in
	double D1 = 55;      // in, part (a)
	double D2 = 30;      // in, part (b)
	double beta1 = 11.5; // degrees
	
	// (a) 验证 α ≈ 33°
	solve_newton(l, h, D1, beta1, 33);
	
	// (b) 使用初始值 33°，D = 30 in
	solve_newton(l, h, D2, beta1, 33);
	
	// (c) 使用割线法，初始值远离 33°
	solve_secant(l, h, D2, beta1, 10, 50);
	
	
	return 0;
}

