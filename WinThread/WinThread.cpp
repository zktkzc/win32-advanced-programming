#include<iostream>
#include<Windows.h>
using namespace std;

DWORD CALLBACK TestProc(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (1)
	{
		printf("%s\n", pszText);
		Sleep(1000);
	}
	return 0;
}

DWORD CALLBACK TestProc2(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (1)
	{
		printf("%s\n", pszText);
		Sleep(1000);
	}
	return 0;
}

int main()
{
	DWORD nID = 0;
	char* pszText = (char*)"********";
	HANDLE hThread = CreateThread(NULL, 0, TestProc, pszText, 0, &nID);

	WaitForSingleObject(hThread, INFINITE);

	char* pszText2 = (char*)"--------";
	HANDLE hThread2 = CreateThread(NULL, 0, TestProc2, pszText2, CREATE_SUSPENDED, &nID);

	getchar();

	SuspendThread(hThread);
	ResumeThread(hThread2);

	getchar();

	return 0;
}