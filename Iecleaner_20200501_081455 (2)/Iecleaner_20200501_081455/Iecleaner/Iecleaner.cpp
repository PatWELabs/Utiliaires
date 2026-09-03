//IeCleaner.cpp

#define IDT_TIMER1 0x1000
#define appName "Nettoyeur IExplorer"

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shlobj.h>
#include <shellapi.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <direct.h>
#include <stdlib.h>
#include <string.h>
#include <commctrl.h>
#include <shlwapi.h>
#include <Wininet.h>
#include <fstream.h>
#include <process.h>
#include "winsock.h"
#include "resource.h"

#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"Wininet.lib")
#pragma comment(lib,"WS2_32.lib")
#pragma comment (lib,"shlwapi.lib")

/*
extern "C" {
 #define SPECSTRINGIZE( x ) #x
__declspec(dllimport) BOOL __stdcall DetectAutoProxyUrl(LPSTR lpszAutoProxyUrl,DWORD dwAutoProxyUrlLength,DWORD dwDetectFlags );
__declspec(dllimport) DWORD __stdcall InternetDialA(HWND hwndParent,LPSTR lpszConnectoid,DWORD dwFlags, DWORD *lpdwConnection,DWORD dwReserved );
__declspec(dllimport) DWORD __stdcall InternetDial(HWND hwndParent,LPSTR lpszConnectoid,DWORD dwFlags, LPDWORD lpdwConnection,DWORD dwReserved);
__declspec(dllimport) BOOL __stdcall InternetGoOnlineA(LPSTR lpszURL,HWND hwndParent,DWORD dwFlags);
__declspec(dllimport) BOOL __stdcall InternetGoOnline(LPSTR lpszURL,HWND hwndParent, DWORD dwFlags);
#define InternetDial InternetDialA
#define InternetGoOnline InternetGoOnlineA
}*/
HICON hIcon,sIcon;
NOTIFYICONDATAA sicon;
RECT rc,rect;
INITCOMMONCONTROLSEX iccex; 
TOOLINFO ti;
HWND hwndTT,hmain,hTT,hWnd;
SYSTEMTIME lp;
WNDCLASS wc;
DWORD dwEntrySize;
LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry;
DWORD MAX_CACHE_ENTRY_INFO_SIZE=4096;
HANDLE hCacheDir;
char buffer[MAX_PATH];

