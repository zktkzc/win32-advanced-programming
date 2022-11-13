#include<iostream>
#include<Windows.h>
using namespace std;

HANDLE g_hSemaphore = 0;

DWORD CALLBACK TestProc(LPVOID pParam)
{
	while (1)
	{
		WaitForSingleObject(g_hSemaphore, INFINITE);
		printf("****************\n");
	}
}

int main()
{
	g_hSemaphore = CreateSemaphore(NULL, 3, 10, NULL);
	DWORD nID = 0;
	HANDLE hThread = CreateThread(NULL, 0, TestProc, NULL, 0, &nID);
	getchar();
	ReleaseSemaphore(g_hSemaphore, 5, NULL);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(g_hSemaphore);
	return 0;
}