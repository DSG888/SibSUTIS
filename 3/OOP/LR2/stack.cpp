#include "stack.h"

void createstack(stack &st)
{
	st.s = new int[mstack_size];
	st.n = 0;
	
}

void sdel(stack &st)
{
	delete[] st.s;
	st.s = NULL;
	st.n = 0;
}

int push(stack &st, int x)
{
	if (st.n >= mstack_size)
		return 1;
	st.s[st.n] = x;
	st.n++;
	return 0;
}

int pop(stack &st, int t)
{
	if (st.n <= 0)
		return 1;
	t = st.s[st.n - 1];
	st.s[st.n - 1] = 0;
	st.n--;
	return 0;
}

int lenstack(stack &st)
{
	int i, j = 0;
	for (i=st.n-1; 0 <= i; i--)
		j++;
	return j;
}

int printstack(stack &st)
{
	int i;
	printf("---=СТЕК=---\n");
	for (i=st.n-1; 0 <= i; i--)
		printf("%d\n", st.s[i]);
	printf("---======---\n");
	return 0;
}
