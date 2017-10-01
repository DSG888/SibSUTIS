#include <stdio.h>
#include "IVAN.h"
#define R 4
int main(){
    int i,j,l,m,t;
    float  mat[R-1][R],k,otv[R];
    /*k-koeficient na kotorui umnogat stroki*/
    FILE *stream;
    HELLO();
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
	if(j==R){
	    j=0;
	    i++;}	    
    }
    for(j=0;j<R-1;j++){
	printf("\n");
	for(l=0;l<R;l++)printf("%f ",mat[j][l]);
    }
    //prymoi hod
    for(j=1;j<i;j++){
	for(l=1;l<i;l++){
	    if(l<j)continue;
	    k=mat[l][j-1]/mat[j-1][j-1];
	    printf("\n\tK: %f\n",k);
	    for(m=0;m<R;m++){
		mat[l][m]=mat[l][m]+mat[j-1][m]*(-k);
	    }
	    for(m=0;m<R-1;m++){
		printf("\n");
		for(t=0;t<R;t++)printf("%f ",mat[m][t]);}
	}
    }
    //obratnui hod
    m=R-2;
    for(l=i-1;l>=0;l--){
	otv[m]=mat[l][R-1];
	for(j=R-2;j>=0;j--){
	    if(j!=m&&j>l){
		otv[m]=otv[m]-mat[l][j]*otv[j];
		continue;
	    }
	    if(j!=m) otv[m]=otv[m]-mat[l][j];
	}
	otv[m]=otv[m]/mat[l][m];
	m--;
    }
    //vivod otveta
    for(j=0;j<R-1;j++) printf("\nX%d:%f\n",j,otv[j]);
return 0;
}
