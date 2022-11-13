#include<windows.h>

// 入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR IpCmdLine, int nCmdShow)
{
	// 在内存中创建窗口
	//HWND hWnd = CreateWindow("Button", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	HWND hWnd = CreateWindow("Edit", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	// 显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// 消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		// 翻译消息
		TranslateMessage(&nMsg);
		// 派发消息
		DispatchMessage(&nMsg); // 将消息交给窗口处理函数来处理
	}
	return 0;
}