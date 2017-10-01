#include <iostream>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
	int n = 3;
	int i, j, l;
	int N = 8;
	double x[8] = {-1, 0, 1, 2, 3, 4, 5, 6};
	double y[8] = {-112, -100, -90, -76, -52, -12, 50, 140};
	double A, B, C;
	double a[3][4];
	double k;
	for (int i = 0; i < N; i++)
	{
		a[0][0] += pow(x[i], 4); 
		a[0][1] = a[1][0] += pow(x[i], 3); 
		a[0][2] = a[2][0] = a[1][1] += pow(x[i], 2); 
		a[1][2] = a[2][1] += x[i];
		a[2][2] = N;
		a[0][3] += pow(x[i], 2) * y[i];
		a[1][3] += x[i] * y[i];
		a[2][3] += y[i];
	} 
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << setw(6) << a[i][j] << " ";
		}
	cout << endl;
	}
	for (i = 0; i < n - 1; i++) //прямой ход
	{
		for (j = i + 1; j < n; j++)
		{
			k = a[j][i] / a[i][i];
			for (l = 0; l <= n; l++)
			{
					a[j][l] -= a[i][l] * k;	
			}
		}
	}
	
	for (j = 0; j < n; j++) 
	{
		for (l = 0; l < n + 1; l++)
			{
				cout << a[j][l] << " ";
			}
	cout << endl;
	}
	
	for (i = n-1; i > 0; i--) //обратный ход
	{
		for (j = 0; j < i; j++)
		{
			k = a[j][i] / a[i][i];
			for (l = n; l >= 0; l--)
			{
					a[j][l] -= a[i][l] * k;	
			}
		}
	}
	
	cout << endl;
	
	for (j = 0; j < n; j++) 
	{
		a[j][n]/=a[j][j];
		a[j][j] = 1;
		for (l = 0; l < n + 1; l++)
			{
				cout << a[j][l] << " ";
			}
	cout << endl;
	}
	
	cout << "Result:" << endl;
	
	A = a[0][3];
	B = a[1][3];
	C = a[2][3];
	
	cout << "A = " ;
	cout << A << endl;
	cout << "B = " ;
	cout << B << endl;
	cout << "C = " ;
	cout << C << endl;


	return 0;
}
