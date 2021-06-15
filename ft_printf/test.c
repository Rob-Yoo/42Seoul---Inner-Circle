#include <stdio.h>

int main()
{
	int n = 10;
	int width = 30;

	int m = 9;
	int wid = 15;

	printf("1 >%*d<\n", width, n); 
	printf("2 >%-*d<\n", width, n); 
	printf("3 >%*.*d<\n", width, width ,n); 
	printf("4 >%-d<\n", n); 
	printf("5 >%-.d<\n", n); 
	printf("6 >%.d<\n", n); 
	printf("7 >%10.4d<\n", n);
	printf("8 >%.4d<\n", n);
	printf("9 >%.1d<\n\n", n);

	printf("1 >%d<\n", m); 
	printf("2 >%*d<\n", wid, m); 
	printf("3 >%-*d<\n", wid, m); 
	printf("4 >%-0.*d<\n", wid, m); // warning
	printf("5 >%.09d<\n", m); 
	printf("6 >%030d<\n", m); 
	printf("7 >%10.4d<\n", m); 
	printf("8 >%-10.5d<\n", m); 
	printf("9 >%.4d<\n", m); 
	printf("10 >%.1d<\n", m); 
}