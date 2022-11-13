#include<windows.h>

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hWnd, &ps);
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkColor(hdc, RGB(0, 255, 0)); // 只适用于OPAQUE模式（不透明模式）
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont(30, 0, 45, 0, 900, 1, 1, 1, GB2312_CHARSET, 0, 0, 0, 0, "黑体");
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
	// DT_VCENTR/DT_BOTTOM只适用于DT_SINGLELINE，和DT_WORDBREAK冲突

	SelectObject(hdc, nOldFont);
	DeleteObject(hFont);

	EndPaint(hWnd, &ps);
}

// 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // 可以使GetMessage函数返回0
		break;
	}

	return DefWindowProc(hWnd, msgID, wParam, lParam); // 给各种消息做默认处理
}

// 入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR IpCmdLine, int nCmdShow)
{
	// 注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0; // 窗口类的附加数据buff的大小
	wc.cbWndExtra = 0; // 窗口的附加数据buff的大小
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3); // 窗口背景色句柄
	wc.hCursor = NULL; // 窗口光标句柄
	wc.hIcon = NULL; // 窗口图标句柄
	wc.hInstance = hIns; // 当前模块的实例句柄
	wc.lpfnWndProc = WndProc; // 窗口处理函数
	wc.lpszClassName = "Main"; // 窗口类的名称
	wc.lpszMenuName = NULL; // 窗口菜单的资源ID字符串
	wc.style = CS_HREDRAW | CS_VREDRAW; // 窗口类的风格
	RegisterClass(&wc); // 将以上所有赋值全部写入操作系统(注册窗口类，注册成功后，返回一个数字标识)

	// 在内存中创建窗口
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	// 显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// 消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		// 翻译消息，将键盘消息翻译成字符消息
		TranslateMessage(&nMsg);
		// 派发消息
		DispatchMessage(&nMsg); // 将消息交给窗口处理函数来处理
	}
	return 0;
}