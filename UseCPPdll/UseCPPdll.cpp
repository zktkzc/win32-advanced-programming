#include<iostream>
using namespace std;

_declspec(dllimport) int CPPdll_add(int sub1, int sub2);
_declspec(dllimport) int CPPdll_sub(int sub1, int sub2);
_declspec(dllimport) int CPPdll_mul(int mul1, int mul2);

#pragma comment(lib, "../WinBase/x64/Debug/CPPdll.lib") // ֪ͨ����������ץ��ź�DLL�ļ�����CPPdll.dll��

int main()
{
	int sum = CPPdll_sub(5, 4);
	int sub = CPPdll_sub(5, 4);
	int mul = CPPdll_mul(5, 4);
	cout << "sum = " << sum << ", sub = " << sub << ", mul = " << mul << endl;
	system("pause");
	return 0;
}