static BOOL CALLBACK DialogFunc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
VOID CreateMyTooltip (HWND hDlg,LPCTSTR ToolTipTitre);
VOID ActiveToolTips();
VOID ByeBye();
VOID InitIconTray();
VOID DisplayCurrentTimeSroll();
BOOL IsConnected();
VOID ConnectToInternet();
VOID ByeBye();
static int InitializeApp(HWND hDlg,WPARAM wParam, LPARAM lParam);
int scanneIECache(HWND hWnd);
//HRESULT SHAutoComplete(HWND hwndEdit,     DWORD dwFlags );

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpCmdLine, int nCmdShow){
	hIcon=LoadIcon(hinst,(LPCTSTR)IDI_ICON1);
	sIcon=LoadIcon(hinst,(LPCTSTR)IDI_ICON1);
	InitCommonControls();
	memset(&wc,0,sizeof(wc));
	wc.lpfnWndProc = DefDlgProc;
	wc.cbWndExtra = DLGWINDOWEXTRA;
	wc.hInstance = hinst;
	wc.lpszClassName = "Nettoyeur_IExplorer";
	wc.hIcon=hIcon;
	wc.hbrBackground=(HBRUSH) CreateSolidBrush(RGB(0xC0,0xC0,0xFF));
	wc.hCursor=LoadCursor(hinst,(LPCTSTR)IDC_POINTER);
	wc.style = CS_VREDRAW  | CS_HREDRAW | CS_SAVEBITS | CS_DBLCLKS; 
	RegisterClass(&wc);
return DialogBox(hinst, (LPCTSTR)IDD_FORMVIEW, NULL, (DLGPROC) DialogFunc);
}
static int InitializeApp(HWND hDlg,WPARAM wParam, LPARAM lParam){ 
	hWnd=hDlg;
	HMENU menu=GetSystemMenu(hDlg,FALSE);
	RemoveMenu(menu,SC_CLOSE,MF_STRING);
	GetWindowRect(hDlg,&rc);
	InitIconTray();
	SetTimer(hDlg,IDT_TIMER1,1000,(TIMERPROC) NULL);
	GetClientRect(GetDesktopWindow(),&rc);				
	SetWindowText(hDlg,"Nettoyeur Internet Explorer");
	ActiveToolTips();
	return 1;
}
static BOOL CALLBACK DialogFunc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam){
switch (msg) {
	return 1;
	case WM_INITDIALOG:
			InitializeApp(hDlg,wParam,lParam);
			if(IsConnected()!=TRUE){
				SetDlgItemText(hDlg,ID_CONNEXION,"Connecté à Internet");
			}else{
				SetDlgItemText(hDlg,ID_CONNEXION,"Requière une connexion à Internet");
			}
			return TRUE;
   		case WM_COMMAND:
		switch (LOWORD(wParam)) {
			case ID_CONNEXION_CMD:
				scanneIECache(hDlg);
				break;
			case IDCANCEL: // Bye Bye
				ByeBye();
				return 1;
		}
		break;
        case WM_DESTROY: 
			ByeBye();
            break; 
 		case WM_CTLCOLORDLG:
			return (long)wc.hbrBackground;
			break;
		case WM_CTLCOLORSCROLLBAR:
			SetTextColor( (HDC)wParam, RGB(0xFF, 0x00,0xFF) );
			SetBkMode( (HDC)wParam, TRANSPARENT ); 
		return (LONG)wc.hbrBackground;
		case WM_CTLCOLORSTATIC:
			SetTextColor( (HDC)wParam, RGB(0xFF, 0x00,0xFF) );
			SetBkMode( (HDC)wParam, TRANSPARENT ); 
		return (LONG)wc.hbrBackground;
		case WM_CTLCOLORLISTBOX:
			SetTextColor( (HDC)wParam, RGB(0xFF,0xFF, 0x00) );
			SetBkMode( (HDC)wParam, TRANSPARENT ); 
		return (LONG)wc.hbrBackground;
		case WM_TIMER:
			char buftime[12];
			GetLocalTime(&lp);
			sprintf(buftime,"%.2d:%.2d:%.2d ",lp.wHour,lp.wMinute,lp.wSecond);
			SetDlgItemText(hDlg,ID_TIME, buftime);
			DisplayCurrentTimeSroll();
			return TRUE;
		case WM_CLOSE:
			ByeBye();
			return TRUE;
}
return FALSE;
}
VOID InitIconTray(){ 
	sicon.cbSize=sizeof(sicon); 
	sicon.hIcon=sIcon; 
	sicon.hWnd=hWnd; 
	sicon.uFlags=NIF_MESSAGE|NIF_ICON; 
	Shell_NotifyIcon(NIM_ADD,&sicon); 
}

VOID CreateMyTooltip (HWND hDlg,LPCTSTR ToolTipTitre){
    unsigned int uid = 0;//création du tooltip
    iccex.dwICC = ICC_WIN95_CLASSES|ICC_ANIMATE_CLASS|ICC_TAB_CLASSES;
    iccex.dwSize = sizeof(iccex);
    InitCommonControlsEx(&iccex);
    hwndTT = CreateWindowEx(WS_EX_TOPMOST,TOOLTIPS_CLASS,NULL,WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP|0x40,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,hWnd,NULL,wc.hInstance,NULL);
    SetWindowPos(hwndTT,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    GetClientRect (hWnd, &rect);
    ti.cbSize = sizeof(ti);
    ti.uFlags = TTF_SUBCLASS;
    ti.hwnd = hDlg;
    ti.hinst = wc.hInstance;
    ti.uId = uid;
    ti.lpszText =(char*) ToolTipTitre;
    ti.rect.left = rect.left;    
    ti.rect.top = rect.top;
    ti.rect.right = rect.right;
    ti.rect.bottom = rect.bottom;
	rc.left= ti.rect.left+3;    
    rc.top=ti.rect.top ;
    rc.right =40;
    rc.bottom = 20 ;
    SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);	
    SendMessage(hwndTT, TTM_SETTIPTEXTCOLOR, (WPARAM) RGB(0,255,0),0);  
    SendMessage(hwndTT, WM_SETFONT, (WPARAM)GetStockObject(0x0E), MAKELPARAM(TRUE, 0));
    SendMessage(hwndTT, 0x420,  (WPARAM) (int) 1, (LPARAM)(LPCTSTR) appName);  
    SendMessage(hwndTT, TTM_SETTIPBKCOLOR,(WPARAM)RGB(204,100,204),0 );
    SendMessage(hwndTT, 0x200B,0,(LPARAM) (LPWSTR) "BUTTON");  
    SendMessage(hwndTT,TTM_SETMARGIN,0,(LPARAM)(LPRECT) &rc);  
} 

