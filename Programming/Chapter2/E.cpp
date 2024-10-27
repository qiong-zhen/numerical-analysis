#include <iostream>  
#include <vector>  
#include <cmath>  
#include "Interpolation.hpp"
#include<cstring>
using namespace std;
int main()
{
    
    for(int i = 0;i < 4;i ++)
    {
        
        vector<double>  x = {0,6,10,13,17,20,28},
                        y1 = {6.67,17.3,42.7,37.3,30.1,29.3,28.7},
                        y2 = {6.67,16.1,18.9,15.0,10.6,9.44,8.89};
        
        NewtonInterpolation A(1000,0,43),B(1000,0,43);

        A.newtonInterpolation(x,y1);
        B.newtonInterpolation(x,y2);

        vector<double>x1_points = A.get_Xpoints();
        vector<double>x2_points = B.get_Xpoints();

        vector<double>y1_pre = A.getY_pre();
        vector<double>y2_pre = B.getY_pre();

        int y1_pre_size = y1_pre.size();
        int y2_pre_size = y2_pre.size();

        freopen("Eout1.csv","w",stdout);
        printf("x,y\n");
        for(int j = 0;j < y1_pre_size;j ++)
        {
            printf("%lf,%lf\n",x1_points[j],y1_pre[j]);
        }

        freopen("Eout2.csv","w",stdout);
        printf("x,y\n");
        for(int j = 0;j < y2_pre_size;j ++)
        {
            printf("%lf,%lf\n",x2_points[j],y2_pre[j]);
        }
    }
    return 0;
}
