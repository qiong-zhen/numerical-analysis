#include "ppform.h"
#include <iostream>
#include <iomanip>
#include <fstream>

// 用于测试的简单函数
double test_function(double x) {
    return x * x;  // 测试函数 f(x) = x^2
}

void test_linear_interpolation() {
    std::cout << "\n=== 测试线性插值 ===" << std::endl;
    
    // 创建测试数据
    std::vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y;
    for(double xi : x) {
        y.push_back(test_function(xi));
    }

    try {
        // 创建线性插值对象
        pp_form_linear linear_spline(x, y);
        
        // 打印插值表达式
        std::cout << "\n分段线性插值表达式：" << std::endl;
        linear_spline.print_Expression();

        // 测试一些点的值
        std::cout << "\n测试点求值：" << std::endl;
        std::vector<double> test_points = {0.5, 1.5, 2.5, 3.5};
        for(double xi : test_points) {
            std::cout << "x = " << std::setw(4) << xi 
                     << ": 插值结果 = " << std::setw(10) << linear_spline(xi)
                     << ", 实际值 = " << std::setw(10) << test_function(xi) << std::endl;
        }
    } catch(const std::exception& e) {
        std::cerr << "线性插值测试失败: " << e.what() << std::endl;
    }
}

void test_cubic_interpolation() {
    std::cout << "\n=== 测试三次样条插值 ===" << std::endl;
    
    // 创建测试数据
    std::vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y;
    for(double xi : x) {
        y.push_back(test_function(xi));
    }

    try {
        // 创建三次样条插值对象
        pp_form_cubic cubic_spline(x, y);
        
        // 打印插值表达式
        std::cout << "\n三次样条插值表达式：" << std::endl;
        cubic_spline.print_Expression();

        // 测试一些点的值
        std::cout << "\n测试点求值：" << std::endl;
        std::vector<double> test_points = {0.5, 1.5, 2.5, 3.5};
        for(double xi : test_points) {
            std::cout << "x = " << std::setw(4) << xi 
                     << ": 插值结果 = " << std::setw(10) << cubic_spline(xi)
                     << ", 实际值 = " << std::setw(10) << test_function(xi) << std::endl;
        }
    } catch(const std::exception& e) {
        std::cerr << "三次样条插值测试失败: " << e.what() << std::endl;
    }
}

void save_results_for_plotting() {
    std::cout << "\n=== 生成绘图数据 ===" << std::endl;
    
    // 创建测试数据
    std::vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y;
    for(double xi : x) {
        y.push_back(test_function(xi));
    }

    // 创建插值对象
    pp_form_linear linear_spline(x, y);
    pp_form_cubic cubic_spline(x, y);

    // 生成密集的点用于绘图
    std::ofstream outfile("interpolation_results.txt");
    outfile << "x exact linear cubic\n";
    
    for(double xi = 0; xi <= 4.0; xi += 0.1) {
        outfile << xi << " " 
               << test_function(xi) << " "
               << linear_spline(xi) << " "
               << cubic_spline(xi) << "\n";
    }
    outfile.close();
}

int main() {
    try {
        test_linear_interpolation();
        test_cubic_interpolation();
        save_results_for_plotting();
        
        std::cout << "\n所有测试完成！数据已保存到 interpolation_results.txt" << std::endl;
    } catch(const std::exception& e) {
        std::cerr << "测试过程中发生错误: " << e.what() << std::endl;
        return 1;
    }
    return 0;
} 