VOID ActiveToolTips(){
	//sprintf(buffer,"Quick Norton v:3.72 édition WindowsXP\n\r(C)opyright Patrice Waechter-Ebling 2000-2005\n\r%s\n\r%s",GetOwner(),GetTodayDate());
	CreateMyTooltip (hWnd,buffer);
	CreateMyTooltip (GetDlgItem(hWnd,2),"Met fin à ce programme");
	CreateMyTooltip (GetDlgItem(hWnd,ID_ABOUT),"Affiche les informations sur ce programme");
	CreateMyTooltip (GetDlgItem(hWnd,IDC_LIST1),"Conteneur de fichiers");

}

VOID DisplayCurrentTimeSroll(){
	GetLocalTime(&lp);
	DWORD d=lp.wHour*3600+lp.wMinute*60+lp.wSecond;
	SendMessage(GetDlgItem(hWnd,IDC_SCROLLBAR1), SBM_SETRANGE, (WPARAM)0x00,(LPARAM) 0x15180); 
	SendMessage(GetDlgItem(hWnd,IDC_SCROLLBAR1), SBM_SETPOS,(WPARAM)d,(LPARAM)TRUE);  
}
BOOL IsConnected(){
    if(InternetCheckConnection("http:cyber.virus.free.fr/getdynHost.php", FLAG_ICC_FORCE_CONNECTION, 0) == 0){
    return FALSE;
    }
	return TRUE;
}

VOID ByeBye(){
	KillTimer(hWnd, IDT_TIMER1); 
	Shell_NotifyIcon(NIM_DELETE,&sicon); 
	EndDialog(hWnd,0); 
}

int scanneIECache(HWND hWnd){
    int nCount=0;
    SendDlgItemMessage(hWnd,IDC_LIST1,LB_RESETCONTENT,0,0);
    SetCursor(LoadCursor(NULL,IDC_WAIT));
    dwEntrySize = MAX_CACHE_ENTRY_INFO_SIZE;
    lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
    lpCacheEntry->dwStructSize = dwEntrySize;
again:
    if (!(hCacheDir = FindFirstUrlCacheEntry(NULL,lpCacheEntry,&dwEntrySize)))   {
        delete[]lpCacheEntry;
        switch(GetLastError()){
            case ERROR_NO_MORE_ITEMS: 
                char tempout[80];
                sprintf(tempout,"The number of cache entries = %d \n",nCount);
                MessageBox(hWnd,tempout,"Cache Enumeration",MB_OK);
                FindCloseUrlCache(hCacheDir);
                SetCursor(LoadCursor(NULL,IDC_ARROW));
                return TRUE;
                break;
            case ERROR_INSUFFICIENT_BUFFER:
                lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO)  new char[dwEntrySize];
                lpCacheEntry->dwStructSize = dwEntrySize;
                goto again;
                break;
            default:
                MessageBox(hWnd,"Erreur","FindNextUrlCacheEntry Init",0);
                FindCloseUrlCache(hCacheDir);
                SetCursor(LoadCursor(NULL,IDC_ARROW));
                return FALSE;
        }
    }
		nCount++;
        delete (lpCacheEntry);
        do {
           dwEntrySize = MAX_CACHE_ENTRY_INFO_SIZE;
           lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
           lpCacheEntry->dwStructSize = dwEntrySize;
retry:
            if (!FindNextUrlCacheEntry(hCacheDir,lpCacheEntry, &dwEntrySize))  {
                delete[]lpCacheEntry;
                switch(GetLastError()) {
                      case ERROR_NO_MORE_ITEMS: 
                           char tempout[80];
							sprintf(tempout,"%d \n",nCount);
                            SetDlgItemText(hWnd,IDC_RECEPTION,tempout);
                            FindCloseUrlCache(hCacheDir);
                            return TRUE;
                            break;
                     case ERROR_INSUFFICIENT_BUFFER:
                           lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
                           lpCacheEntry->dwStructSize = dwEntrySize;
                           goto retry;
                           break;
                      default:
                           MessageBox(hWnd,"Erreur","FindNextUrlCacheEntry Init",0);
                           FindCloseUrlCache(hCacheDir);
                           return FALSE;
                        }
                }
			GetShortPathName(lpCacheEntry->lpszLocalFileName,buffer,256);
			SetDlgItemText(hWnd,ID_CONNEXION,lpCacheEntry->lpszLocalFileName);
			SetDlgItemText(hWnd,ID_DESCRIPTION2,lpCacheEntry->lpszSourceUrlName);
			SetDlgItemText(hWnd,IDC_STATUT,buffer);
            SetDlgItemInt(hWnd,IDC_RECEPTION,nCount,FALSE);
			nCount++;
            delete[] lpCacheEntry;        
        }
        while (TRUE);
        SetCursor(LoadCursor(NULL,IDC_ARROW));
        return TRUE;        
}

