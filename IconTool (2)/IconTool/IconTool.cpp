// IconTool.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "IconTool.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND hList;
HIMAGELIST im1,im2;
COLORREF background,textecolor;
char szItemSel[256];  //va contenir le nom de l'item(icone) selectionné
char Adresse[256];    //va contenir le nom du dossier ou se trouve l'item(icone) selectionné
int ListItem=0;
int LimitFolderFile;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int ImlListView(char* Path);
void AddIconIMG_List(HIMAGELIST &hIml, LPCTSTR lpIconName);
void InitListViewImageLists(void);
void RecupInfo(void);
void SwitchToRepport();
HRESULT SaveIcon(HICON hIcon,LPCSTR path);

int ImlListView(char* Path){
	SHFILEINFO sfi;
	ZeroMemory(&sfi,sizeof(SHFILEINFO));
	im1=(HIMAGELIST)SHGetFileInfo(Path, 0, &sfi,sizeof(SHFILEINFO),SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	im2=(HIMAGELIST)SHGetFileInfo(Path, 0, &sfi,sizeof(SHFILEINFO),SHGFI_SYSICONINDEX | SHGFI_LARGEICON);
	SendMessage(hList,LVM_SETIMAGELIST,LVSIL_SMALL,(LPARAM)im1);
	SendMessage(hList,LVM_SETIMAGELIST,LVSIL_NORMAL,(LPARAM)im2);
	return sfi.iIcon; 
}
void AddIconIMG_List(HIMAGELIST &hIml, LPCTSTR lpIconName){
	HICON hIcon=LoadIcon(hInst,lpIconName);
	ImageList_AddIcon(hIml,hIcon); 
    HRESULT hr = SaveIcon(hIcon, "c:\\test.ico");
	DeleteObject(hIcon);
}
HRESULT SaveIcon(HICON hIcon, LPCSTR path) {
    PICTDESC desc = { sizeof(PICTDESC) };
    desc.picType = PICTYPE_ICON;
    desc.icon.hicon = hIcon;
    IPicture* pPicture = 0;
    HRESULT hr = OleCreatePictureIndirect(&desc, IID_IPicture, FALSE, (void**)&pPicture);
    if (FAILED(hr)) return hr;
    IStream* pStream = 0;
    CreateStreamOnHGlobal(0, TRUE, &pStream);
    LONG cbSize = 0;
    hr = pPicture->SaveAsFile(pStream, TRUE, &cbSize);
    if (!FAILED(hr)) {
        HGLOBAL hBuf = 0;
        GetHGlobalFromStream(pStream, &hBuf);
        void* buffer = GlobalLock(hBuf);
        HANDLE hFile = CreateFile(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
        if (!hFile) hr = HRESULT_FROM_WIN32(GetLastError());
        else {
            DWORD written = 0;
            WriteFile(hFile, buffer, cbSize, &written, 0);
            CloseHandle(hFile);
        }
        GlobalUnlock(buffer);
    }
    pStream->Release();
    pPicture->Release();
    return hr;

}
void InitListViewImageLists(void) {	
	im1=ImageList_Create(32,32,ILC_COLOR24 | ILC_MASK,4,0); //limite gdi a 24bits 16M couleurs
	im2=ImageList_Create(16,16,ILC_COLOR24 | ILC_MASK,4,0);
	AddIconIMG_List(im1,MAKEINTRESOURCE(IDI_ICONTOOL));
	AddIconIMG_List(im2,MAKEINTRESOURCE(IDI_ICONTOOL));
	SendMessage(hList,LVM_SETIMAGELIST,LVSIL_SMALL,(LPARAM)im1);
	SendMessage(hList,LVM_SETIMAGELIST,LVSIL_NORMAL,(LPARAM)im2);
}
int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR    lpCmdLine,int       nCmdShow){
	MSG msg;
	HACCEL hAccelTable;
	HWND hWnd;
	WNDCLASSEX wcex;
	INITCOMMONCONTROLSEX lp;
	RECT rc;
	background=RGB(128,128,234);
	textecolor=RGB(234,255,128);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ICONTOOL, szWindowClass, MAX_LOADSTRING);
    hInst = hInstance; // Store instance handle in our global variable
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_ICONTOOL);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= CreateSolidBrush(background);
	wcex.lpszMenuName	= (LPCTSTR)IDC_ICONTOOL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= wcex.hIcon;
	if (!RegisterClassEx(&wcex)){return FALSE;}
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd){  return FALSE;  }
	CreateStatusWindow(WS_CHILD|WS_VISIBLE,__argv[0],hWnd,6000);
	GetClientRect(hWnd,&rc);
	lp.dwSize=sizeof(lp);
	lp.dwICC=ICC_LISTVIEW_CLASSES|ICC_WIN95_CLASSES|ICC_INTERNET_CLASSES|ICC_STANDARD_CLASSES|ICC_LINK_CLASS;
	InitCommonControlsEx(&lp);
	OleInitialize(NULL);
	InitListViewImageLists();
	DragAcceptFiles(hWnd,true);
	hList = CreateWindowEx(LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES|LVS_EX_CHECKBOXES | LVS_EX_TRACKSELECT| LVS_EX_FULLROWSELECT| LVS_EX_FLATSB | LVS_EX_INFOTIP,WC_LISTVIEW, 0, WS_CHILD|WS_VISIBLE | WS_BORDER|LVS_LIST|LVS_SINGLESEL|LVS_SORTASCENDING  |LVS_SHAREIMAGELISTS|LVS_AUTOARRANGE , 5, 5, rc.right-10, rc.bottom-36, hWnd,(HMENU)1000, hInstance, NULL);
	SendMessage(hList, LVM_SETBKCOLOR, 0, (LPARAM)(COLORREF)background);
    SendMessage(hList, LVM_SETTEXTCOLOR, 0, (LPARAM)(COLORREF)textecolor);
    SendMessage(hList, LVM_SETTEXTBKCOLOR, 0, (LPARAM)(COLORREF)background);
	SwitchToRepport();
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_ICONTOOL);
	while (GetMessage(&msg, NULL, 0, 0)) 	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	OleUninitialize();
	return (int) msg.wParam;
}
void RecupInfo(void){
	char szItemSelTemp[MAX_PATH]="";
	HWND GFocus=GetFocus();
	if(GFocus==hList){
		int ItemSel=ListView_GetNextItem(hList,-1,LVNI_SELECTED);
		ListView_GetItemText(hList,ItemSel,0,szItemSelTemp,sizeof(szItemSelTemp));
		strcpy(szItemSel,szItemSelTemp);
	}
}
void SwitchView( DWORD dwView){	DWORD dwStyle = GetWindowLong(hList, GWL_STYLE);SetWindowLong(hList, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);}
void SwitchToRepport(){
	LVCOLUMN lvc;
	int iCol = 0;
	ListView_SetExtendedListViewStyleEx(hList, LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);
	ListView_SetExtendedListViewStyle(hList, LVS_REPORT, LVS_REPORT);
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.iSubItem = iCol++;
	lvc.pszText = (LPSTR)"Fichier";
	lvc.cx = strlen(lvc.pszText) * 17;
	lvc.fmt = LVCFMT_LEFT;
	ListView_InsertColumn(hList, iCol, &lvc);
	lvc.iSubItem = iCol++;
	lvc.pszText = (LPSTR)"Index";
	lvc.cx = strlen(lvc.pszText) * 7;
	lvc.fmt = LVCFMT_LEFT;
	ListView_InsertColumn(hList, iCol, &lvc);
	lvc.iSubItem = iCol++;
	lvc.pszText = (LPSTR)"Chemin";
	lvc.cx = strlen(lvc.pszText) * 50;
	lvc.fmt = LVCFMT_LEFT;
	ListView_InsertColumn(hList, iCol, &lvc);

}
void ListerRepFile(HWND hDlg,char* Path) {
	bool bRestart=false;
	LVITEM LvItem;
	LvItem.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	LvItem.state=0; 
    LvItem.stateMask=0;
	LvItem.iSubItem=0;
	SetCurrentDirectory(Path);
Restart:
	WIN32_FIND_DATA wData;
	HANDLE listing;
	listing=FindFirstFile("*.*",&wData);
	if (listing==INVALID_HANDLE_VALUE)
		return;
	
	int bList=true;
	while(bList)
	{
		LvItem.iItem=ListItem;
		char szImlListView[256];
		char clef[8];
		if(wData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //Verifie que c'est bien un Dossier
		{
			if(strcmp(wData.cFileName,".")!=0 && strcmp(wData.cFileName,"..")!=0 && !bRestart)
			{
				LvItem.pszText=wData.cFileName;
				sprintf(szImlListView,"%s\\%s",Path,wData.cFileName);
				LvItem.iImage=ImlListView(szImlListView);
				int res = SendMessage(hList,LVM_INSERTITEM,0,(LPARAM)&LvItem);
				ListView_SetItemText(hList, res, 0, wData.cFileName);
				sprintf(clef,"%.8d",ListItem++);
				ListView_SetItemText(hList, res, 1, clef);
				ListView_SetItemText(hList, res, 2, Path);
				SetDlgItemText(hDlg,6000,szImlListView);
				ListItem++;
				ListerRepFile(hDlg,szImlListView);
			}
		}else{
			if(bRestart){
				LvItem.pszText=wData.cFileName;
				sprintf(szImlListView,"%s\\%s",Path,wData.cFileName);
				SetDlgItemText(hDlg,6000,szImlListView);
				LvItem.iImage=ImlListView(szImlListView);
				int res = SendMessage(hList,LVM_INSERTITEM,0,(LPARAM)&LvItem);
				ListView_SetItemText(hList, res, 0, wData.cFileName);
				sprintf(clef,"%.8d",ListItem++);
				ListView_SetItemText(hList, res, 1, clef);
				ListView_SetItemText(hList, res, 2, Path);
				SetDlgItemText(hDlg,6000,szImlListView);
				ListItem++;
			}
		}
		bList=FindNextFile(listing,&wData);
	}
	FindClose(listing);

	if(!bRestart){
		bRestart=true;
		LimitFolderFile=ListItem;
		goto Restart;	
	}
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	char clef[8];

	switch (message) 	{
	case WM_SETFOCUS:SetFocus(hList);break;
	case WM_DROPFILES:	{ 
		HDROP hDropInfo=(HDROP) wParam; 
		LVITEM LvItem;
		LvItem.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
		LvItem.state=0; 
		LvItem.stateMask=0;
		LvItem.iSubItem=0;
		int nb,taille,i; 
		taille=0; 
		nb=0; 
		nb=DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0 ); 
		char fic[500]; 
		char fic2[500]; 
		for( i = 0; i < nb; i++ ) 	{ 
			taille=DragQueryFile(hDropInfo, i, NULL, 0 )+1; 
			DragQueryFile(hDropInfo, i, fic, taille ); 
			LvItem.iImage=ImlListView(fic);
			strcpy(fic2,fic);
			int res = SendMessage(hList,LVM_INSERTITEM,0,(LPARAM)&LvItem);
			ListView_SetItemText(hList, res, 0, PathFindFileName(fic));
			sprintf(clef,"%.8d",res++);
			ListView_SetItemText(hList, res, 1, clef);
			ListView_SetItemText(hList, res, 2, fic2);
		} 
		DragFinish(hDropInfo);
	}	break; 
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		switch (wmId){
		case IDM_ABOUT:	DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);		break;
		case IDM_EXIT:	DestroyWindow(hWnd); PostQuitMessage(0);			break;
		case ID_OUVRIRUNDOSSIER:{
			BROWSEINFO bi;
			char szPath[MAX_PATH + 1];
			LPITEMIDLIST pidl;
			BOOL bResult = FALSE;
			LPMALLOC pMalloc;
			if (SUCCEEDED(SHGetMalloc(&pMalloc))) 					{
				bi.hwndOwner = GetDesktopWindow();
				bi.pidlRoot = NULL;
				bi.pszDisplayName = NULL;
				bi.lpszTitle = "Sélectionnez le dossier à traiter";
				bi.ulFlags = BIF_STATUSTEXT; //BIF_EDITBOX 
				bi.lpfn = 0;
				bi.lParam = 0;
				pidl = SHBrowseForFolder(&bi);
				if (pidl){if (SHGetPathFromIDList(pidl,szPath)) {
				bResult = TRUE;	
				SetDlgItemText(hWnd,6000,szPath);
				ListerRepFile(hWnd,szPath);
				}
			pMalloc->Free(pidl);
			pMalloc->Release();}
			}
							} break;
		case ID_REINITIALISERLALISTE:SendMessage(hList, LVM_DELETEALLITEMS, 0, 0L); break;	
		case ID_AFFICHAGE_LISTE:SwitchView(LVS_LIST); break;	
		case ID_AFFICHAGE_PETITESICONES:SwitchView(LVS_SMALLICON); break;	
		case ID_AFFICHAGE_GRANDESICONES:SwitchView(LVS_ICON); break;	
		case ID_AFFICHAGE_DETAILLE:SwitchView(LVS_REPORT); break;	
default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
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

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
