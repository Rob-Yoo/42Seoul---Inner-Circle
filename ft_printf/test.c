#include <stdio.h>

int main()
{
	int n = 3;
	char c = 'a';
	printf("1 >%*c<\n", n, c); 
	printf("2 >%-*c<\n", n, c); 
	printf("3 >%*.c<\n", n, c); 
	printf("4 >%-c<\n", c); 
	printf("5 >%-.c<\n", c); 
	printf("6 >%.c<\n", c); 
	printf("9 >%.c<\n", c);
}