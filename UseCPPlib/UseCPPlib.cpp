#include<iostream>
using namespace std;
#pragma comment(lib, "../WinBase/x64/Debug/CPPlib.lib")
#pragma comment(lib, "../WinBase/x64/Debug/Clib.lib")

int CPPlib_add(int add1, int add2);
int CPPlib_sub(int sub1, int sub2);
extern "C" int Clib_add(int add1, int add2);
extern "C" int Clib_sub(int sub1, int sub2);

int main()
{
	int sum = CPPlib_add(5, 4);
	int sub = CPPlib_sub(5, 4);
	cout << "sum = " << sum << ", sub = " << sub << endl;

	sum = Clib_add(5, 3);
	sub = Clib_sub(5, 3);
	cout << "sum = " << sum << ", sub = " << sub << endl;
	system("pause");
	return 0;
}