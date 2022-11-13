#include<windows.h>
#include"resource.h"

HINSTANCE g_hInstance = 0;

void DrawBmp(HDC hdc)
{
	// ���λͼ��Դ������Ҫд���룩
	HBITMAP hBmp = LoadBitmap(g_hInstance, (char*)IDB_BITMAP1);
	HDC hMemdc = CreateCompatibleDC(hdc); // ����һ���ڴ�DC������һ���������򣬲����ڴ�DC�����������л�ͼ
	HGDIOBJ nOldBmp = SelectObject(hMemdc, hBmp); // ��λͼ�����͸��ڴ�DC���ڴ�DC�����������н�λͼ���Ƴ���
	BitBlt(hdc, 100, 100, 48, 48, hMemdc, 0, 0, SRCCOPY); // ���񣬽����������л��ƺõ�ͼ����񵽴���
	StretchBlt(hdc, 200, 200, 24, 24, hMemdc, 0, 0, 48, 48, SRCCOPY); // ���ų���
	StretchBlt(hdc, 300, 300, 96, 96, hMemdc, 0, 0, 48, 48, SRCCOPY); // ���ų���
	SelectObject(hMemdc, nOldBmp);
	DeleteObject(hBmp);
	DeleteDC(hMemdc);
}

void DrawRect(HDC hdc)
{
	Rectangle(hdc, 100, 100, 300, 300);
}

void DrawEll(HDC hdc)
{
	Ellipse(hdc, 100, 100, 300, 300);
}

void DrawLine(HDC hdc)
{
	MoveToEx(hdc, 100, 100, NULL);
	LineTo(hdc, 300, 300);
	LineTo(hdc, 0, 300);
	LineTo(hdc, 100, 100);
}

void DrawPit(HDC hdc)
{
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			SetPixel(hdc, i, j, RGB(i, j, 0));
		}
	}
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hWnd, &ps);

	HPEN hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);

	//HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
	//HBRUSH hBrush = CreateHatchBrush(HS_CROSS, RGB(0, 255, 0));
	HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
	HGDIOBJ nOldBrush = SelectObject(hdc, hBrush);

	//DrawPit(hdc); // ���Ƶ�
	//DrawLine(hdc); // ����ֱ��
	//DrawRect(hdc); // ���ƾ���
	//DrawEll(hdc); // ����Բ��
	DrawBmp(hdc); // ����λͼ

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);

	SelectObject(hdc, nOldBrush);
	//DeleteObject(hBrush);

	EndPaint(hWnd, &ps);
}

// ���ڴ��������Զ��壬������Ϣ��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_PAINT:
		OnPaint(hWnd);
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3); // ���ڱ���ɫ���
	wc.hCursor = NULL; // ���ڹ����
	wc.hIcon = NULL; // ����ͼ����
	wc.hInstance = hIns; // ��ǰģ���ʵ�����
	wc.lpfnWndProc = WndProc; // ���ڴ�����
	wc.lpszClassName = "Main"; // �����������
	wc.lpszMenuName = NULL; // ���ڲ˵�����ԴID�ַ���
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