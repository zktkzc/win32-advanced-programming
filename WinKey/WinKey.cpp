#include<windows.h>
#include<stdio.h>

HANDLE g_hOutput = 0;

void OnKeyDown(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_KEYDOWN：键码值=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnKeyUp(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_KEYUP：键码值=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnChar(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_CHAR：wParam=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

// 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_CHAR:
		OnChar(hWnd, wParam);
		break;
	case WM_KEYDOWN:
		OnKeyDown(hWnd, wParam);
		break;
	case WM_KEYUP:
		OnKeyUp(hWnd, wParam);
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
	AllocConsole();
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// 注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0; // 窗口类的附加数据buff的大小
	wc.cbWndExtra = 0; // 窗口的附加数据buff的大小
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 窗口背景色句柄
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