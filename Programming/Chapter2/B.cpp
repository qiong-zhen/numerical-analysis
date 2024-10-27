#include <iostream>  
#include <vector>  
#include <cmath>  
#include "Interpolation.hpp"
#include<cstring>
using namespace std;
int N[] = {2,4,6,8};

int main()
{
    
    for(int i = 0;i < 4;i ++)
    {
        std::string filename = "Bout" + std::to_string(i) + ".csv";  
        freopen(filename.c_str(),"w",stdout);
        vector<double>x,y;
        for(int j = 0;j <= N[i];j ++)
        {
            double x_i = -5 + 10.0 * j / N[i];
            x.push_back(x_i);
        }
        ProblemFunction f(1);
        NewtonInterpolation A(1000,-5.0,5.0);
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
