#include <stdlib.h>
#include <stdio.h>
int main() {
     int **a,i,j,n,k;
     scanf("%d",&n); // ��������� ���������� �����
     a=(int**)malloc(sizeof(int*)*n); // ������� ������ ��� ������
     for (i=0;i<n;i++) {
         k=rand()%(2*n)+2; // � ������ ������ ��������� ���������� ��������� �� 2 �� 2*n+2-1
         a[i]=(int*)malloc(sizeof(int)*(k+1)); // �������� ������ ��� � ���������+1 (1 ��� ������ ������ ����� �)
         a[i][0]=k; // ���������� � ������� ������� ����������� ��������� � ������
     }
     for (i=0;i<n;i++) {
         printf("(%2d) ",a[i][0]); // ������� ���������� ��������� � i-��� ������
         for (j=1;j<=a[i][0];j++) {
             a[i][j]=rand()%(2*n); // ������ �������� ���� ����� �� 0 �� 2*n-1
             printf("%4d",a[i][j]); // ������� ���
         }
         printf("\n"); // ������� �� ����� ������
     } 
     for (i=0;i<n;i++) free(a[i]); // ����������� ������
     free(a);  // ������� ������
     system("pause");
}
