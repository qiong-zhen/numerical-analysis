#include <iostream>  
#include <vector>  
#include <cmath>  
#include "Interpolation.hpp"
using namespace std;
int N[] = {5,10,15,20};
std::vector<double> getChebyshevNodes(double st, double ed, int n) {  
    std::vector<double> nodes(n);  
    for (int i = 0; i < n; ++i) {  
        nodes[i] = 0.5 * (st + ed) + 0.5 * (ed - st) * std::cos((2 * i + 1) * std::acos(-1.0) / (2 * n));  
    }  
    return nodes;  
}  
int main()
{
    
    for(int i = 0;i < 4;i ++)
    {
        std::string filename = "CoutCheb" + std::to_string(i) + ".csv";  
        freopen(filename.c_str(),"w",stdout);
        vector<double>x,y;
        x = getChebyshevNodes(-1,1,N[i]);
        NewtonInterpolation A(1000,-1,1);
        ProblemFunction f(25);
        A.newtonInterpolation(x,f);
        vector<double>x_points = A.get_Xpoints();
        vector<double>y_pre = A.getY_pre();
        int y_pre_size = y_pre.size();
        printf("x,y\n");
        for(int j = 0;j < y_pre_size;j ++)
        {
            printf("%lf,%lf\n",x_points[j],y_pre[j]);
        }
    }
    return 0;
}
