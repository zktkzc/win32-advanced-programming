#include<iostream>
#include<Windows.h>
using namespace std;

HANDLE g_hEvent = 0; // �����¼����

DWORD CALLBACK PrintProc(LPVOID pParam)
{
	while (1)
	{
		WaitForSingleObject(g_hEvent, INFINITE);
		printf("*********************\n");
		//ResetEvent(g_hEvent); // �¼���Ϊ���ź�
	}
	return 0;
}

DWORD CALLBACK ControlProc(LPVOID pParam)
{
	while (1)
	{
		Sleep(1000);
		SetEvent(g_hEvent); // �¼���Ϊ���ź�
	}
	return 0;
}

int main()
{
	//g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL); // �¼���ʼ���źţ���Ҫ�ֶ���λ
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL); // �¼���ʼ���źţ��Զ���λ
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, PrintProc, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, ControlProc, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(g_hEvent);
	return 0;
}