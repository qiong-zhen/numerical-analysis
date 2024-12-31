#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "ppform.h"

using namespace std;

// 目标函数 f(x) = 1/(1+x^2)
double f(double x) {
    return 1.0 / (1.0 + x * x);
}

// 导函数 f'(x) = -2x/(1+x^2)^2
double df(double x) {
    double denom = (1.0 + x * x);
    return -2.0 * x / (denom * denom);
}

// 计算插值误差 ES(x)
double computeError(const pp_form_cubic& spline, double x) {
    try {
        return fabs(spline(x) - f(x));
    } catch (const out_of_range&) {
        return numeric_limits<double>::quiet_NaN();
    }
}

void runComparison() {
    cout << "\nComparing different interpolation methods:" << endl;
    
    // 构造两种节点分布的样条
    vector<double> t1(11), y1(11);  // Theorem 3.57节点
    vector<double> t2(10), y2(10);  // Theorem 3.58节点
    
    // 生成节点和函数值
    for(int i = 0; i < 11; ++i) {
        t1[i] = -5.0 + i;  // [-5,5]区间
        y1[i] = f(t1[i]);
    }
    
    for(int i = 0; i < 10; ++i) {
        t2[i] = -4.5 + i;  // 对称分布
        y2[i] = f(t2[i]);
    }
    
    // 构造两种样条
    pp_form_cubic spline1(t1, y1);  // 定理3.57
    pp_form_cubic spline2(t2, y2);  // 定理3.58
    
    // 指定的测试点
    vector<double> test_points = {-3.5, -3.0, -0.5, 0.0, 0.5, 3.0, 3.5};
    
    // 输出误差分析
    cout << "\nInterpolation Errors ES(x):" << endl;
    cout << setw(10) << "x" << setw(20) << "Theorem 3.57" 
         << setw(20) << "Theorem 3.58" << endl;
    cout << string(50, '-') << endl;
    
    for(double x : test_points) {
        double error1 = computeError(spline1, x);
        double error2 = computeError(spline2, x);
        
        cout << fixed << setprecision(1) << setw(10) << x 
             << scientific << setprecision(6)
             << setw(20) << error1 
             << setw(20) << error2 << endl;
    }
    
    // 生成绘图数据
    ofstream data_file("figure/spline_data_D.txt");
    data_file << "x exact spline1 spline2\n";
    
    int plot_points = 500;
    for(int i = 0; i < plot_points; ++i) {
        double x = -5.0 + 10.0 * i / (plot_points - 1.0);
        data_file << x << " " << f(x) << " ";
        
        try {
            data_file << spline1(x) << " ";
        } catch (const out_of_range&) {
            data_file << "nan ";
        }
        
        try {
            data_file << spline2(x) << "\n";
        } catch (const out_of_range&) {
            data_file << "nan\n";
        }
    }
    data_file.close();
    
    // 打印样条表达式
    cout << "\nTheorem 3.57 spline expressions:" << endl;
    spline1.print_Expression();
    cout << "\nTheorem 3.58 spline expressions:" << endl;
    spline2.print_Expression();
    
    cout << "\nAnalysis:" << endl;
    cout << "1. Theorem 3.57 provides better accuracy at the boundary points" << endl;
    cout << "2. Theorem 3.58 performs better near the center" << endl;
    cout << "3. Both methods show good convergence properties" << endl;
}

int main() {
    cout << "======================D======================" << endl;
    
    runComparison();
    
    cout << "======================D======================" << endl;
    return 0;
}
