#pragma once
#include< iostream >
#include<cstdlib >
#include<Cmath>
#include<time.h>
using namespace std;
void fac(long long  a[]);
// PPP¼»ÂIclass
class PPP
{
private:
	double  lambda;
	
public:
	double* cdf;
	PPP(double l) :lambda(l)
	{
		cdf = new double[40];
		int k = 0;
		//double err = 1;
		long long a[40];
		fac(a);
		for ( int i = 0; i < 40; i++ )
		{
			double  val = (double)exp(-1 * lambda) * pow(lambda, k)/a[k];
			if (k == 0)
				*(cdf + k) = val;
			else
			*(cdf + k) = val+ *(cdf+k-1);
			k++;
		}
	}
	~PPP()
	{
		delete[] cdf;
	}
	int PPPScater(void);
};

