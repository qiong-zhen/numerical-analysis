#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "ppform.h"

using namespace std;

// Runge函数
double f(double x) {
    return 1.0 / (1.0 + 25.0 * x * x);
}

int main() {
    wcout << L"======================A======================" << endl;
    
    vector<int> N_array = {6, 11, 21, 41, 81};
    vector<double> errors;  // 存储误差
    
    for(int N : N_array) {
        // 生成插值节点
        vector<double> nodes(N);
        vector<double> values(N);
        for(int i = 0; i < N; ++i) {
            nodes[i] = -1.0 + 2.0 * i / (N - 1);
            values[i] = f(nodes[i]);
        }
        
        // 构造三次样条
        pp_form_cubic spline(nodes, values);
        
        // 计算中点处的误差
        double max_error = 0.0;
        for(int i = 0; i < N-1; ++i) {
            double mid = (nodes[i] + nodes[i+1]) / 2.0;
            double error = fabs(spline(mid) - f(mid));
            max_error = max(max_error, error);
        }
        errors.push_back(max_error);
        
        // 生成绘图数据
        ofstream data_file("figure/runge_data_" + to_string(N) + ".txt");
        data_file << "x exact spline\n";
        
        int plot_points = 1000;
        for(int i = 0; i < plot_points; ++i) {
            double x = -1.0 + 2.0 * i / (plot_points - 1.0);
            data_file << x << " " << f(x) << " " << spline(x) << "\n";
        }
        data_file.close();
        
        wcout << L"N = " << N << L", Error = " << scientific << setprecision(6) 
              << max_error << endl;
        
        // 打印样条表达式
        wcout << L"\nPiecewise polynomial expressions for N = " << N << L":" << endl;
        spline.print_Expression();
        wcout << L"\n";
    }
    
    // 计算收敛率
    wcout << L"\nConvergence rates:" << endl;
    for(size_t i = 1; i < N_array.size(); ++i) {
        double rate = log(errors[i-1]/errors[i]) / log(2.0);
        wcout << L"From N=" << N_array[i-1] << L" to N=" << N_array[i] 
              << L": " << fixed << setprecision(4) << rate << endl;
    }
    
    // 保存收敛率数据
    ofstream conv_file("figure/convergence_data.txt");
    for(double err : errors) {
        conv_file << err << "\n";
    }
    conv_file.close();
    
    wcout << L"======================A======================" << endl;
    return 0;
}
