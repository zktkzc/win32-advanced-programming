#include<windows.h>
#include"resource.h"

HINSTANCE g_hInstance = 0;

void DrawBmp(HDC hdc)
{
	// 添加位图资源（不需要写代码）
	HBITMAP hBmp = LoadBitmap(g_hInstance, (char*)IDB_BITMAP1);
	HDC hMemdc = CreateCompatibleDC(hdc); // 创建一个内存DC，构建一个虚拟区域，并且内存DC在虚拟区域中绘图
	HGDIOBJ nOldBmp = SelectObject(hMemdc, hBmp); // 将位图数据送给内存DC，内存DC在虚拟区域中将位图绘制出来
	BitBlt(hdc, 100, 100, 48, 48, hMemdc, 0, 0, SRCCOPY); // 成像，将虚拟区域中绘制好的图像成像到窗口
	StretchBlt(hdc, 200, 200, 24, 24, hMemdc, 0, 0, 48, 48, SRCCOPY); // 缩放成像
	StretchBlt(hdc, 300, 300, 96, 96, hMemdc, 0, 0, 48, 48, SRCCOPY); // 缩放成像
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

	//DrawPit(hdc); // 绘制点
	//DrawLine(hdc); // 绘制直线
	//DrawRect(hdc); // 绘制矩形
	//DrawEll(hdc); // 绘制圆形
	DrawBmp(hdc); // 绘制位图

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);

	SelectObject(hdc, nOldBrush);
	//DeleteObject(hBrush);

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

	g_hInstance = hIns;

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