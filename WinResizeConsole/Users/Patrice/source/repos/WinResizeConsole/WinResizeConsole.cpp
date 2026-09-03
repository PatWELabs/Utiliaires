//WinResizeConsole
#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <commctrl.h>
#include "Resource.h"

#pragma comment(lib, "comctl32.lib")

HINSTANCE hInst;
HANDLE hStdout, hStdin;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
RECT rc;
int x=160;
int y=80;

void CreerConsole();
void NewLine(void); 
void ScrollScreenBuffer(HANDLE, INT); 
//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam){
	switch(Msg)	{
		case WM_INITDIALOG:
			SendMessage(hDlg, WM_SETICON, 1, (LPARAM)LoadIcon(hInst,(LPCTSTR)IDI_ICON1));
			x=rc.right/8;
			y=rc.bottom/12;
			SendMessage(GetDlgItem(hDlg,IDC_PROGRESS1), PBM_SETRANGE, 0, MAKELPARAM(0,x));
			SendMessage(GetDlgItem(hDlg,IDC_PROGRESS1), PBM_SETSTEP, (WPARAM) 1, 0); 
			SendMessage(GetDlgItem(hDlg,IDC_PROGRESS2), PBM_SETRANGE, 0, MAKELPARAM(0, y));
			SendMessage(GetDlgItem(hDlg,IDC_SLIDER1), TBM_SETRANGE, 0, MAKELPARAM(0, x));
			SendMessage(GetDlgItem(hDlg,IDC_SLIDER2), TBM_SETRANGE, 0, MAKELPARAM(0, y));
			SendMessage(GetDlgItem(hDlg,IDC_PROGRESS2), PBM_SETSTEP, (WPARAM) 1, 0); 
			SetDlgItemInt(hDlg,IDC_MAXCOL,x,0);
			SetDlgItemInt(hDlg,IDC_MAXCOL2,y,0);
			SendMessage(GetDlgItem(hDlg,IDC_PROGRESS1), PBM_SETPOS , (WPARAM)x/2, 0); 
			SendMessage(GetDlgItem(hDlg,IDC_PROGRESS2),PBM_SETPOS  , (WPARAM)y/2, 0); 
			SendMessage(GetDlgItem(hDlg,IDC_SLIDER1), SBM_SETPOS , 0, (LPARAM)x/2); 
			SendMessage(GetDlgItem(hDlg,IDC_SLIDER2),SBM_SETPOS, 0  , (LPARAM)y/2); 
			return TRUE;
		case WM_HSCROLL:{
			x= SendMessage(GetDlgItem(hDlg,IDC_SLIDER1), TBM_GETPOS ,0, 0); 
			SendMessage(GetDlgItem(hDlg,IDC_PROGRESS1), PBM_SETPOS , (WPARAM)x, 0); 
			y= SendMessage(GetDlgItem(hDlg,IDC_SLIDER2), TBM_GETPOS ,0, 0); 
			SendMessage(GetDlgItem(hDlg,IDC_PROGRESS2), PBM_SETPOS , (WPARAM)y, 0); 
			SetDlgItemInt(hDlg,IDC_MAXCOL,x,0);
			SetDlgItemInt(hDlg,IDC_MAXCOL2,y,0);
			  }break;
		case WM_COMMAND:
			switch(wParam)		{
			case IDOK:{
				CreerConsole();
				}return TRUE;
			}
			case IDCANCEL:	return EndDialog(hDlg, 0);
		}
	return FALSE;
}
void NewLine(void) { 
    if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo))     {        MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"),TEXT("Console Error"), MB_OK);         return;    }
    csbiInfo.dwCursorPosition.X = 0; 
    if ((csbiInfo.dwSize.Y-1) == csbiInfo.dwCursorPosition.Y) {         ScrollScreenBuffer(hStdout, 1);     } 
    else csbiInfo.dwCursorPosition.Y += 1; 
    if (! SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition))     {        MessageBox(NULL, TEXT("SetConsoleCursorPosition"),             TEXT("Console Error"), MB_OK);         return;}
} 

void ScrollScreenBuffer(HANDLE h, INT x){
    SMALL_RECT srctScrollRect, srctClipRect;
    CHAR_INFO chiFill;
    COORD coordDest;
    srctScrollRect.Left = 0;
    srctScrollRect.Top = 1;
    srctScrollRect.Right = csbiInfo.dwSize.X - (SHORT)x; 
    srctScrollRect.Bottom = csbiInfo.dwSize.Y - (SHORT)x; 
    coordDest.X = 0; 
    coordDest.Y = 0; 
    srctClipRect = srctScrollRect; 
    chiFill.Attributes = FOREGROUND_RED|FOREGROUND_INTENSITY; 
    chiFill.Char.AsciiChar = (char)' '; 
	ScrollConsoleScreenBuffer( h,&srctScrollRect,&srctClipRect,coordDest,&chiFill);
}
void CreerConsole(){
	SECURITY_ATTRIBUTES sa;
	char comm[80];
	DWORD lpNumberOfCharsWritten;
	AllocConsole();
	sa.nLength=sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle=1;
	sa.lpSecurityDescriptor=0;
	HANDLE ccscb=CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,&sa,CONSOLE_TEXTMODE_BUFFER,0);
	SetConsoleTitle("Consolle parameter override");
	wsprintf(comm,"mode con: cols=%d lines=%d\n cmd.exe",x,y); 
	WriteConsole(ccscb,comm,strlen(comm),&lpNumberOfCharsWritten,0);
	FreeConsole();
	system(comm);
}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
	GetClientRect(GetDesktopWindow(),&rc);
	hInst=hInstance;
	InitCommonControls();
	DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, GetDesktopWindow(), (DLGPROC) DlgProc);

    return 0;
}