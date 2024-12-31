#include "Bsplines.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

// 测试函数
double test_function(double x) {
    return sin(x);  // 使用正弦函数作为测试
}

void test_bspline_interpolation() {
    std::cout << "\n=== 测试B样条插值 ===" << std::endl;
    
    // 创建测试数据点
    std::vector<double> x;
    std::vector<double> y;
    int num_points = 10;
    for(int i = 0; i < num_points; ++i) {
        double xi = i * 2.0 * M_PI / (num_points - 1);
        x.push_back(xi);
        y.push_back(test_function(xi));
    }

    try {
        // 创建不同类型的B样条
        LinearBsplines linear_spline;
        CubicBsplines cubic_spline;
        AnyOrderBsplines quadratic_spline(3);  // 3阶=二次

        // 进行插值
        linear_spline.interpolate(x, y);
        quadratic_spline.interpolate(x, y);
        cubic_spline.interpolate(x, y);

        // 打印信息
        std::cout << "\n线性B样条：" << std::endl;
        linear_spline.print();
        std::cout << "\n二次B样条：" << std::endl;
        quadratic_spline.print();
        std::cout << "\n三次B样条：" << std::endl;
        cubic_spline.print();

        // 生成数据用于绘图
        std::ofstream outfile("bspline_results.txt");
        outfile << "x exact linear quadratic cubic\n";
        
        // 在整个区间上生成密集的点
        double x_min = x.front();
        double x_max = x.back();
        int num_eval_points = 200;
        
        for(int i = 0; i < num_eval_points; ++i) {
            double xi = x_min + i * (x_max - x_min) / (num_eval_points - 1);
            outfile << xi << " " 
                   << test_function(xi) << " ";
            
            try {
                outfile << linear_spline.evaluate(xi) << " "
                       << quadratic_spline.evaluate(xi) << " "
                       << cubic_spline.evaluate(xi);
            } catch(const std::exception& e) {
                outfile << "nan nan nan";
            }
            outfile << "\n";
        }
        
        outfile.close();
        std::cout << "\n插值结果已保存到 bspline_results.txt" << std::endl;
        
    } catch(const std::exception& e) {
        std::cerr << "B样条插值测试失败: " << e.what() << std::endl;
    }
}

int main() {
    try {
        test_bspline_interpolation();
    } catch(const std::exception& e) {
        std::cerr << "测试过程中发生错误: " << e.what() << std::endl;
        return 1;
    }
    return 0;
} 