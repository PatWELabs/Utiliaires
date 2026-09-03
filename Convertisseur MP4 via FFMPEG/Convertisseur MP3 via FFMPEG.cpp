#include <windows.h>
#include <Shellapi.h>
#include <stdio.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include <iostream>
#include <sstream>
#pragma comment (lib,"Shlwapi")
#pragma comment (lib,"comctl32")

HWND hList=0;
WIN32_FIND_DATA File;  
HANDLE liste;  
TCHAR path[MAX_PATH];
TCHAR AppPath[MAX_PATH];
HWND hwnd; 



static int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData){
    if (uMsg == BFFM_INITIALIZED) {
        LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);
        ::SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM) path);
        MessageBox(hwnd,path,"Chemin",0);
    }
    return 0;
}
char* BrowseFolder(){
	char szDir [MAX_PATH];
	BROWSEINFO bi;        
	LPITEMIDLIST pidl;        
	LPMALLOC pMalloc;
	bool f_selected = false;
	if (SUCCEEDED (::SHGetMalloc (&pMalloc))){
		::ZeroMemory (&bi,sizeof(bi)); 	
		bi.lpszTitle  = ("Sélectionner le dossier à traiter...");
		bi.hwndOwner =hwnd;
		bi.pszDisplayName = 0;           
		bi.pidlRoot = 0;
		bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
		bi.lpfn = NULL; 
	//	bi.lParam = NULL;
		pidl = ::SHBrowseForFolder(&bi);  
		if (pidl){
			if (::SHGetPathFromIDList (pidl, szDir)){ f_selected = true;}
			pMalloc -> Free(pidl);
			pMalloc -> Release();
			}     
       }
       if (f_selected){        MessageBox (hwnd,szDir, "User selected path:",0);   	SetCurrentDirectory(szDir);
	char szRepertoire[260];
	char buffer[512];
	strcpy(szRepertoire,"*.*");
	FILE *f;
	  f = fopen ("\\myfile.cmd","w");
 	liste = FindFirstFile(szRepertoire, &File);
	while((FindNextFile(liste, &File)))
	{
	
			if(File.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			
		}else{
			/* GetShortPathName(
  _In_   LPCTSTR lpszLongPath,
  _Out_  LPTSTR lpszShortPath,
  _In_   DWORD cchBuffer
);
*/
			wsprintf(buffer,"ffmpeg.exe -i \"%s\\%s\" -vn -ar 44100 -ac 2 -ab 128000 -f mp4 \"%s%s.mp4\" >> \"%s\\%s.txt\"",szDir,File.cFileName,AppPath,File.cFileName,AppPath,File.cFileName);
			fprintf (f, "%s\n",buffer);
			SendMessage(hList,LB_ADDSTRING, 0, (LPARAM)File.cFileName);
			SetDlgItemText(hwnd,6000,buffer);
				}
	}
	fclose(f);
	FindClose(liste);
        return path;    }
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	MSG Msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Convertisseur MP4 via FFMPEG",WS_VISIBLE|WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,CW_USEDEFAULT, 	CW_USEDEFAULT,640,480,	NULL,NULL,hInstance,NULL);
	 hList= CreateWindowEx(WS_EX_CLIENTEDGE,"LISTBOX","",WS_VISIBLE|WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL,2,	2,625,	400,hwnd,(HMENU)1000,hInstance,NULL);
	 GetCurrentDirectory(256,AppPath);
	 PathAddBackslash(AppPath);
	 CreateStatusWindow(WS_CHILD|WS_VISIBLE,AppPath,hwnd,6000);
	 BrowseFolder();

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&Msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&Msg); /* Translate key codes to chars if present */
		DispatchMessage(&Msg); /* Send it to WndProc */
	}
	return Msg.wParam;
}
