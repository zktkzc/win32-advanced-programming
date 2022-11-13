#include<windows.h>
#include"resource.h"

HINSTANCE g_hInstance = 0;

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NEW:
		if (HIWORD(wParam) == 0)
		{
			MessageBox(hWnd, "�½��˵�����", "Infor", MB_OK);
		}
		else if (HIWORD(wParam) == 1)
		{
			MessageBox(hWnd, "ctrl+n�����", "Infor", MB_OK);
		}
		break;
	}
}

// ���ڴ��������Զ��壬������Ϣ��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_SETCURSOR:
	{
		HCURSOR hCursor = LoadCursor(g_hInstance, (char*)IDC_CURSOR2);
		if (LOWORD(lParam) == HTCLIENT)
		{
			SetCursor(hCursor);
			return 0;
		}
		else
		{
			// �ǿͻ���
		}
	}
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
	wc.hCursor = LoadCursor(hIns, (char*)IDC_CURSOR1); // ���ڹ����
	wc.hIcon = LoadIcon(hIns, (char*)IDI_ICON1); // ����ͼ����
	wc.hInstance = hIns; // ��ǰģ���ʵ�����
	wc.lpfnWndProc = WndProc; // ���ڴ�����
	wc.lpszClassName = "Main"; // �����������
	wc.lpszMenuName = (char*)IDR_MENU1; // ���ڲ˵�����ԴID�ַ���
	wc.style = CS_HREDRAW | CS_VREDRAW; // ������ķ��
	RegisterClass(&wc); // ���������и�ֵȫ��д�����ϵͳ(ע�ᴰ���࣬ע��ɹ��󣬷���һ�����ֱ�ʶ)

	char szTitle[256] = { 0 };
	LoadString(hIns, IDS_WND, szTitle, 256);

	// ���ڴ��д�������
	HWND hWnd = CreateWindow("Main", szTitle, WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	// ��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// ��ȡ���ټ�����
	HACCEL hAccel = LoadAccelerators(hIns, (char*)IDR_ACCELERATOR1);

	// ��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &nMsg))
		{
			// ������Ϣ����������Ϣ������ַ���Ϣ
			TranslateMessage(&nMsg);
			// �ɷ���Ϣ
			DispatchMessage(&nMsg); // ����Ϣ�������ڴ�����������
		};
	}
	return 0;
}