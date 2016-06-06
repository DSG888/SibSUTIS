#include <stdio.h>
int main()
{
	int i, j;
	printf("Input i & j value: ");
	scanf("%d %d", &i,&j);
	printf("Your input was i=%d, j=%d\nInput i & j again: ",i,j);
	scanf("%d %d",&i,&j);
	printf("Your input was i=%d, j=%d\n",i,j);
	printf("i + j = %d\n",i + j);
	return 0;
}
