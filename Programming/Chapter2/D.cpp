#include <iostream>  
#include <vector>  
#include <cmath>  
#include "Interpolation.hpp"
#include<cstring>
using namespace std;
int main()
{
    
    std::vector<double> x = {0, 3, 5, 8, 13};  
    std::vector<double> y = {0,225,383,623,993};  
    std::vector<double> dy = {75, 77, 80, 74, 72};  
    HermiteInterpolator hermite(x, y, dy,1000,0,13);  
    Polynomial p = hermite.getPolynomial();
    double interpolated_value = hermite.getPointValue(10);

    std::cout << "Interpolated value at x = " << 10 << " is " << interpolated_value << std::endl;  
    double max_y_prime_pre = -1;
    
    
    vector<double>x_points = hermite.get_Xpoints();
    vector<double>y_pre = hermite.getPointsValue();
    int y_pre_size = y_pre.size();
    
    for(int i = 1;i < y_pre_size;i ++)
    {
        double y_prime = (y_pre[i] - y_pre[i- 1]) / (x_points[i] - x_points[i - 1]);
        if(max_y_prime_pre < y_prime)max_y_prime_pre = y_prime;
    }

    printf("max v = %lf\n",max_y_prime_pre);

    if(max_y_prime_pre > 81)
        printf("Speed Exceeded!!!\n");
    else
        printf("Speed not exceeded.\n");
    // freopen("Dout.csv","w",stdout);
    // printf("x,y\n");
    // for(int i = 0;i < y_pre_size;i ++)
    // {
    //     printf("%lf,%lf\n",x_points[i],y_pre[i]);
    // }
    
    return 0; 
}
