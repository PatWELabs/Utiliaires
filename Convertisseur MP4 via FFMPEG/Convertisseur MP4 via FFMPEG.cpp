char szClassName[ ] = ""; 
#define AppName "Convertisseur MP4 via FFMPEG"
#define WINVER				0x0501		// Attribuez la valeur appropriée à cet élément pour cibler Windows 98 et Windows 2000 ou version ultérieure.
#define _WIN32_WINNT		0x0501		// Attribuez la valeur appropriée à cet élément pour cibler Windows 98 et Windows 2000 ou version ultérieure.
#define _WIN32_WINDOWS		0x0510 // Attribuez la valeur appropriée à cet élément pour cibler Windows Me ou version ultérieure.
#define _WIN32_IE			0x0600	// Attribuez la valeur appropriée à cet élément pour cibler IE 5.0 ou version ultérieure.
#define MAX_PATH			260
#define BUFSIZE				65536 
#define LookTimer			0x01000
#define MNS_NOCHECK         0x80000000
#define MNS_MODELESS        0x40000000
#define MNS_DRAGDROP        0x20000000
#define MNS_AUTODISMISS     0x10000000
#define MNS_NOTIFYBYPOS     0x08000000
#define MNS_CHECKORBMP      0x04000000
#define MIM_MAXHEIGHT       0x00000001
#define MIM_BACKGROUND      0x00000002
#define MIM_HELPID          0x00000004
#define MIM_MENUDATA        0x00000008
#define MIM_STYLE           0x00000010
#define MIM_APPLYTOSUBMENUS 0x80000000
#define ID_APP_ABOUT        0xE140


#pragma comment(lib,"User32.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"Lz32.lib")
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"wininet.lib")

#include <windows.h>
#include <windowsx.h>
#include <Winbase.h>
#include <Winuser.h>
#include <stdlib.h> 
#include <tchar.h> 
#include <stdio.h>
#include <string.h>
#include <commctrl.h>
#include <shlobj.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <Lzexpand.h>
#include <assert.h> 
#include <Commdlg.h>
#include <conio.h>
#include <crtdbg.h>
#include <direct.h>
#include <exdisp.h>
#include <mshtml.h>
#include <mshtmhst.h>
#include <process.h>
#include <Wininet.h>
#include <shellapi.h>
#include <tlhelp32.h>
#include <vdmdbg.h>
#include <time.h>
#include "resource.h"

typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
char *jours[7] = {"dimanche", "lundi","mardi","mercredi","jeudi","vendredi","samedi"};
char *mois[12] = {"janvier", "février","mars", "avril", "mai", "juin","juillet","aout","septembre", "octobre", "novembre", "décembre"};

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgMainProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

INITCOMMONCONTROLSEX iccex; 
WNDCLASSEX wcex;

