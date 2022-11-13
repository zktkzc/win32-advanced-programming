#include<iostream>
#include"../ClassDll/ClassDll.h"
using namespace std;

#pragma comment(lib, "../WinBase/x64/Debug/ClassDll.lib")

int main()
{
	CMath math;
	int sum = math.Add(5, 6);
	int sub = math.Sub(5, 6);
	cout << "sum = " << sum << ", sub = " << sub << endl;
	system("pause");
	return 0;
}