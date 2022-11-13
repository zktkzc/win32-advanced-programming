#include<stdio.h>
#pragma comment(lib, "../WinBase/x64/Debug/Clib.lib")

int main()
{
	int sum, sub;
	sum = Clib_add(5, 3);
	sub = Clib_sub(5, 3);
	printf("sum=%d,sub=%d", sum, sub);
	return 0;
}