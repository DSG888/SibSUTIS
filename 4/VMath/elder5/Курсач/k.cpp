#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

double Eytken(double X);
double x[100];
double y[100];
int n;

int main()
{
	ofstream fout1("y.txt");
	ofstream fout2("i.txt");
	ofstream fout3("p.txt");
	n = 6;
	for (int i = 0; i < n; i++)
	{
		x[i] = i + 1;
		y[i] = cos(x[i]);
	}
	cout << endl;
	int N = 6;
	cout << "x[0]=" << x[0] << endl;
	for (double k = 1.0; k < 6.0; k+=0.3)
	{
		double Y1 = cos(k);
		fout1 << k << " " << Y1 << endl; 
		double Y2 = Eytken(k);
		fout2 << k << " " << Y2 << endl; 
	}
	for (int i = 1; i < N; i++) 
	{
		double Y = cos(x[i]);
		fout3 << x[i] << " " << Y << endl;
	}
	fout1.close();
	fout2.close();
	fout3.close();
}

double Eytken(double X)
{
	double P[100][100];
	int i, k, j;
	for (int l = 0; l < n; l++)
	{
		for (int m = 0; m < n; m++)
			{
				if (l == m)
					P[l][m] = y[l];
				else 
					P[l][m] = 0;
			}
		cout << endl;
	}
	for (k = 1; k < n; k++)
	{
		for (i = 0; i < n - k; i++)
		{
			j = i + k;
			P[i][j] = (P[i][j - 1] * (X - x[j]) - P[i + 1][j] * (X - x[i])) / (x[i] - x[j]);
		}
		cout << endl;
	}
	return P[0][n-1];
}
