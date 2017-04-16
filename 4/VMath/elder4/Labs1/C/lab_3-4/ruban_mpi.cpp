#include "fstream"
#include "iostream"
#include <math.h>

#define N 3
#define E 0.0001

using namespace std;

void print_x(double x[N])
{
    for (int i = 0; i < N; i++)
        printf("\t%.8f\n", x[i]);
}

void mx_na_mx(double d[N], double c[N][N], double x[N])
{
    double e;
    for (int i = 0; i < N; i++) {
        e = 0;
        for (int j = 0; j < N; j++)
            e += c[i][j]*x[j];
        d[i] = e;
    }
}

// X(k+1) = B(k)-C(K)*X[k]
void mpi(double x[N], double c[N][N], double b[N], int n)
{
    double d[N];
    for (int i = 0; i < n; i++) { 
        mx_na_mx(d, c, x);  
        
            for (int j = 0; j < N; j++)
            x[j] = b[j] - d[j];
        
                cout << "x" << i+1 << ":" << endl;
        print_x(x);
    }
}

void zeidel(double x[N], double c[N][N], double b[N], int n)
{
    double s; // сумма (C(1,1)*X(1)+C(2,2)*X(2)+.....)
    for (int i = 0; i < n; i++) {  
        for (int j = 0; j < N; j++) 
            s = 0;
            for (int k = 0; k < N; k++)
                s += c[j][k]*x[k];  используется элемент X(K)
            // вычитанием из B суммы
            x[j] = b[j] - s;
        }
        cout << "x" << i+1 << ":" << endl;
        print_x(x);
    }
} 


// считаем первую норму
void norma1(double c[N][N], double b[N], double *nc, double *nb)
{
    double sum, max = -1;
    
    for (int j = 0; j < N; j++) {
        sum = 0;
        for (int i = 0; i < N; i++) 
            sum += fabs(c[i][j]);
        if (sum > max)
            max = sum;
    }
    *nc = max; 

    // далее считаем нонрму B
    sum = 0;
    for (int i = 0; i < N; i++)
        sum += fabs(b[i]);
    *nb = sum;
}

// бесконечная норма по строкам
void norma8(double c[N][N], double b[N], double *nc, double *nb)
{
    double sum, max = -1;
    for (int i = 0; i < N; i++) {
        sum = 0;
        for (int j = 0; j < N; j++)
            sum += fabs(c[i][j]);
        if (sum > max)
            max = sum;
    }
    *nc = max;

    // норма B
    max = -1;
    for (int i = 0; i < N; i++)
        if (fabs(b[i]) > max)
            max = fabs(b[i]);
    *nb = max;
}

int main()
{
  
    ifstream in("in.txt");
    
    double c[N][N] , b[N], x[N], xmpi[N], xzeid[N];
    
    
    for (int i = 0; i < N; i++) {
        x[i] = 0; 
        for (int j = 0; j < N; j++)
            in >> c[i][j]; 
        in >> b[i]; 
    }
    for(int i=0;i<N;i++)
    {
            xmpi[i]=x[i];
            xzeid[i]=x[i];
            }
    // приводим матрицу к виду, удобному для МПИ
    double tmp;
    for (int i = 0; i < N; i++) {
        tmp = c[i][i];
               b[i] /= tmp;  
        for (int j = 0; j < N; j++)
            c[i][j] /= tmp;
        c[i][i] = 0;
    }

    
    cout << "Matrix C:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("\t%.2f", c[i][j]);
        printf("\n");
    }
   
    cout << "Matrix B:" << endl;
    for (int i = 0; i < N; i++)
        printf("\t%.2f\n", b[i]);
    
    //
    double nb , nc; 
    norma8(c, b, &nc, &nb);
    cout << "norma c = " << nc << endl;
    cout << "norma b = " << nb << endl;
    int n =(int)((log(E*(1-nc)/nb)/log(nc))+1); 
    mpi(xmpi, c, b, n);
    printf("=================\n");
    printf("      ZEIDEL     \n");
    zeidel(xzeid, c, b, n); 
getchar();
    return 0;
}
