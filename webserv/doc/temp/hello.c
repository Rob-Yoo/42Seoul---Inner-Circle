#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char dir[512];

	printf("This is hello file!\n");
	getcwd(dir, 512);
	printf("[%s]\n", dir);
}