LRESULT CALLBACK DlgMainProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SYSTEMTIME st;
	char Temporaire[256];
	switch (msg)
	{
		case WM_INITDIALOG:{
			SetClassLong(hDlg, GCL_HICON, (long)wcex.hIcon);
			SetWindowText(hDlg,AppName);
			iccex.dwICC = ICC_LISTVIEW_CLASSES|ICC_TREEVIEW_CLASSES|ICC_BAR_CLASSES|ICC_TAB_CLASSES|ICC_UPDOWN_CLASS|ICC_PROGRESS_CLASS|ICC_WIN95_CLASSES|ICC_DATE_CLASSES|ICC_COOL_CLASSES|ICC_INTERNET_CLASSES|ICC_PAGESCROLLER_CLASS|ICC_STANDARD_CLASSES|ICC_LINK_CLASS;
			iccex.dwSize = sizeof(iccex);
			InitCommonControlsEx(&iccex);
			CreateStatusWindow(WS_CHILD|WS_VISIBLE,__argv[0],hDlg,6000);
			GetLocalTime(&st);
			wsprintf(Temporaire,"Démarrage le %.2d-%.2d-%.4d à %.2d:%.2d:%.2d",st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond);
			SetTimer(hDlg,LookTimer,1000,(TIMERPROC) NULL);
			DWORD cmp=80;
			GetComputerName(Temporaire,&cmp);
			SetDlgItemText(hDlg,6000,Temporaire);
			break;
		}
	case WM_DROPFILES:	{ 
		HDROP hDropInfo=(HDROP) wParam; 
		int nb,taille,i; 
		taille=0; 
		nb=0; 
		nb=DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0 ); 
		char fic[500]; 
		for( i = 0; i < nb; i++ ) 	{ 
			taille=DragQueryFile(hDropInfo, i, NULL, 0 )+1; 
			DragQueryFile(hDropInfo, i, fic, taille ); 
			SendMessage(GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING, 0,(LPARAM)fic);
		} 
		DragFinish(hDropInfo);
	}	break; 

		case WM_TIMER:{
			SYSTEMTIME st;
			GetLocalTime(&st);
			wsprintf(Temporaire,"Nous sommes %s, le %2d %s %4d , il est %.2d:%.2d:%.2d",jours[st.wDayOfWeek],st.wDay,mois[st.wMonth-1],st.wYear,st.wHour,st.wMinute,st.wSecond);
			SetDlgItemText(hDlg,6000,Temporaire);
					  }break;
		case WM_COMMAND:
		{

			switch (LOWORD(wParam))
			{
				case IDOK:{ 
					char tmp[512];
					char tmp2[512];
					char tmp1[1024];
					for(int x=0; x<SendMessage(GetDlgItem(hDlg,IDC_LIST1),LB_GETCOUNT,0,0); x++){
						SendDlgItemMessage(hDlg,IDC_LIST1,LB_GETTEXT,(WPARAM)x,(LPARAM)tmp);
						SendDlgItemMessage(hDlg,IDC_LIST1,LB_GETTEXT,(WPARAM)x,(LPARAM)tmp2);
						PathRenameExtension(tmp2,".mp4");
						wsprintf(tmp1,"ffmpeg -i \"%s\" -strict experimental -c:v copy -c:a aac -b:a 128k \"%s\"",tmp,tmp2);
						system(tmp1);
					}
						  }break;
				case WM_DESTROY:
					PostQuitMessage(0);
					EndDialog(hDlg,0);
					break;
			}
			break;
		}
		case WM_CTLCOLORDLG:return (long)wcex.hbrBackground;			break;
		case WM_CTLCOLORSTATIC:	SetTextColor( (HDC)wParam, RGB(128,0,255) );SetBkMode( (HDC)wParam, TRANSPARENT ); 		return (long)wcex.hbrBackground;
		case WM_CTLCOLOREDIT:	SetTextColor( (HDC)wParam, RGB(0xA0,0xFF,0xff ) );SetBkMode( (HDC)wParam, TRANSPARENT );return (long)wcex.hbrBackground;
		case WM_CTLCOLORLISTBOX:SetTextColor( (HDC)wParam, RGB(255,0, 255) );SetBkMode( (HDC)wParam, TRANSPARENT ); 	return (long)wcex.hbrBackground;
		case WM_CTLCOLORBTN:	SetTextColor( (HDC)wParam, RGB(0,255, 255) );SetBkMode( (HDC)wParam, TRANSPARENT ); 	return (long)wcex.hbrBackground;
		case WM_CTLCOLORMSGBOX:	return (long)wcex.hbrBackground;		break;
		default: 	
			return 0;
	}
	return 1;
}
int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInst,LPSTR lpCmdLine,int nCmdShow){     
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)DlgMainProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= CreateSolidBrush(RGB(128,255,128));;
	wcex.lpszClassName	= AppName;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON1);
	RegisterClassEx(&wcex);
	DialogBoxParam(wcex.hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgMainProc,0);
    return (0);
}


