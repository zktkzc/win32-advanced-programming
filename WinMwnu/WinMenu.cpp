#include<windows.h>
#include"resource.h"

HINSTANCE g_hInstance = 0;

void OnCreate(HWND hWnd)
{
	// ��ȡ�˵����
	HMENU hMenu = LoadMenu(g_hInstance, (char*)IDR_MENU1);
	// ���ò˵�
	SetMenu(hWnd, hMenu);
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NEW:
		MessageBox(hWnd, "�½������", "Infor", MB_OK);
		break;
	case ID_EXIT:
		MessageBox(hWnd, "�˳������", "Infor", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd, "���ڱ����", "Infor", MB_OK);
		break;
	}
}

// ���ڴ��������Զ��壬������Ϣ��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_CREATE:
		OnCreate(hWnd);
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // ����ʹGetMessage��������0
		break;
	}

	return DefWindowProc(hWnd, msgID, wParam, lParam); // ��������Ϣ��Ĭ�ϴ���
}

// ��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR IpCmdLine, int nCmdShow)
{
	g_hInstance = hIns;

	// ע�ᴰ����
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0; // ������ĸ�������buff�Ĵ�С
	wc.cbWndExtra = 0; // ���ڵĸ�������buff�Ĵ�С
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���ڱ���ɫ���
	wc.hCursor = NULL; // ���ڹ����
	wc.hIcon = NULL; // ����ͼ����
	wc.hInstance = hIns; // ��ǰģ���ʵ�����
	wc.lpfnWndProc = WndProc; // ���ڴ�����
	wc.lpszClassName = "Main"; // �����������
	wc.lpszMenuName = NULL; // ���ڲ˵�����ԴID�ַ��� (char*)IDR_MENU1
	wc.style = CS_HREDRAW | CS_VREDRAW; // ������ķ��
	RegisterClass(&wc); // ���������и�ֵȫ��д�����ϵͳ(ע�ᴰ���࣬ע��ɹ��󣬷���һ�����ֱ�ʶ)

	// ���ڴ��д�������
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	// ��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// ��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		// ������Ϣ����������Ϣ������ַ���Ϣ
		TranslateMessage(&nMsg);
		// �ɷ���Ϣ
		DispatchMessage(&nMsg); // ����Ϣ�������ڴ�����������
	}
	return 0;
}