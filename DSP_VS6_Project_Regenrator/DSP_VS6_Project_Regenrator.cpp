// DSP_VS6_Project_Regenrator.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
WNDCLASSEX wcex;
HWND hWnd;
HACCEL hAccelTable;
FILE *f;
	char szPath[MAX_PATH + 1];

LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT __stdcall About(HWND, UINT, WPARAM, LPARAM);
LRESULT __stdcall Wizzard(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int __stdcall BrowseForFolderCallback(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData);
void CreerProjet(char* titre,char* fichier);
void ListerRepFile(char* CurrentDir);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR     lpCmdLine,int       nCmdShow){
	MSG msg;
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DSP_VS6_PROJECT_REGENRATOR, szWindowClass, MAX_LOADSTRING);
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DSP_VS6_PROJECT_REGENRATOR);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)CreateSolidBrush(RGB(128,128,128));
	wcex.lpszMenuName	= (LPCSTR)IDC_DSP_VS6_PROJECT_REGENRATOR;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= wcex.hIcon;
	RegisterClassEx(&wcex);


   hInst = hInstance;

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DSP_VS6_PROJECT_REGENRATOR);

	DialogBox(hInst, (LPCTSTR)IDD_DIALOGMAIN, hWnd, (DLGPROC)Wizzard);//			  
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return  msg.wParam;
}

LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
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

LRESULT __stdcall Wizzard(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	hWnd=hDlg;
	HDC hDc=reinterpret_cast<HDC>(wParam); 
	LPDRAWITEMSTRUCT lpdis;
	switch (message){
		case WM_DRAWITEM:{
			lpdis = (LPDRAWITEMSTRUCT) lParam;
			SetTextColor(lpdis->hDC, RGB(200,200,200)); 
			SetBkColor(lpdis->hDC, RGB(0,200,200)); 
			}return TRUE; 
		case WM_INITDIALOG:
			CreateStatusWindow(WS_CHILD|WS_VISIBLE,szTitle,hDlg,6000);
				return TRUE;
		case WM_CTLCOLORMSGBOX:{
			SetBkMode( (HDC)lParam, TRANSPARENT ); 
			SetTextColor(hDc, RGB(0, 255, 0)); 
							}return (LONG)CreateSolidBrush(RGB(128,128,128));
		case WM_CTLCOLORSTATIC:{SetBkMode( (HDC)wParam, TRANSPARENT );
			SetTextColor( (HDC)wParam, RGB(0xA0,0xFF,0xff ) ); 
			if (GetDlgItem(hDlg, IDC_PATH) == reinterpret_cast<HWND>(lParam)){ SetTextColor(hDc, RGB(0, 255, 0));}
			SetBkMode( (HDC)wParam, TRANSPARENT );
							   }return (LONG)CreateSolidBrush(RGB(128,128,128));
		case WM_CTLCOLOREDIT:SetTextColor( (HDC)wParam, RGB(0xA0,0xFF,0xff ) );SetBkMode( (HDC)wParam, TRANSPARENT ); return (LONG)CreateSolidBrush(RGB(128,128,128));
		case WM_CTLCOLORLISTBOX:SetTextColor( (HDC)wParam, RGB(255,0, 255) );SetBkMode( (HDC)wParam, TRANSPARENT ); return (LONG)CreateSolidBrush(RGB(128,128,128));
		case WM_CTLCOLORBTN:{
			SetBkMode( (HDC)lParam, TRANSPARENT ); 
				if (GetDlgItem(hDlg, IDOK) == reinterpret_cast<HWND>(lParam)) SetTextColor(hDc, RGB(0, 255, 0)); 
				if (GetDlgItem(hDlg, IDCANCEL) == reinterpret_cast<HWND>(lParam)) SetTextColor(hDc, RGB(255, 0, 0)); 
			return (LONG)CreateSolidBrush(RGB(128,128,128));
							}

		case WM_COMMAND:
			switch (LOWORD(wParam)){
				case IDC_BUTTON1:{
						SendMessage(GetDlgItem(hDlg,IDC_LIST1),LB_RESETCONTENT, 0,0);
						BROWSEINFO bi;
						LPSTR lpszFolder;
						LPITEMIDLIST pidl;
						BOOL bResult = FALSE;
						LPMALLOC pMalloc;
						if (SUCCEEDED(SHGetMalloc(&pMalloc))) 					{
							bi.hwndOwner = hDlg;
							bi.pidlRoot = NULL;
							bi.pszDisplayName = NULL;
							bi.lpszTitle = "Sélectionnez le dossier contenant les fichiers du projet á générer";
							bi.ulFlags = BIF_STATUSTEXT; // 
							bi.lpfn = BrowseForFolderCallback;
							bi.lParam = (LPARAM)lpszFolder;
							pidl = SHBrowseForFolder(&bi);
							if (pidl){if (SHGetPathFromIDList(pidl,szPath)) {bResult = TRUE;	SetDlgItemText(hDlg,IDC_PATH, szPath);}
							pMalloc->Free(pidl);
							pMalloc->Release();}
							SetDlgItemText(hDlg,IDC_EDIT1,PathFindFileName(szPath));
							ListerRepFile(szPath);
							}
						}
				case IDOK:{
					char titre[80];
					char fichier[260];
					GetDlgItemText(hDlg,IDC_EDIT1,titre,sizeof(titre));
					wsprintf(fichier,"%s\\%s.dsp",szPath,titre);
			//		CreerProjet(titre,fichier);
						  } break;
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				case IDCANCEL:EndDialog(hDlg, LOWORD(wParam));return TRUE;	}
					break;
			}
    return FALSE;
}

