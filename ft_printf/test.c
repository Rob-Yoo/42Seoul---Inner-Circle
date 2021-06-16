#include <stdio.h>

int main()
{
	char c[] = "this is string";

	int n = 10;
	
	printf("1 >%*s<\n", n, c);
	printf("2 >%-*s<\n", n, c);
	printf("3 >%*.s<\n", n, c);
	printf("4 >%-s<\n", c);
	printf("5 >%-.s<\n", c);
	printf("6 >%.s<\n", c);
	printf("7 >%10.4s<\n", c);
	printf("8 >%.4s<\n", c);
	printf("9 >%.1s<\n", c);
	printf("A >%.s<\n\n", c);

	printf("1 >%1s<\n", c);
	printf("2 >%-*s<\n", n, c);
	printf("3 >%.*s<\n", n, c);
	printf("4 >%-s<\n", c);
	printf("5 >%-.s<\n", c);
	printf("6 >%.s<\n", c);
	printf("7 >%10.4s<\n", c);
	printf("8 >%.4s<\n", c);
	printf("9 >%.1s<\n", c);
	printf("A >%.s<\n", c);
	printf("B >%14.10s<\n", c);
	printf("D >%-.100s<\n", c);
}
