#include <stdio.h>
#include "IVAN.h"
#include <math.h>
#define E 0.001
#define R 256
#include <conio.h>
float mat[R-1][R],C[R-1][R-1],B[R-1][1],X[R-1][1];
int sizeof_matr(){
    int z,x;
    char mas[R];
    FILE *str;
    str=fopen("MATR.txt","r");
    z=0;x=0;
    while(1){
	if(feof(str))
	    break;
	fscanf(str,"%c",&mas[z]);
	z++;
	if(mas[z-1]=='\n') x++;
    }
    x=x+1;
return x;
}
float NORMA_B(float B[R-1][1],int s){
    int i;
    float max;
    max = B[0][0];
    for(i=0;i<s-1;i++)
	if(max<B[i][0]) max=B[i][0];
    return max;
}
float NORMA_C(float C[R-1][R-1],int s){
    int i,j;
    float mas[R-1][1],max;
    for(i=0;i<s-1;i++){
	mas[i][0]=0;
	for(j=0;j<s-1;j++) mas[i][0]+=C[i][j];
    }
    max = mas[0][0];
    for(i=0;i<s-1;i++)
	if(mas[i][0]>max) max = mas[i][0];
 return max;
}
void ALGORITM(float X[R-1][1],float C[R-1][R-1],float B[R-1][1],int s,int N){
    int i,j,k;
    float mas[R-1][1];
    for(i=0;i<N;i++){
	for(j=0;j<s-1;j++) mas[j][0] = 0;
	for(j=0;j<s-1;j++){
	    for(k=0;k<s-1;k++) mas[j][0]=mas[j][0] + C[j][k]*X[k][0];
	}
	for(j=0;j<s-1;j++) X[j][0] = B[j][0] - mas[j][0];
	printf("\nMATRIX X:\n");
	for(j=0;j<s-1;j++) printf("\n %f",X[j][0]);
    }
}

// s - sizeof matr (column)
int MPI(float mat[R-1][R],int s,float C[R-1][R-1],float B[R-1][1],float X[R-1][1]){
    int i,j,k;
    unsigned int N;
    float counter;
    // privodim matricu k vidu udobnoi dly itteracii
    for (i=0;i<s;i++){
	counter = 1;
	for(j=0;j<=s;j++){
	    if(i==j){ counter = mat[i][j];break;}
	}
	for(k = 0;k <= s;k++){
	    mat[i][k]=mat[i][k]/counter;}
	}
	// diagonalnie elementi = 0
    for(i=0;i<s;i++){
	for(j=0;j<s;j++)
	if(i==j)
	    mat[i][j]=0;
    }
    // poluchaem matricu C
    for(i=0;i<s-1;i++)
	for(j=0;j<s-1;j++) C[i][j]=mat[i][j];
    printf("\nMATRIX C:");
    for(i=0;i<s-1;i++){
	printf("\n");
	for(j=0;j<s-1;j++) printf(" %f ",C[i][j]);
    }
    // poluchaem matricu B
    for(i=0;i<s-1;i++) B[i][0] = mat[i][s-1];
    printf("\nMATRICA B:\n");
    for(i=0;i<s-1;i++) printf("\n %f",B[i][0]);
    // obnulyem X dly pervogo shaga
    for(i=0;i<s-1;i++) X[i][0]=0;
    printf("\nMATRIX X\n");
    for(i=0;i<s-1;i++) printf("\n %f",X[i][0]);
    printf("\nnorma C:  %f \n",NORMA_C(C,s));
    
    if (NORMA_C(C,s)>=1){
	printf("\n itteracionnii process ne shoditsy\n");
	return -1;
    }
    printf("\nnorma B:  %f \n",NORMA_B(B,s));
    //vichislyem kollichestvo shagov
    N = ((logf(fabs((E*(1-NORMA_C(C,s)))/NORMA_B(B,s))))/logf(fabs((NORMA_C(C,s))))) + 1;
    printf("\nN: %d\n",N);
    printf("\n\n");
    ALGORITM(X,C,B,s,N);
    return 0;
}
int main(){
    int i,j,l,s;
    /*k-koeficient na kotorui umnogat stroki*/
    FILE *stream;
    HELLO();
    s=sizeof_matr()+1;
    //read from file
    stream = fopen("MATR.txt","r");
    if(stream==NULL){
	printf("\nERROR\n");
	return 0;
    }
    i=0;
    j=0;
    while(1){
	if(feof(stream))
	    break;
	fscanf(stream,"%f",&mat[i][j]);
	j++;
	if(j==s){
	    j=0;
	    i++;}
    }
    for(j=0;j<s-1;j++){
	printf("\n");
	for(l=0;l<s;l++)printf("%f ",mat[j][l]);
    }
    printf("\n\n");
    if (MPI(mat,s,C,B,X)!=0)
	return 0;
    printf("\n");
    for(j=0;j<s-1;j++){
	printf("\n");
	for(l=0;l<s;l++)printf("%f ",mat[j][l]);
    }
    getch();
return 0;
}
