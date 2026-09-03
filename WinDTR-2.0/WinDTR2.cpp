// WinDTR2.cpp : Defines the entry point for the application.
//

#include <Windows.h>
#include "resource.h"

#define MAX_LOADSTRING 100
#define IDM_TIMER1 0x01000

// Global Variables:
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
WNDCLASSEX wcex;
HWND hMain;
NOTIFYICONDATA m_niData;
static char* jours[7] = { "dimanche", "lundi","mardi","mercredi","jeudi","vendredi","samedi" };
static char* mois[12] = { "janvier", "février","mars", "avril", "mai", "juin","juillet","aout","septembre", "octobre", "novembre", "décembre" };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ResolutionDTR(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ValiderTansfoDTR(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);
int MsgBox(HWND hDlg, char* lpszText, char* lpszCaption, DWORD dwStyle, int lpszIcon);
void AfficherHeureMenu();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINDTR2, szWindowClass, MAX_LOADSTRING);
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON2);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 128, 255));
	wcex.lpszMenuName = (LPCSTR)IDC_WINDTR2;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON2);
	RegisterClassEx(&wcex);
	hMain = CreateWindowEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_CONTEXTHELP, szWindowClass, szTitle, WS_BORDER | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hMain) { return FALSE; }
	ShowWindow(hMain, nCmdShow);
	UpdateWindow(hMain);
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_WINDTR2);
	SetTimer(hMain, IDM_TIMER1, 1000, (TIMERPROC)NULL);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(wcex.hInstance, IDS_HELLO, szHello, MAX_LOADSTRING);
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:{
			DialogBox(wcex.hInstance, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			}break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_RESOLUTIONDTR:
		{
			DialogBox(wcex.hInstance, (LPCTSTR)IDD_DIALOG1, hWnd, (DLGPROC)ResolutionDTR);
		}break;
		case ID_QUALIFICATIONTRANSFOVIADTR:
		{
			DialogBox(wcex.hInstance, (LPCTSTR)IDD_DIALOG2, hWnd, (DLGPROC)ValiderTansfoDTR);
		}break;
		//
		case ID_DATE:
		{
			char buf[80];
			GetWindowText(hMain,buf, sizeof(buf));
			MsgBox(hWnd, buf, szTitle, MB_OK | MB_ICONINFORMATION, IDI_ICON2);
		}break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TIMER:
	{
		AfficherHeureMenu();
	}break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		RECT rt;
		GetClientRect(hWnd, &rt);
		DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDc = reinterpret_cast<HDC>(wParam);
	switch (message)
	{
	case WM_INITDIALOG: {
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(wcex.hInstance, (LPCSTR)IDI_ICON3));
		return TRUE;
	}
	case WM_CTLCOLOREDIT: {
		SetTextColor((HDC)wParam, RGB(0xA0, 0xFF, 0xff));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (LONG)CreateSolidBrush(RGB(255, 0, 255));
	}
	case WM_CTLCOLORLISTBOX: {
		SetTextColor((HDC)wParam, RGB(255, 0, 255));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (LONG)CreateSolidBrush(RGB(255, 0, 255));
	}
	case WM_CTLCOLORBTN: {
		SetBkMode((HDC)wParam, TRANSPARENT);
		if (GetDlgItem(hDlg, IDOK) == reinterpret_cast<HWND>(lParam)) SetTextColor(hDc, RGB(0, 255, 0));
		if (GetDlgItem(hDlg, IDCANCEL) == reinterpret_cast<HWND>(lParam)) SetTextColor(hDc, RGB(255, 0, 0));
		return (LONG)wcex.hbrBackground;
	}
	case WM_CTLCOLORMSGBOX:return (LONG)CreateSolidBrush(RGB(255, 0, 255));

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}LRESULT CALLBACK ResolutionDTR(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDc = reinterpret_cast<HDC>(wParam);	switch (message)
	{
	case WM_INITDIALOG: {
		SetWindowText(hDlg, "Calculer le ratio DTR d'un transformateur");
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(wcex.hInstance, (LPCSTR)IDI_ICON1));
		return TRUE;
	}
	case WM_CTLCOLOREDIT: {
		SetTextColor((HDC)wParam, RGB(0xA0, 0xFF, 0xff));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (LONG)CreateSolidBrush(RGB(255, 0, 255));
	}
	case WM_CTLCOLORLISTBOX: {
		SetTextColor((HDC)wParam, RGB(255, 0, 255));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (LONG)CreateSolidBrush(RGB(255, 0, 255));
	}
	case WM_CTLCOLORBTN: {
		SetBkMode((HDC)wParam, TRANSPARENT);
		if (GetDlgItem(hDlg, IDOK) == reinterpret_cast<HWND>(lParam)) SetTextColor(hDc, RGB(0, 255, 0));
		if (GetDlgItem(hDlg, IDCANCEL) == reinterpret_cast<HWND>(lParam)) SetTextColor(hDc, RGB(255, 0, 0));
		return (LONG)wcex.hbrBackground;
	}
	case WM_CTLCOLORMSGBOX:return (LONG)CreateSolidBrush(RGB(255, 0, 255));
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
LRESULT CALLBACK ValiderTansfoDTR(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDc = reinterpret_cast<HDC>(wParam);
	switch (message)
	{
	case WM_INITDIALOG: {
		SetWindowText(hDlg, "Valider Tansformateur via le control DTR");
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(wcex.hInstance, (LPCSTR)IDI_ICON4));
		return TRUE;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	case WM_CTLCOLOREDIT: {
		SetTextColor((HDC)wParam, RGB(0xA0, 0xFF, 0xff)); 
		SetBkMode((HDC)wParam, TRANSPARENT); 
		return (LONG)CreateSolidBrush(RGB(255, 0, 255)); 
	}
	case WM_CTLCOLORLISTBOX: {
		SetTextColor((HDC)wParam, RGB(255, 0, 255));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (LONG)CreateSolidBrush(RGB(255, 0, 255));
	}
	case WM_CTLCOLORBTN: {
		SetBkMode((HDC)wParam, TRANSPARENT);
		if (GetDlgItem(hDlg, IDOK) == reinterpret_cast<HWND>(lParam)) SetTextColor(hDc, RGB(0, 255, 0));
		if (GetDlgItem(hDlg, IDCANCEL) == reinterpret_cast<HWND>(lParam)) SetTextColor(hDc, RGB(255, 0, 0));
		return (LONG)wcex.hbrBackground;
	}
	case WM_CTLCOLORMSGBOX:return (LONG)CreateSolidBrush(RGB(255, 0, 255));
	}
	return FALSE;
}int MsgBox(HWND hDlg, char* lpszText, char* lpszCaption, DWORD dwStyle, int lpszIcon) {
	MSGBOXPARAMS lpmbp;
	lpmbp.hInstance = wcex.hInstance;
	lpmbp.cbSize = sizeof(MSGBOXPARAMS);
	lpmbp.hwndOwner = hDlg;
	lpmbp.dwLanguageId = MAKELANGID(0x0800, 0x0800); //par defaut celui du systeme
	lpmbp.lpszText = lpszText;
	lpmbp.lpszCaption = lpszCaption;
	lpmbp.dwStyle = dwStyle | 0x00000080L;
	lpmbp.lpszIcon = (LPCTSTR)lpszIcon;
	lpmbp.lpfnMsgBoxCallback = 0;
	return  MessageBoxIndirect(&lpmbp);
}
void AfficherHeureMenu() {
	SYSTEMTIME st;
	GetLocalTime(&st);
	CHAR buf[80];
	wsprintf(buf, "%s Nous sommes %s, le %2d %s %4d il est %.2d:%.2d:%.2d", szTitle,
		jours[st.wDayOfWeek], st.wDay, mois[st.wMonth-1], st.wYear, st.wHour, st.wMinute, st.wSecond);
	SetWindowText(hMain, buf);	
	wsprintf(buf, "%.2d:%.2d:%.2d", st.wHour, st.wMinute, st.wSecond);
	ModifyMenu(GetMenu(hMain), ID_DATE, MF_BYCOMMAND, ID_DATE, buf);


}