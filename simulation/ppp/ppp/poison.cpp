#include<iostream>
#include"poison.h"
#include<Cmath>
#include<time.h>
using namespace std;
void fac(long long  a[])   //���h���
{
	a[0] = 1;
	for (int i = 1; i < 40; i++)
	{
		a[i] = a[i - 1] * i;
		//cout << a[i] << endl;
	}
};
int  PPP::PPPScater(void)  //�H����� [0,1] �϶����ƭ�, �ù����� PPP ���I�Ӽ�
{
	int i;
	srand(time(NULL));
	double x = rand()% (100+ 1);
	x = x / 100;
	//cout << x<<endl;
	for ( i = 0; i < 40; i++)
	{
		if (*(this->cdf + i) > x)
			break;
		i++;
		if (i > 39)
			break;
		
	}
	if (i == 0)
		return 0;
	else
		if (i > 39)
			return 39;
		return i - 1;
};


