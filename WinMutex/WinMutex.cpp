#include<iostream>
#include<Windows.h>
using namespace std;

HANDLE g_hMutex = 0; // »¥³â¾ä±ú

DWORD CALLBACK TestProc(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (1)
	{
		//printf("%s\n", pszText);
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(pszText); i++)
		{
			printf("%c", pszText[i]);
			Sleep(125);
		}
		printf("\n");
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

DWORD CALLBACK TestProc2(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (1)
	{
		//printf("%s\n", pszText);
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(pszText); i++)
		{
			printf("%c", pszText[i]);
			Sleep(125);
		}
		printf("\n");
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

int main()
{

	g_hMutex = CreateMutex(NULL, FALSE, NULL);

	DWORD nID = 0;
	char* pszText = (char*)"********";
	HANDLE hThread = CreateThread(NULL, 0, TestProc, pszText, 0, &nID);

	char* pszText2 = (char*)"--------";
	HANDLE hThread2 = CreateThread(NULL, 0, TestProc2, pszText2, 0, &nID);

	getchar();
	CloseHandle(g_hMutex);

	return 0;
}