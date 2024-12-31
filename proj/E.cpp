#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "src/ppform.h"

using namespace std;

// 计算累积弦长参数化的节点
vector<double> compute_chordal_params(const vector<vector<double>>& points) {
    vector<double> params(points[0].size(), 0.0);
    for(size_t i = 1; i < points[0].size(); ++i) {
        double dx = points[0][i] - points[0][i-1];
        double dy = points[1][i] - points[1][i-1];
        params[i] = params[i-1] + sqrt(dx*dx + dy*dy);
    }
    // 归一化到[0,1]
    double total_length = params.back();
    for(double& p : params) {
        p /= total_length;
    }
    return params;
}

// 生成心形曲线的点
void generate_curve_points(int N, vector<vector<double>>& points, int curve_type) {
    points.resize(3, vector<double>(N+1));
    
    if(curve_type == 2) {  // r2(t)
        for(int i = 0; i <= N; ++i) {
            double t = i * 6.0 * M_PI / N;
            points[0][i] = sin(t) + t * cos(t);
            points[1][i] = cos(t) - t * sin(t);
        }
    } else if(curve_type == 3) {  // r3(t)
        for(int i = 0; i <= N; ++i) {
            double t = i * 2.0 * M_PI / N;
            double u = cos(t);
            double v = sin(t);
            points[0][i] = sin(u) * cos(v);
            points[1][i] = sin(u) * sin(v);
            points[2][i] = cos(u);
        }
    }
}

void fit_and_save_curve(int N, int curve_type) {
    vector<vector<double>> points;
    generate_curve_points(N, points, curve_type);
    
    // 计算两种参数化方式
    vector<double> uniform_params(N+1);
    for(int i = 0; i <= N; ++i) {
        uniform_params[i] = (double)i / N;
    }
    vector<double> chordal_params = compute_chordal_params(points);
    
    // 构造样条
    vector<pp_form_cubic> splines_uniform;
    vector<pp_form_cubic> splines_chordal;
    
    for(size_t i = 0; i < points.size(); ++i) {
        splines_uniform.push_back(pp_form_cubic(uniform_params, points[i]));
        splines_chordal.push_back(pp_form_cubic(chordal_params, points[i]));
    }
    
    // 保存结果
    string filename = "figure/curve" + to_string(curve_type) + "_N" + to_string(N) + ".txt";
    ofstream outfile(filename);
    outfile << "t uniform_x uniform_y";
    if(curve_type == 3) outfile << " uniform_z";
    outfile << " chordal_x chordal_y";
    if(curve_type == 3) outfile << " chordal_z";
    outfile << "\n";
    
    int num_points = 1000;
    for(int i = 0; i <= num_points; ++i) {
        double t = (double)i / num_points;
        outfile << t;
        
        // 均匀参数化的结果
        for(const auto& spline : splines_uniform) {
            outfile << " " << spline(t);
        }
        
        // 弦长参数化的结果
        for(const auto& spline : splines_chordal) {
            outfile << " " << spline(t);
        }
        outfile << "\n";
    }
    outfile.close();
}

int main() {
    cout << "======================E======================" << endl;
    
    vector<int> N_values = {10, 40, 160};
    
    try {
        // 拟合r2(t)曲线
        for(int N : N_values) {
            cout << "Fitting r2(t) with N = " << N << endl;
            fit_and_save_curve(N, 2);
        }
        
        // 拟合r3(t)曲线
        for(int N : N_values) {
            cout << "Fitting r3(t) with N = " << N << endl;
            fit_and_save_curve(N, 3);
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    cout << "======================E======================" << endl;
    return 0;
}
