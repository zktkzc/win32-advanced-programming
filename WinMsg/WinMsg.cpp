#include<windows.h>
#include<stdio.h>

HANDLE g_hOutput = 0; // 接收标准输出句柄

#define WM_MYMESSAGE WM_USER+1001

void OnCreate(HWND hWnd, LPARAM lParam)
{
	CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
	char* pszText = (char*)pcs->lpCreateParams;
	MessageBox(NULL, pszText, "Infor", MB_OK);
	PostMessage(hWnd, WM_MYMESSAGE, 1, 2);
	CreateWindowEx(0, "EDIT", "hello", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, 200, 200, hWnd, NULL, 0, NULL);
}

void OnSize(HWND hWnd, LPARAM lParam)
{
	short nWidth = LOWORD(lParam);
	short nHignt = HIWORD(lParam);
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_SIZE : 宽：%d, 高：%d\n", nWidth, nHignt);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnMyMessage(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "自定义消息被处理：wParam=%d,lParam=%d\n", wParam, lParam);
	MessageBox(hWnd, szText, "Infor", MB_OK);
}

// 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_MYMESSAGE:
		OnMyMessage(hWnd, wParam, lParam);
		break;
	case WM_SIZE: // 窗口大小发生改变
		OnSize(hWnd, lParam);
		break;
	case WM_CREATE: // 窗口创建之后，显示之前
		OnCreate(hWnd, lParam);
		break;
	case WM_DESTROY: // 窗口销毁
		//PostQuitMessage(0); // 可以使GetMessage函数返回0
		PostMessage(hWnd, WM_QUIT, 0, 0);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			int nRet = MessageBox(hWnd, "是否退出", "Infor", MB_YESNO);
			if (nRet == IDYES)
			{
				// 什么都不写
			}
			else
			{
				return 0;
			}
		}
		break;
	}

	return DefWindowProc(hWnd, msgID, wParam, lParam); // 给各种消息做默认处理
}

// 入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR IpCmdLine, int nCmdShow)
{

	AllocConsole(); // 增加DOS窗口
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出句柄

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
	char* pszText = (char*)"hello data";
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, pszText);

	// 显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// 消息循环
	MSG nMsg = { 0 };
	/*while (GetMessage(&nMsg, NULL, 0, 0))
	{
		// 翻译消息，将键盘消息翻译成字符消息
		TranslateMessage(&nMsg);
		// 派发消息
		DispatchMessage(&nMsg); // 将消息交给窗口处理函数来处理
	}*/
	while (1)
	{
		if (PeekMessage(&nMsg, NULL, 0, 0, PM_NOREMOVE))
		{
			// 有消息
			if (GetMessage(&nMsg, NULL, 0, 0))
			{
				// 翻译消息，将键盘消息翻译成字符消息
				TranslateMessage(&nMsg);
				// 派发消息
				DispatchMessage(&nMsg); // 将消息交给窗口处理函数来处理
			}
			else
			{
				return 0;
			}
		}
		else
		{
			// 没消息，空闲处理
			WriteConsole(g_hOutput, "OnIdle", strlen("OnIdle"), NULL, NULL);
		}
	}
	return 0;
}