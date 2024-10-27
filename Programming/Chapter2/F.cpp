#include <iostream>  
#include <vector>  
#include <cmath> 
int m = 40;
double sq3 = sqrt(3);
double absx(double x)
{
    return x > 0?x:-x;
}
double dfx(double x,double y)
{
    if(x > 0){
        return 2 * x - 3.0 / 2 * y * (1.0 / sqrt(x)) + 1;
    }
    else{
    return 2 * x + 3.0 / 2 * y * (1.0 / sqrt(-x)) - 1;
    }
}
double dfy(double x,double y)
{
    return 9.0 / 2 * y - 3 * sqrt(absx(x)) * y;
}
int main() {  
    std::vector<double> x,y;
    for(int i = 0;i <= m / 2;i ++)
    {
        double x_now = -sq3 + 2 * sq3 * i / (m / 2);
        x.push_back(x_now);
        y.push_back((sqrt(3 - x_now * x_now) + sqrt(absx(x_now))) * 2.0 / 3);
    }
    for(int i = m / 2 - 1;i >= 0;i --)
    {
        double x_now = -sq3 + 2 * sq3 * i / (m / 2);
        x.push_back(-sq3 + 2 * sq3 * i / (m / 2));
        y.push_back((-sqrt(3 - x_now * x_now) + sqrt(absx(x_now))) * 2.0 / 3);
    }
    std::vector<double> xans,yans;
    for(int i = 0;i < m;i ++)
    {
        double dy1 = -dfx(x[i],y[i]);
        double dx1 = dfy(x[i],y[i]);
        double temp1 = sqrt(dy1*dy1 + dx1 * dx1);
        dy1 = dy1 / temp1;
        dx1 = dx1 / temp1;
        double dy2 = -dfx(x[i + 1],y[i + 1]);
        double dx2 = dfy(x[i + 1],y[i + 1]);
        double temp2 = sqrt(dy2*dy2 + dx2 * dx2);
        dy2 = dy2 / temp2;
        dx2 = dx2 / temp2;
        double qx[] = {x[i],x[i] + 1.0 / 3 * dx1,x[i + 1] - 1.0 / 3 * dx1,x[i + 1]};
        double qy[] = {y[i],y[i] + 1.0 / 3 * dy1,y[i + 1] - 1.0 / 3 * dy1,y[i + 1]};
        for(double t = 0;t <= 1;t += 0.01)
        {
            double xt = qx[3] * pow(t,3) + qx[0] * pow((1 - t),3) + 3 * qx[2] * pow(t,2) * (1 - t) + 3 * qx[1] * pow((1 - t),2) * t;
            double yt = qy[3] * pow(t,3) + qy[0] * pow((1 - t),3) + 3 * qy[2] * pow(t,2) * (1 - t) + 3 * qy[1] * pow((1 - t),2) * t;
            xans.push_back(xt);
            yans.push_back(yt);
        }
    }
    freopen("Fout.csv","w",stdout);
    printf("x,y\n");
    for(int i = 0;i < xans.size();i ++)
    {
        printf("%lf,%lf\n",xans[i],yans[i]);
    }

    return 0;  
}