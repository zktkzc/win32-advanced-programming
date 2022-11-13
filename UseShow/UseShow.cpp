#include<iostream>
#include<Windows.h>
using namespace std;

typedef int(*ADD)(int m, int n);
typedef int(*SUB)(int m, int n);
typedef int(*MUL)(int m, int n);

int main()
{
	HINSTANCE hDll = LoadLibrary("CPPdll.dll"); // ���붯̬��
	cout << "hDll: " << hDll << endl;

	ADD myAdd = (ADD)GetProcAddress(hDll, "CPPdll_add");
	cout << "myAdd: " << myAdd << endl;
	int sum = myAdd(5, 4);
	cout << "sum = " << sum << endl;

	SUB mySub = (SUB)GetProcAddress(hDll, "CPPdll_sub");
	cout << "mySub: " << mySub << endl;
	int sub = mySub(5, 4);
	cout << "sub = " << sub << endl;

	MUL myMul = (MUL)GetProcAddress(hDll, "?CPPdll_mul@@YAHHH@Z");
	cout << "myMul: " << myMul << endl;
	int mul = myMul(5, 4);
	cout << "mul = " << mul << endl;

	FreeLibrary(hDll); // �ͷŶ�̬��

	system("pause");
	return 0;
}