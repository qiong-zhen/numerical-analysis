#include "Bsplines.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

// 测试函数
double test_function(double x) {
    return sin(x);  // 使用sin函数作为示例
}

// 测试B样条插值
void test_bspline_interpolation() {
    // 定义节点和对应的y值
    std::vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0};  // 节点
    std::vector<double> y = {test_function(0.0), test_function(1.0), test_function(2.0), 
                             test_function(3.0), test_function(4.0)};  // 对应的y值

    // 创建CubicBsplines对象
    CubicBsplines cubic_spline;

    // 定义边界条件 (比如这里使用自然边界条件)
    std::vector<double> boundary = {0.0, 0.0};  // 自然边界条件，第二个值表示导数在最后一个点为零
    
    // 进行插值
    cubic_spline.interpolate357(x, y, boundary);

    // 打印插值结果
    cubic_spline.print();

    // 测试插值计算，获取某些x点的插值结果
    std::cout << "Interpolated value at x=1.5: " << cubic_spline.evaluate(1.5) << std::endl;
    std::cout << "Interpolated value at x=2.5: " << cubic_spline.evaluate(2.5) << std::endl;
}

// 生成测试数据并进行插值对比
void generate_and_compare() {
    std::vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y = {test_function(0.0), test_function(1.0), test_function(2.0), 
                             test_function(3.0), test_function(4.0)};
    
    // 创建B样条对象
    CubicBsplines cubic_spline;
    
    // 使用自然边界条件进行插值
    cubic_spline.interpolate358(x, y);
    
    // 打印系数
    cubic_spline.print();
    
    // 输出一些插值结果
    for (double xi = 0.0; xi <= 4.0; xi += 0.5) {
        std::cout << "Interpolated value at x = " << xi << " : " << cubic_spline.evaluate(xi) << std::endl;
    }
}

int main() {
    // 测试函数调用
    std::cout << "Testing cubic spline interpolation with boundary conditions:" << std::endl;
    test_bspline_interpolation();
    
    // 生成数据并进行插值比较
    std::cout << "\nGenerating and comparing interpolated values:" << std::endl;
    generate_and_compare();
    
    return 0;
}
