#include<windows.h>

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hWnd, &ps);
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkColor(hdc, RGB(0, 255, 0)); // ֻ������OPAQUEģʽ����͸��ģʽ��
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont(30, 0, 45, 0, 900, 1, 1, 1, GB2312_CHARSET, 0, 0, 0, 0, "����");
	HGDIOBJ nOldFont = SelectObject(hdc, hFont);

	char szText[] = "hello text";
	TextOut(hdc, 100, 100, szText, strlen(szText));
	RECT rc;
	rc.left = 100;
	rc.top = 150;
	rc.right = 200;
	rc.bottom = 200;
	//Rectangle(hdc, 100, 150, 200, 200);
	DrawText(hdc, szText, strlen(szText), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
	// DT_VCENTR/DT_BOTTOMֻ������DT_SINGLELINE����DT_WORDBREAK��ͻ

	SelectObject(hdc, nOldFont);
	DeleteObject(hFont);

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