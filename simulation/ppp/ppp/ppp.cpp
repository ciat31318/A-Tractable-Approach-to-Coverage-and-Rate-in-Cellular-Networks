#include <iostream>
#include "poison.h"
#include <vector>
#include <random>
#include<math.h>
#include<fstream>
using namespace std;

const  double sigma = 0;    // 噪音平方
const double alpha = 4;      // path loss exponent
const double lambda = 24;  //基地台密度
const double power_m = 0;  // 基地台 db
//const double threshhold = -10;  
void linspace(double x1, double x2, int n, double* y);


typedef struct
{
    double x;
    double y;
}coord;



default_random_engine generator;
uniform_real_distribution<double> distribution(0.0, 1000.0);
uniform_real_distribution<double> distribution1(250.0, 750.0);
exponential_distribution<double> exp_distribution(1);
poisson_distribution<int> ppp_distribution(lambda);


double Connected_SINR( coord user, vector<coord> bss,  double threshhold )
{
    // 計算基地台到 user 的距離
    vector< double > distance;
    for (int i = 0; i < bss.size(); i++)
    {   
        distance.push_back(sqrt(pow(bss[i].x - user.x, 2) + pow(bss[i].y - user.y, 2)));
    }

    // 計算 BS 傳給user 的 power (不包含干擾) 
    vector<double> user_getpower;
    double total_power = 0;  // BS 傳給user 的 total power
    double max_sinr = 0;  // 所要連接 BS 的 SINR
    for (int i = 0; i < bss.size(); i++)
    {
        double h = exp_distribution(generator); // fading parameter 用指數分配 隨機抽取
        double temp = pow(10,(power_m/10)) * h * pow(distance[i], -1*alpha);
        total_power += temp;
        user_getpower.push_back(temp);
    }
    //計算所有 BS 的 SINR 然後取出最大值(所連結的BS)
    for (int i = 0; i < bss.size(); i++)
    {
        double sinr = user_getpower[i] / (total_power - user_getpower[i] + sigma);
        max_sinr = max(sinr, max_sinr);   
    }
    return max_sinr;
}

double Coverage_rate(double threshhold)
{
    
    int num = ppp_distribution(generator);  // PPP 基地台撒點個數
    vector<coord> bss;  // PPP 基地台撒點座標集合
    vector<coord> users; // PPP users 撒點集合
    int user_num = 1000;
    // PPP 抽取 Users 跟 BSs 加入 vector
    for (int i = 0; i < num; i++)
    {
        coord point;
        point.x = distribution(generator);
        point.y = distribution(generator);
        bss.push_back(point);
    }
    for (int i = 0; i < user_num; i++)
    {
        coord user;
        user.x = distribution1(generator);
        user.y = distribution1(generator);
        users.push_back(user);
    }

    double T = pow(10, (threshhold / 10)); // threshhold ( db 轉 w )
    //cout << "Treshhold:" << T << endl;
    int c = 0;  // users 大於 threshhold 個數

    // 計算抽取的 users 大於 threshhold 的個數
    for (int i = 0; i < users.size(); i++)
    {
        coord user = users[i];
        double  result = Connected_SINR(user, bss, threshhold);
        //cout << result << endl;
        if (result > T)
            c += 1;
    }
    //cout << (double) c / users.size() << endl;

    return (double)c / users.size();
}

void linspace(double x1, double x2, int n, double *y)
{
    double d = (x2 - x1) / n;
    for (int i = 0; i <= n; i++)
    {
        y[i] = x1 + i * d;
        cout << y[i] << endl;
    }
}

int main()
{
    double T[51];
    int point = 50; // 描繪到座標的點個數
    linspace(-10, 20, point, T);
    ofstream ofile("coverage_rate.txt", ios::out);
    for (int i = 0; i <= point; i++)
    {
        int run = 1000;
        int j = run;
        double avg = 0;
        while (j --)
            avg += Coverage_rate(T[i]);
        avg = avg / run; 
        cout << "Coverage Rate:"<<avg << endl;
        ofile << avg << endl;
    }
    system("pause");
}


