#include<windows.h>

// ��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR IpCmdLine, int nCmdShow)
{
	// ���ڴ��д�������
	//HWND hWnd = CreateWindow("Button", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	HWND hWnd = CreateWindow("Edit", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	// ��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// ��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		// ������Ϣ
		TranslateMessage(&nMsg);
		// �ɷ���Ϣ
		DispatchMessage(&nMsg); // ����Ϣ�������ڴ�����������
	}
	return 0;
}