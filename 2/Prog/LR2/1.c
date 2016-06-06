#include <stdio.h>
#include <stdlib.h>

void init(int** arr, int n)
{
//	arr = malloc(n * sizeof(int));
	*arr = malloc(n * sizeof(int));
	int i;
	for (i = 0; i < n; ++i)
	{
//		arr[i] = i;
		*(*arr+i) = i;
	}
}

int main()
{
	int* arr = NULL;
	int n = 10;
//	init(arr, n);
	init(&arr, n);
	int i;
	for (i = 0; i < n; ++i)
	{
		printf("%d\n", arr[i]);
	}
//	
	free(arr);
	return 0;
}


