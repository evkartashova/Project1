#include <windows.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <cmath>
const int R = 100;
const int R1 = 105;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//====================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	HWND hMainWnd;
	TCHAR   szClassName[] = _T("MyClass");
	MSG msg;
	WNDCLASSEX wc;
	// Заполняем структуру класса окна
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// Регистрируем класс окна
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, _T("Cannot register class"), _T("Error"), MB_OK);
		return 0;
	}
	// Создаем основное окно приложения
	hMainWnd = CreateWindow(szClassName, _T("Привет"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		(HWND)NULL, (HMENU)NULL,
		(HINSTANCE)hInstance, NULL
	);
	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}
	// Показывем окно
	ShowWindow(hMainWnd, nCmdShow);
	// UpdateWindow(hMainWnd); // Обновление отображения окна
	// Выполняем цикл обработки сообщения
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	static int sx, sy;
	static int a, b, x, y;
	static double angle;
	RECT rect;
	switch (uMsg)
	{
	case WM_CREATE:
			break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		a = sx / 2;
		b = sy / 2;
		x = a;
		y = b - R;
		break;
	case WM_LBUTTONDOWN:
		SetTimer(hWnd, 1, 1000, NULL);
		break;
	case WM_RBUTTONDOWN:
		KillTimer(hWnd, 1);
		a = sx / 2;
		b = sy / 2;
		x = a;
		y = b - R;
		angle = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_TIMER:
		angle += M_PI / 60;
		x = a + R * sin(angle);
		y = b - R * cos(angle);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		KillTimer(hWnd, 1);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
	//	GetClientRect(hWnd, &rect);
	//	a = sx / 2;
	//	b = sy / 2;
	//	MoveToEx(hDC, 0, b, NULL);
	//	LineTo(hDC, sx, b);
	//	MoveToEx(hDC, a, 0, NULL);
	//	LineTo(hDC, a, sy);
	//	MoveToEx(hDC, a, b, NULL); 
	//	for (angle = 0.0; angle < 2 * M_PI; angle += M_PI/60)
	//	{
	//		x = a + R * sin(angle);
	//		y = b - R * cos(angle);
			//Циклоида
		//	x = a + R * (1 - cos(angle)) * cos(angle);
		//	y = b - R * (1 - cos(angle)) * sin(angle);
		Ellipse(hDC, a-R1, b-R1, a+R1, b+R1);
		MoveToEx(hDC, a, b,NULL);
		LineTo(hDC, x, y);
			
	//	}
	//	DrawText(hDC, _T("Привет, мир"), -1, &rect,
	//		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
