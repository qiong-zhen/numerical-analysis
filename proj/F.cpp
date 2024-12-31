#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "src/ppform.h"

using namespace std;

// 计算差商表
vector<vector<double>> dividedDifference(const vector<double>& t, double x) {
    int n = t.size();
    vector<vector<double>> dd(n, vector<double>());
    
    // 计算 (t[i]-x)_{+}^{n-2}
    for(int i = 0; i < n; ++i) {
        if(t[i] >= x) {
            dd[0].push_back(pow(t[i] - x, n-2));
        } else {
            dd[0].push_back(0.0);
        }
    }
    
    // 计算差商
    for(int j = 1; j < n; ++j) {
        for(int i = 0; i < n-j; ++i) {
            double denom = t[i+j] - t[i];
            if(abs(denom) < 1e-10) {
                dd[j].push_back(0.0);  // 处理除零情况
            } else {
                dd[j].push_back((dd[j-1][i+1] - dd[j-1][i]) / denom);
            }
        }
    }
    
    return dd;
}

void computeCase1() {
    cout << "\nCase 1: Three Points" << endl;
    vector<double> t = {0.0, 1.0, 2.0};
    
    ofstream out("figure/divided_diff_1.txt");
    out << "x f[0] f[1] f[2] f[0,1] f[1,2] f[0,1,2]\n";
    
    // 在节点范围内计算，包括端点
    for(double x = 0.0; x <= 2.0; x += 0.01) {
        auto dd = dividedDifference(t, x);
        out << fixed << setprecision(6) << x;
        for(const auto& row : dd) {
            for(double val : row) {
                out << " " << val;
            }
        }
        out << "\n";
    }
    out.close();
    
    // 打印特定点的差商表
    cout << "\nDivided differences at x = 1.0:" << endl;
    auto dd = dividedDifference(t, 1.0);
    for(size_t i = 0; i < dd.size(); ++i) {
        cout << "Order " << i << ": ";
        for(double val : dd[i]) {
            cout << scientific << setprecision(6) << setw(15) << val;
        }
        cout << endl;
    }
}

void computeCase2() {
    cout << "\nCase 2: Four Points" << endl;
    vector<double> t = {0.0, 1.0, 2.0, 3.0};
    
    ofstream out("figure/divided_diff_2.txt");
    out << "x f[0] f[1] f[2] f[3] f[0,1] f[1,2] f[2,3] f[0,1,2] f[1,2,3] f[0,1,2,3]\n";
    
    // 在节点范围内计算，包括端点
    for(double x = 0.0; x <= 3.0; x += 0.01) {
        auto dd = dividedDifference(t, x);
        out << fixed << setprecision(6) << x;
        for(const auto& row : dd) {
            for(double val : row) {
                out << " " << val;
            }
        }
        out << "\n";
    }
    out.close();
    
    // 打印特定点的差商表
    cout << "\nDivided differences at x = 1.5:" << endl;
    auto dd = dividedDifference(t, 1.5);
    for(size_t i = 0; i < dd.size(); ++i) {
        cout << "Order " << i << ": ";
        for(double val : dd[i]) {
            cout << scientific << setprecision(6) << setw(15) << val;
        }
        cout << endl;
    }
}

int main() {
    cout << "======================F======================" << endl;
    
    try {
        computeCase1();
        computeCase2();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    cout << "======================F======================" << endl;
    return 0;
}