LRESULT __stdcall About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

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
int __stdcall BrowseForFolderCallback(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData)
{
	char szPath[MAX_PATH];
		HDC hDc=reinterpret_cast<HDC>(lp); 

	switch(uMsg)
	{
		case WM_CTLCOLOREDIT:SetTextColor( (HDC)lp, RGB(0xA0,0xFF,0xff ) );SetBkMode( (HDC)lp, TRANSPARENT ); return (LONG)CreateSolidBrush(RGB(128,128,128));
		case WM_CTLCOLORLISTBOX:SetTextColor( (HDC)lp, RGB(0,255, 255) );SetBkMode( (HDC)lp, TRANSPARENT ); return (LONG)CreateSolidBrush(RGB(128,128,128));
		case WM_CTLCOLORBTN:{
			SetBkMode( (HDC)lp, TRANSPARENT ); 
				if (GetDlgItem(hwnd, IDOK) == reinterpret_cast<HWND>(pData)) SetTextColor(hDc, RGB(0, 255, 0)); 
				if (GetDlgItem(hwnd, IDCANCEL) == reinterpret_cast<HWND>(pData)) SetTextColor(hDc, RGB(255, 0, 0)); 
			return (LONG)wcex.hbrBackground;
							}
		case WM_CTLCOLORMSGBOX:return (LONG)CreateSolidBrush(RGB(128,128,128));
		case BFFM_INITIALIZED:
			SendMessage(hwnd, BFFM_SETSELECTION, TRUE, pData);
			break;

		case BFFM_SELCHANGED: 
			if (SHGetPathFromIDList((LPITEMIDLIST) lp ,szPath)) 
			{
				SendMessage(hwnd, BFFM_SETSTATUSTEXT,0,(LPARAM)szPath);	

			}
			break;
	}

	return 0;
}
void CreerProjet(char* titre,char* fichier){
char ext[4];
char entree[260];
fopen(fichier,"+rb");
	fprintf(f,"# Microsoft Developer Studio Project File - Name=\"%s\" - Package Owner=<4>\n",titre);
	fprintf(f,"# Microsoft Developer Studio Generated Build File, Format Version 6.00\n");
	fprintf(f,"# ** DO NOT EDIT **\n");
	fprintf(f,"# TARGTYPE \"Win32 (x86) Application\" 0x0101 \n");
	fprintf(f,"CFG=%s - Win32 Debug\n");
	fprintf(f,"!MESSAGE This is not a valid makefile. To build this project using NMAKE,\n");
	fprintf(f,"!MESSAGE use the Export Makefile command and run\n");
	fprintf(f,"!MESSAGE \n");
	fprintf(f,"!MESSAGE NMAKE /f \"%s.mak\"",titre);
	fprintf(f,"!MESSAGE \n");
	fprintf(f,"!MESSAGE You can specify a configuration when running NMAKE\n");
	fprintf(f,"!MESSAGE by defining the macro CFG on the command line. For example:\n");
	fprintf(f,"!MESSAGE \n");
	fprintf(f,"!MESSAGE NMAKE /f \"%s.mak\" CFG=\"ActivationVista - Win32 Debug\"\n",titre);
	fprintf(f,"!MESSAGE \n");
	fprintf(f,"!MESSAGE Possible choices for configuration are:\n");
	fprintf(f,"!MESSAGE \n");
	fprintf(f,"!MESSAGE \"%s - Win32 Release\" (based on \"Win32 (x86) Application\")\n",titre);
	fprintf(f,"!MESSAGE \"%s - Win32 Debug\" (based on \"Win32 (x86) Application\")\n",titre);
	fprintf(f,"!MESSAGE \n");
	fprintf(f,"# Begin Project\n");
	fprintf(f,"# PROP AllowPerConfigDependencies 0\n");
	fprintf(f,"# PROP Scc_ProjName \"\"\n");
	fprintf(f,"# PROP Scc_LocalPath \"\"\n");
	fprintf(f,"CPP=cl.exe\n");
	fprintf(f,"MTL=midl.exe\n");
	fprintf(f,"RSC=rc.exe\n");
	fprintf(f,"!IF  \"$(CFG)\" == \"%s - Win32 Release\"",titre);
	fprintf(f,"# PROP BASE Use_MFC 0");
	fprintf(f,"# PROP BASE Use_Debug_Libraries 0");
	fprintf(f,"# PROP BASE Output_Dir \"Release\"");
	fprintf(f,"# PROP BASE Intermediate_Dir \"Release\"");
	fprintf(f,"# PROP BASE Target_Dir \"\"");
	fprintf(f,"# PROP Use_MFC 0");
	fprintf(f,"# PROP Use_Debug_Libraries 0");
	fprintf(f,"# PROP Output_Dir \"Release\"");
	fprintf(f,"# PROP Intermediate_Dir \"Release\"");
	fprintf(f,"# PROP Target_Dir \"\"");
	fprintf(f,"# ADD BASE CPP /nologo /W3 /GX /O2 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\" /D \"_MBCS\" /Yu\"stdafx.h\" /FD /c");
	fprintf(f,"# ADD CPP /nologo /W3 /GX /O2 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\" /D \"_MBCS\" /FR /Yu\"stdafx.h\" /FD /c");
	fprintf(f,"# ADD BASE MTL /nologo /D \"NDEBUG\" /mktyplib203 /win32");
	fprintf(f,"# ADD MTL /nologo /D \"NDEBUG\" /mktyplib203 /win32");
	fprintf(f,"# ADD BASE RSC /l 0x40c /d \"NDEBUG\"");
	fprintf(f,"# ADD RSC /l 0x40c /d \"NDEBUG\"");
	fprintf(f,"BSC32=bscmake.exe");
	fprintf(f,"# ADD BASE BSC32 /nologo");
	fprintf(f,"# ADD BSC32 /nologo");
	fprintf(f,"LINK32=link.exe");
	fprintf(f,"# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386");
	fprintf(f,"# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386");
	fprintf(f,"!ELSEIF  \"$(CFG)\" == \"%s - Win32 Debug\"",titre);
	fprintf(f,"# PROP BASE Use_MFC 0");
	fprintf(f,"# PROP BASE Use_Debug_Libraries 1");
	fprintf(f,"# PROP BASE Output_Dir \"Debug\"");
	fprintf(f,"# PROP BASE Intermediate_Dir \"Debug\"");
	fprintf(f,"# PROP BASE Target_Dir \"\"");
	fprintf(f,"# PROP Use_MFC 0");
	fprintf(f,"# PROP Use_Debug_Libraries 1");
	fprintf(f,"# PROP Output_Dir \"Debug\"");
	fprintf(f,"# PROP Intermediate_Dir \"Debug\"");
	fprintf(f,"# PROP Target_Dir \"\"");
	fprintf(f,"# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D \"WIN32\" /D \"_DEBUG\" /D \"_WINDOWS\" /D \"_MBCS\" /Yu\"stdafx.h\" /FD /GZ /c");
	fprintf(f,"# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D \"WIN32\" /D \"_DEBUG\" /D \"_WINDOWS\" /D \"_MBCS\" /FR /Yu\"stdafx.h\" /FD /GZ /c");
	fprintf(f,"# ADD BASE MTL /nologo /D \"_DEBUG\" /mktyplib203 /win32");
	fprintf(f,"# ADD MTL /nologo /D \"_DEBUG\" /mktyplib203 /win32");
	fprintf(f,"# ADD BASE RSC /l 0x40c /d \"_DEBUG\"");
	fprintf(f,"# ADD RSC /l 0x40c /d \"_DEBUG\"");
	fprintf(f,"BSC32=bscmake.exe");
	fprintf(f,"# ADD BASE BSC32 /nologo");
	fprintf(f,"# ADD BSC32 /nologo");
	fprintf(f,"LINK32=link.exe");
	fprintf(f,"# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept");
	fprintf(f,"# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept");
	fprintf(f,"!ENDIF ");
	fprintf(f,"# Begin Target");
	fprintf(f,"# Name \"%s - Win32 Release\"",titre);
	fprintf(f,"# Name \"%s - Win32 Debug\"",titre);
	fprintf(f,"# Begin Group \"Source Files\"");
	fprintf(f,"# PROP Default_Filter \"cpp;c;cxx;rc;def;r;odl;idl;hpj;bat\"");
/*
/*for
strcpy(ext,PathFindExtension(entree));
fprintf(f,"# Begin Source File");

SOURCE=.\ActivationVista.cpp"); // main C++
# ADD CPP /w /W0");
# SUBTRACT CPP /YX /Yc /Yu");
# End Source File");
*/
	/* loop files
	fprintf(f,"# Begin Source File");
	fprintf(f,"SOURCE=.\%s\n",entree);//ActivationVista.def
	fprintf(f,"# End Source File");
	fprintf(f,"# Begin Source File");
	fprintf(f,"# End Source File");
	fprintf(f,"# End Group");
	// les entetes
	fprintf(f,"# Begin Group \"Header Files\"");
	fprintf(f,"# PROP Default_Filter \"h;hpp;hxx;hm;inl\"");
	fprintf(f,"# End Group");
	fprintf(f,"# Begin Group \"Resource Files\"");
	fprintf(f,"# PROP Default_Filter \"ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe\"");
	fprintf(f,"# Begin Source File");
	fprintf(f,"SOURCE=.\%s",entree);
	fprintf(f,"# End Source File");
	fprintf(f,"# Begin Source File");
//sortie du loop
	fprintf(f,"# End Group");
	fprintf(f,"# Begin Source File");
	 fprintf(f,"End Source File");
fprintf(f,"# End Target");
fprintf(f,"# End Project");
*/

}


void ListerRepFile(char* CurrentDir){
	WIN32_FIND_DATA fd; 
	char buffer[MAX_PATH];
 	SetCurrentDirectory(CurrentDir);
	BOOL fFinished=FALSE;
	int x=0;
	char tmp[200];
	HANDLE hSearch = FindFirstFile("*.*", &fd); 
	SendMessage(GetDlgItem(hWnd,IDC_LIST1),LB_ADDSTRING, 0,(LPARAM)fd.cFileName);
	if (hSearch == INVALID_HANDLE_VALUE){ printf("Analyse terminée de\n%s",CurrentDir);return;}
	while (!fFinished){ 
		x++;
		if  (GetFileAttributes(fd.cFileName)!= FILE_ATTRIBUTE_DIRECTORY){
			SendMessage(GetDlgItem(hWnd,IDC_LIST1),LB_ADDSTRING, 0,(LPARAM)fd.cFileName);
		}
		if (!FindNextFile(hSearch, &fd)){if (GetLastError() == ERROR_NO_MORE_FILES) { fFinished = TRUE; 	} else  { 	printf("Impossible de trouver le fichier suivant"); 				return;			} 		}	
} 
FindClose(hSearch);
}
void GetProjectName(char* path)
{
}