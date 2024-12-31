#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
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

void runComparison(const string& type) {
    cout << "\nRunning comparison for " << type << " boundary conditions:" << endl;
    
    // 第一种节点: ti = -6 + i, i = 1,...,11 (Theorem 3.57)
    vector<double> t1(11);
    vector<double> y1(11);
    for(int i = 0; i < 11; ++i) {
        t1[i] = -5.0 + i;  // 修改为[-5,5]区间
        y1[i] = f(t1[i]);
    }

    // 第二种节点: ti = i - 11/2, i = 1,...,10 (Theorem 3.58)
    vector<double> t2(10);
    vector<double> y2(10);
    for(int i = 0; i < 10; ++i) {
        t2[i] = -4.5 + i;  // 修改为对称分布
        y2[i] = f(t2[i]);
    }

    // 构造不同边界条件的样条
    pp_form_cubic spline1(t1, y1);
    pp_form_cubic spline2(t2, y2);
    
    // 生成绘图数据
    ofstream data_file("figure/spline_data_" + type + ".txt");
    data_file << "x exact spline1 spline2\n";

    // 在[-5,5]区间上生成密集的点
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
}

int main() {
    cout << "======================C======================" << endl;
    
    // 运行不同边界条件的比较
    runComparison("natural");
    
    cout << "======================C======================" << endl;
    return 0;
}