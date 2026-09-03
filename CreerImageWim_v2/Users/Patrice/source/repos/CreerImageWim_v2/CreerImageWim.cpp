// CreerImageWim.cpp : Definit le point d'entree de l'application.
//

#include "framework.h"
#include "CreerImageWim.h"

#define MAX_LOADSTRING 100

// Variables globales :
HINSTANCE hInst;                                // instance actuelle
CHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
CHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale
BROWSEINFO bi;
ITEMIDLIST *il;
OPENFILENAME ofn;
IWebBrowser2* pIWeb;
INITCOMMONCONTROLSEX iccex; 
WNDCLASS wc;
HWND hWnd,hwndTT,imghWnd;
NOTIFYICONDATAA nf;
RECT rc,rect;
HBITMAP bmp;
HMENU mnu;
SYSTEMTIME st;
BOOL AffichageMenu=FALSE;
WCHAR url[256];
DWORD version=MAKEWORD(21,1);
bool GestionErreur;
long returnValue;
unsigned long dwLen = 0;
double dwKeyEn = sizeof(long);
char szPath[MAX_PATH];
char buffer[MAX_PATH];
char Result[MAX_PATH];
char szFile[MAX_PATH];

BOOL CALLBACK    ProcedurePrincipale(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ProcedurePropos(HWND, UINT, WPARAM, LPARAM);

EXTERN_C const IID DIID_DWebBrowserEvents2;
EXTERN_C const IID IID_IShellDispatch2;

struct Erreur{
	int numero;
	int style;
	char *description;
};
struct ImageWIM{
	char date[0x08];
	bool bootable=false;
	char nom[0x30];
	char description[0x50];
	int type=0;
	char scratchDir[MAX_PATH];
	bool checkIntegrite=false;
	bool verifier=false;
	int compression=0;
} wim;
class Evenement : public IDispatch {
private:
	long ref;
	HWND fenetre;
	BSTR url;

public:
	Evenement(HWND fenet) {
		fenetre = fenet; 
	}
	~Evenement() { 
		SysFreeString(url); 
	}
	STDMETHODIMP QueryInterface(REFIID iid, void** ppvObject) {
		if (iid == IID_IUnknown || iid == IID_IDispatch || iid == DIID_DWebBrowserEvents2) {
			*ppvObject = this; AddRef(); 
			return S_OK; 
		} else return E_NOINTERFACE; 
	}
	ULONG STDMETHODCALLTYPE AddRef() { 
		return InterlockedIncrement(&ref); 
	}
	ULONG STDMETHODCALLTYPE Release() {
		int tmp = InterlockedDecrement(&ref); 
		if (tmp == 0) delete this; 
		return tmp; 
	}
	HRESULT STDMETHODCALLTYPE GetTypeInfoCount(unsigned int FAR* pctinfo) {
		return E_NOTIMPL; 
	}
	HRESULT STDMETHODCALLTYPE GetTypeInfo(unsigned int iTInfo, LCID  lcid, ITypeInfo FAR* FAR* ppTInfo) {
		return E_NOTIMPL; 
	}
	HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, unsigned int cNames, LCID lcid, DISPID FAR* rgDispId) {
		return E_NOTIMPL; 
	}
	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* parResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) {
		IUnknown* pIUnk; VARIANT* vurl;
		if (!pDispParams) return E_INVALIDARG;
		switch (dispIdMember) {
		case 0xFA:{
			pIUnk = pDispParams->rgvarg[6].pdispVal; 
			SendMessage(fenetre, BEFORENAVIGATE2, (WPARAM)pIUnk, 0);
				 }break;
		case 0x6A:{
			SendMessage(fenetre, DOWNLOADBEGIN, 0, 0); 
				 }break;
		case 0x68:{
			SendMessage(fenetre, DOWNLOADCOMPLETE, 0, 0); 
				 }break;
		case 0xFC:{
			pIUnk = pDispParams->rgvarg[1].pdispVal; 
			vurl = pDispParams->rgvarg[0].pvarVal; 
			url = vurl->bstrVal; 
			SendMessage(fenetre, NAVIGATECOMPLETE2, (WPARAM)pIUnk, (LPARAM)url); 
				 }break;
		case 0x103:{
			pIUnk = pDispParams->rgvarg[1].pdispVal;	
			SendMessage(fenetre, DOCUMENTCOMPLETE, (WPARAM)pIUnk, 0); 
				 }break;
		case 0x69:{
			long command; command = pDispParams->rgvarg[1].lVal;
			VARIANT_BOOL etat = pDispParams->rgvarg[0].boolVal; 
			SendMessage(fenetre, COMMANDSTATECHANGE, (WPARAM)command, (LPARAM)etat); 
				 }break;
		case 0xFB:{
			pDispParams->rgvarg[0].pvarVal->vt = VT_BOOL; 
			pDispParams->rgvarg[0].pvarVal->boolVal = VARIANT_TRUE; 
				 }break;
		default:break;
		}return S_OK;
	}


};
char jours[7][10] = {"dimanche", "lundi","mardi","mercredi","jeudi","vendredi","samedi"};
char mois[12][10] = {"janvier", "fevrier","mars", "avril", "mai", "juin","juillet","aout","septembre", "octobre", "novembre", "decembre"};
char edition[5][19]={"Windows Pro","Windows Entreprise","Windows Education","Windows Familiale","Windows PE"};

char* ExtraireNomImage(char* Chemin);
void GetDate();
char* GetTime();
void Horrodatage(char* dataTexte);
void SauverFichier();
void ExplorerDossiers(LPCTSTR titre);
void AjouterAuMenu(HMENU menu);
static BOOL CALLBACK DialogFunc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
LPSTR ExecuteCommandeDos(LPSTR csExeName, LPSTR csArguments);
void GenerationParametre();
int MsgBox(HWND hDlg,char* lpszText,char* lpszCaption, DWORD dwStyle,int lpszIcon);
void IntegrationExplorateur(HWND hDlg);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CREERIMAGEWIM, szWindowClass, MAX_LOADSTRING);
	iccex.dwICC=ICC_WIN95_CLASSES;
	iccex.dwSize=sizeof(iccex);
	InitCommonControlsEx(&iccex);
	GetCurrentDirectory(0xFF,wim.scratchDir);
	memset(&wc,0,sizeof(wc));
	wc.hCursor=LoadCursor(hInstance, (LPCTSTR)IDC_CURSOR1);
	wc.lpfnWndProc = DefDlgProc;
	wc.cbWndExtra = DLGWINDOWEXTRA;
	wc.hInstance = hInstance;
	wc.lpszClassName ="CreerImageWim";
	wc.hbrBackground=(HBRUSH)CreateSolidBrush(RGB(0xCC,0xCC,0xCC));
	wc.hIcon=LoadIcon(hInstance,(LPCTSTR)IDI_ICON1);
	wc.style = CS_VREDRAW  | CS_HREDRAW | CS_SAVEBITS | CS_DBLCLKS;
	RegisterClass(&wc);
	return DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, NULL, (DLGPROC)ProcedurePrincipale);
}
BOOL CALLBACK ProcedurePrincipale(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	hWnd =hDlg;
	POINT mouse;
	switch (message) {
		case WM_INITDIALOG:{
			AnimateWindow(hDlg, 2000, AW_CENTER|AW_ACTIVATE);
			GetDate();
			Horrodatage(wim.date);
			SetTimer(hDlg,IDM_TIMER1,1000,(TIMERPROC) NULL);
			RemoveMenu(GetSystemMenu(hDlg, FALSE), SC_CLOSE, MF_STRING);
			RemoveMenu(GetSystemMenu(hDlg, FALSE), SC_MOVE, MF_STRING);
			AjouterAuMenu(GetSystemMenu(hDlg,FALSE));
			AppendMenu(GetSystemMenu(hDlg,FALSE),MF_STRING, IDM_ProcedurePropos,"A propos de ce programme..");
			AppendMenu(GetSystemMenu(hDlg,FALSE),MF_STRING,0xE140,"Quel Windows s'execute?");
			AppendMenu(GetSystemMenu(hDlg,FALSE),MF_STRING,2,"Fermer ce programme");
			SendMessage(GetDlgItem(hDlg,IDCANCEL), WM_SETFONT, (WPARAM)GetStockObject(0x1E), MAKELPARAM(TRUE, 0));
			SendMessage(GetDlgItem(hDlg,IDOK), WM_SETFONT, (WPARAM)GetStockObject(0x1F), MAKELPARAM(TRUE, 0));
			SendMessage(GetDlgItem(hDlg,0xE140), STM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadIcon(wc.hInstance,(LPCTSTR)IDI_ICON1));
			nf.cbSize=sizeof(nf);
			nf.hIcon=wc.hIcon;
			nf.hWnd=hDlg;
			strcpy(nf.szTip,"CreerImageWim\0");
			nf.uCallbackMessage=WM_TRAY_ICONE;
			nf.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
			Shell_NotifyIcon(NIM_ADD,&nf);
			imghWnd = CreateWindowEx(0, "STATIC", NULL, WS_VISIBLE|WS_CHILD|SS_ICON,600, 10, 10, 10,hDlg , (HMENU)45000, wc.hInstance, NULL);
			SendMessage(imghWnd, STM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadIcon(wc.hInstance,(LPCTSTR)IDI_ICON2));
			SetWindowText(hDlg,Titre);
			GetLocalTime(&st);
			CreateStatusWindow(WS_CHILD|WS_VISIBLE,__argv[0],hDlg,6000);
			sprintf(buffer,"Nous sommes %s, le %2d %s %4d",jours[st.wDayOfWeek],st.wDay,mois[st.wMonth-1],st.wYear); //creation du string de date
			SetDlgItemText(hDlg,IDC_TIME2,buffer);
			SendMessage(GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING, 0,(LPARAM)buffer);
			SendMessage(GetDlgItem(hDlg,IDC_COMBO1),CB_ADDSTRING, 0,(LPARAM)"Aucune");
			SendMessage(GetDlgItem(hDlg,IDC_COMBO1),CB_ADDSTRING, 0,(LPARAM)"Rapide");
			SendMessage(GetDlgItem(hDlg,IDC_COMBO1),CB_ADDSTRING, 0,(LPARAM)"Normale");
			SendMessage(GetDlgItem(hDlg,IDC_COMBO1),CB_ADDSTRING, 0,(LPARAM)"Maximale");
			for(int a=0; a<5;a++){
				SendMessage(GetDlgItem(hDlg,IDC_COMBO2),CB_ADDSTRING, 0,(LPARAM)edition[a]);
			}
			SendMessage(GetDlgItem(hDlg,IDC_COMBO1),CB_SETCURSEL,(WPARAM)3, 0);
			SendMessage(GetDlgItem(hDlg,IDC_COMBO2),CB_SETCURSEL,(WPARAM)4, 0);
			IntegrationExplorateur(hDlg);
#ifdef _WIN64
			SetClassLong(hDlg, GCLP_HICON, (long)LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON3)));
#else
			SetClassLong(hDlg, GCL_HICON, (long)LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON3)));
#endif // WIN64
			SendMessage(GetDlgItem(hDlg,IDOK), WM_SETFONT, (WPARAM)GetStockObject(2), 1L);
			SendMessage(GetDlgItem(hDlg,IDC_EDIT4), WM_SETFONT, (WPARAM)GetStockObject(11), 1L);
			SendMessage(GetDlgItem(hDlg,6000), WM_SETFONT, (WPARAM)GetStockObject(8), 1L);
			SendMessage(GetDlgItem(hDlg,IDCANCEL), WM_SETFONT, (WPARAM)GetStockObject(10), 1L);
			SetTextColor( (HDC)IDC_EDIT1, RGB(128,255,0) );
			SetDlgItemText(hDlg,IDC_EDIT3,wim.scratchDir);

					   }return TRUE;
	case WM_SYSCOMMAND:{
		switch (LOWORD(wParam)) {
			case 0xE140:ShellAbout(hDlg,wc.lpszClassName,"Createur d'images WIM 32Bits\n© Patrice Waechter-Ebling 2022",wc.hIcon);
				break;
			case IDM_ProcedurePropos:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ProcedureProposBOX), hWnd, ProcedurePropos);
				break;
			case 0xE145:
				break;
			case IDCANCEL:{
					Shell_NotifyIcon(NIM_DELETE,&nf); 
					KillTimer(hDlg,IDM_TIMER1);
					PostQuitMessage(1);
						  }return 0x01;
				}		
					   }break;	
	case WM_COMMAND:{
		switch (LOWORD(wParam)) {
			case IDC_BUTTON1:
				ExplorerDossiers("Demo pour etude\nFunction BrowseForFolders");
				break;
			case IDC_BUTTON3:{
				SauverFichier();
							 }break;
			case IDM_ProcedurePropos:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ProcedureProposBOX), hWnd, ProcedurePropos);
				break;
			case 0xE141:ShellExecute(hDlg,"open",wim.scratchDir,NULL,NULL,0x01);
				break;
			case 0xE142:	
//				SendMessage(GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING, 0,(LPARAM)"Founction AddToList");//ajout a la liste
				break;
			case 0xE143:
//				SendMessage(GetDlgItem(hDlg,IDC_LIST1),LB_RESETCONTENT, 0,0); //efface la liste
				MessageBox(hDlg,"Liste effacee","Demo pour etude",MB_OK|MB_ICONEXCLAMATION);
				break;
			case 0xE144:
	//			OuvrirFichier("Function GetOpenFileName");
				break;
			case IDC_CHECK1:{
				if (IsDlgButtonChecked(hDlg, IDC_CHECK1)){
					CheckDlgButton(hDlg, IDC_CHECK1, false);
				}else{
					CheckDlgButton(hDlg, IDC_CHECK1, true); 
				}
							} break;
			case IDC_CHECK2:{
				if (IsDlgButtonChecked(hDlg, IDC_CHECK2)){
					CheckDlgButton(hDlg, IDC_CHECK2, false); 
				}else{
					CheckDlgButton(hDlg, IDC_CHECK2, true);
				}
							}break;
			case IDC_CHECK3:{
				if (IsDlgButtonChecked(hDlg, IDC_CHECK3)){
					CheckDlgButton(hDlg, IDC_CHECK3, false);
				}else{
					CheckDlgButton(hDlg, IDC_CHECK3, true);
				}
							}break;
			case IDC_EDIT4:{
					switch(HIWORD(wParam)){
						case EN_CHANGE:{
							char buffer[261];
							GetDlgItemText(hDlg,IDC_EDIT4,buffer,sizeof(buffer));
							if(strlen(buffer)==0x50){MsgBox(hDlg,buffer,(char*)"Description exedentaire",0,IDI_ICON2);	 }
									   }break;
					}
							   }break;
			case IDC_COMBO2:{
				switch(HIWORD(wParam)){
					int selection = SendMessage (GetDlgItem(hDlg,IDC_COMBO2),CB_GETCURSEL,NULL,NULL);
					if (selection!=CB_ERR){
						wsprintf(buffer,"%s Plateforme: %s",GetTime(),edition[selection]);
						SendMessage(GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING, 0,(LPARAM)buffer);
						MessageBox(hDlg,buffer,0,0);


					}
				}break;
							}break;
			case IDCANCEL:{
					Shell_NotifyIcon(NIM_DELETE,&nf); 
					KillTimer(hDlg,IDM_TIMER1);
					PostQuitMessage(1);
						  }return 0x01;
			}
							 }break;
		case WM_TIMER:{
			GetLocalTime(&st);
			sprintf(buffer,"Nous sommes %s, le %2d %s %4d",jours[st.wDayOfWeek],st.wDay,mois[st.wMonth-1],st.wYear);
			SetDlgItemText(hDlg,IDC_TIME2,buffer);
			sprintf(buffer,"%.2d:%.2d:%.2d",st.wHour,st.wMinute,st.wSecond);
			SetDlgItemText(hDlg,IDC_TIME,buffer);
					  }break;
		case WM_CTLCOLORDLG:		return (long)wc.hbrBackground;
		case WM_CTLCOLORSTATIC:{
			SetTextColor( (HDC)wParam, RGB(0, 0,255) );
			SetBkMode( (HDC)wParam, TRANSPARENT ); 
						   }return (LONG)wc.hbrBackground; //retourne la couleur choisie dans la classe
		case WM_CTLCOLOREDIT:{
			SetBkMode((HDC)wParam, TRANSPARENT); 	
			if (GetDlgItem(hDlg, IDC_EDIT1) == reinterpret_cast<HWND>(lParam)) SetTextColor((HDC)wParam, RGB(0,120,  192)); 
			if (GetDlgItem(hDlg, IDC_CHEMIN) == reinterpret_cast<HWND>(lParam)) SetTextColor((HDC)wParam, RGB(0, 0, 155)); 
			if (GetDlgItem(hDlg, IDC_EDIT3) == reinterpret_cast<HWND>(lParam)) SetTextColor((HDC)wParam, RGB(0,65,  0)); 
			if (GetDlgItem(hDlg, IDC_EDIT4) == reinterpret_cast<HWND>(lParam)) SetTextColor((HDC)wParam, RGB(255, 0, 25)); 

						 }return (LONG)(HBRUSH)wc.hbrBackground;
		case WM_CTLCOLORLISTBOX: {
			SetTextColor( (HDC)wParam, RGB(255,255, 255) );
			SetBkMode( (HDC)wParam, TRANSPARENT ); 
							 }return (LONG)(HBRUSH)CreateSolidBrush(RGB(0,0,0));
		case WM_CTLCOLORBTN:{
			SetBkMode( (HDC)wParam, TRANSPARENT );
			switch(LOWORD(wParam)){
			case IDOK:{SetTextColor((HDC)wParam, RGB(0, 255, 0));}break;
			}
				if (GetDlgItem(hWnd, IDCANCEL) == reinterpret_cast<HWND>(lParam)) SetTextColor((HDC)wParam, RGB(255, 0, 0)); 
				if (GetDlgItem(hWnd, 6000) == reinterpret_cast<HWND>(lParam)) SetTextColor((HDC)wParam, RGB( 0, 0,255)); 
						}return (LONG)(HBRUSH)wc.hbrBackground;
		case WM_CTLCOLORMSGBOX:{
			SetTextColor( (HDC)wParam, RGB(0,255, 255) );
						   }return (long)(HBRUSH)CreateSolidBrush(RGB(255,0,128));
		case WM_CLOSE: {
			Shell_NotifyIcon(NIM_DELETE,&nf);
			KillTimer(hDlg,IDM_TIMER1);
			PostQuitMessage(1);
				   }return  0x01;
	}return FALSE;
 
}

// Gestionnaire de messages pour la boîte de dialogue À propos de.
INT_PTR CALLBACK ProcedurePropos(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_CTLCOLORDLG:		return (long)CreateSolidBrush(RGB(0xCC, 0xCC, 0x50));
	case WM_CTLCOLORSTATIC: {
		SetTextColor((HDC)wParam, RGB(0, 0, 255));
		SetBkMode((HDC)wParam, TRANSPARENT);
	}return (LONG)CreateSolidBrush(RGB(0xCC, 0xCC, 0x50));
	case WM_CTLCOLORBTN: {
		SetBkMode((HDC)wParam, TRANSPARENT);
		switch (LOWORD(wParam)) {
		case IDOK: {SetTextColor((HDC)wParam, RGB(0, 255, 0)); }break;
		}
		if (GetDlgItem(hWnd, IDCANCEL) == reinterpret_cast<HWND>(lParam)) SetTextColor((HDC)wParam, RGB(255, 0, 0));
	}return (LONG)(HBRUSH)wc.hbrBackground;
	case WM_CTLCOLORMSGBOX: {
		SetTextColor((HDC)wParam, RGB(0, 255, 255));
	}return (long)(HBRUSH)CreateSolidBrush(RGB(255, 0, 128));

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
LPSTR ExecuteCommandeDos(LPSTR csExeName, LPSTR csArguments){
	char tempEx[0xFE];
	wsprintf(tempEx,"cmd -c %s %s",csExeName,csArguments);
	SECURITY_ATTRIBUTES secattr; 
	ZeroMemory(&secattr,sizeof(secattr));
	secattr.nLength = sizeof(secattr);
	secattr.bInheritHandle = TRUE;
	HANDLE rPipe, wPipe;
	CreatePipe(&rPipe,&wPipe,&secattr,0);
	STARTUPINFO sInfo; 
	ZeroMemory(&sInfo,sizeof(sInfo));
	PROCESS_INFORMATION pInfo; 
	ZeroMemory(&pInfo,sizeof(pInfo));
	sInfo.cb=sizeof(sInfo);
	sInfo.dwFlags=STARTF_USESTDHANDLES;
	sInfo.hStdInput=NULL; 
	sInfo.hStdOutput=wPipe; 
	sInfo.hStdError=wPipe;
	CreateProcess(0,(LPSTR)tempEx,0,0,TRUE,NORMAL_PRIORITY_CLASS|CREATE_FORCEDOS/*CREATE_NO_WINDOW*/,0,0,&sInfo,&pInfo);
	CloseHandle(wPipe);
	char buf[100];
	DWORD reDword; 
	Horrodatage(tempEx);
	char m_csOutput[0xff];
	BOOL res;
	do{
		res=::ReadFile(rPipe,buf,100,&reDword,0);
		strcat(m_csOutput,buf);
	}while(res);
	SendMessage(GetDlgItem(hWnd,IDC_LIST1),LB_ADDSTRING, 0,(LPARAM)m_csOutput);

	return m_csOutput;
}
char* ExtraireNomImage(char* Chemin){
	wsprintf(wim.nom,"%s_%s",PathFindFileNameA(Chemin), wim.date);
	return wim.nom;
}
void GetDate(){
	GetLocalTime(&st);
	wsprintf(wim.date,"%4d%.2d%.2d",st.wYear,st.wMonth,st.wDay);
}
char* GetTime(){
	char tmp[10];
	GetLocalTime(&st);
	wsprintf(tmp,"%.2d%:2d%:2d",st.wHour,st.wMinute,st.wSecond);
	return tmp;
}
void GenerationParametre(){
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(wc.hInstance, 1, szHello, MAX_LOADSTRING);
	char scratch[0xFE];
	GetCurrentDirectory(0xFE,scratch);
	GetDlgItemText(hWnd,IDC_EDIT1,wim.nom,sizeof(wim.nom));
	GetDlgItemText(hWnd,IDC_EDIT4, wim.description,sizeof(wim.description));
	wim.bootable=(bool)IsDlgButtonChecked(hWnd, IDC_CHECK1);
	wim.verifier=(bool)IsDlgButtonChecked(hWnd, IDC_CHECK2);
	wim.checkIntegrite=(bool) IsDlgButtonChecked(hWnd, IDC_CHECK3);
	/*
char edition[0x16];
int compression=0;
	*/
}
int MsgBox(HWND hDlg,char* lpszText,char* lpszCaption, DWORD dwStyle,int lpszIcon){
	MSGBOXPARAMS lpmbp;
	lpmbp.hInstance=wc.hInstance;
	lpmbp.cbSize=sizeof(MSGBOXPARAMS);
	lpmbp.hwndOwner=hDlg;
	lpmbp.dwLanguageId=MAKELANGID(0x0800,0x0800); //par defaut celui du systeme
	lpmbp.lpszText=lpszText;
	if(lpszCaption!=NULL){
		lpmbp.lpszCaption=lpszCaption;
	}else{
		lpmbp.lpszCaption=Titre;
	}
	lpmbp.dwStyle=dwStyle|0x00000080L;
	lpmbp.lpszIcon=(LPCTSTR)lpszIcon;
	lpmbp.lpfnMsgBoxCallback=0;
	return  MessageBoxIndirect(&lpmbp);
}
void IntegrationExplorateur(HWND hDlg){
	static BSTR titre;
	Evenement* pEvnm;
	IConnectionPointContainer* pCPContainer;
	IConnectionPoint* pConnectionPoint;
	DWORD dwCookie = 0; HINSTANCE hDLL = 0;
	HWND  hConteneur= GetDlgItem(hDlg,IDC_EXPLORATEUR);
#ifdef _WIN64
	SetClassLong(hConteneur, GCLP_HICON, (long)LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON1)));
#else
	SetClassLong(hConteneur, GCL_HICON, (long)LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON1)));
#endif // WIN64
	hDLL = LoadLibraryA("atl.dll");
	typedef HRESULT(WINAPI* PAttachControl)(IUnknown*, HWND, IUnknown**);
	PAttachControl AtlAxAttachControl = (PAttachControl)GetProcAddress(hDLL, "AtlAxAttachControl");
	CoInitialize(0);
	CoCreateInstance(CLSID_WebBrowser, 0, CLSCTX_ALL, IID_IWebBrowser2, (void**)&pIWeb);
	AtlAxAttachControl(pIWeb, hConteneur, NULL);
	pIWeb->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPContainer);
	pCPContainer->FindConnectionPoint(DIID_DWebBrowserEvents2, &pConnectionPoint);
	pEvnm = new Evenement(hConteneur);
	pConnectionPoint->Advise(pEvnm, &dwCookie);
	if (pCPContainer) pCPContainer->Release();
	MultiByteToWideChar(CP_ACP, 0, (LPCCH)wim.scratchDir, -1, url, 256);
	pIWeb->Navigate(url, 0, 0, 0, 0);

}
void AjouterAuMenu(HMENU menu){
	AppendMenu(menu,MF_STRING,0xE140,"À propos de ce programme"); //about
	SetMenuItemBitmaps(menu,MF_BYCOMMAND,0xE140,bmp,bmp);
}

void Horrodatage(char* dataTexte){
	char temp[0xFF];
	GetLocalTime(&st);
	wsprintf(buffer,"%4d%2d%2d:%2d%2d%.2d > %s",st.wYear,st.wMonth-1,st.wDay,st.wHour,st.wMinute,st.wSecond,dataTexte);
	SendMessage(GetDlgItem(hWnd,IDC_LIST1),LB_ADDSTRING, 0,(LPARAM)temp);
}
void SauverFichier(){
	SHGetSpecialFolderPath(hWnd,szPath,CSIDL_PERSONAL,FALSE);
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrInitialDir = szPath;
	ofn.lpstrFilter ="Fichiers Source\0*.wim\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle="Enregister l'image sous";
	ofn.lpstrFileTitle =NULL;
	ofn.nMaxFileTitle = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetSaveFileName(&ofn)==TRUE) { 
		HANDLE hf = CreateFile(ofn.lpstrFile, GENERIC_WRITE,0, (LPSECURITY_ATTRIBUTES) NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,(HANDLE) NULL); //acces au fichier
		SetDlgItemText(hWnd,IDC_EDIT3,ofn.lpstrFile);
	}
}
void ExplorerDossiers(LPCTSTR titre){
	bi.hwndOwner=hWnd;
	bi.pidlRoot=NULL;
	bi.pszDisplayName=&buffer[0];
	bi.lpszTitle=titre;
	bi.ulFlags=BIF_RETURNONLYFSDIRS |BIF_DONTGOBELOWDOMAIN|BIF_STATUSTEXT |BIF_EDITBOX ;
	bi.lpfn=NULL; 
	il=SHBrowseForFolder(&bi);
	if (il==NULL) return ;
	if(SHGetPathFromIDList(il,&Result[0])){
		SetDlgItemText(hWnd,IDC_CHEMIN,Result);
		if(strlen(Result)<=3){
			CHAR szVolumeName[MAX_PATH];
			BOOL bSucceeded = GetVolumeInformation(Result,szVolumeName,MAX_PATH,NULL,NULL,NULL,NULL,0);
			SetDlgItemText(hWnd,IDC_EDIT1,ExtraireNomImage(szVolumeName));
		}else{
			SetDlgItemText(hWnd,IDC_EDIT1,ExtraireNomImage(Result));
		}
		MultiByteToWideChar(CP_ACP, 0, (LPCCH) Result, -1, url, 256);
		pIWeb->Navigate(url, 0, 0, 0, 0);
	}
}
void OnRegError(int nError){
	Erreur err;
	switch (nError){
	case ERR_CLECHEMIN:
		err.numero = 1;
		err.description =(char*) "La base et le chemin indiques n'existe pas ou sont inaccessible!";
		err.style = MB_ICONSTOP;
		break;
	case ERR_NOM:
		err.numero = 2;
		err.description = (char*)"Le nom indique n'existe pas ou est inaccessible!";
		err.style = MB_ICONSTOP;
		break;
	case ERR_FERMER:
		err.numero = 3;
		err.description = (char*)"La cle n'a pas pu être fermee!";
		err.style = MB_ICONSTOP;
		break;
	case ERR_ECRIRE:
		err.numero = 4;
		err.description = (char*)"La nouvelle valeur n'a pas pu être ecrite!";
		err.style = MB_ICONSTOP;
		break;
	case ERR_CREERCLE:
		err.numero = 5;
		err.description = (char*)"Une erreur s'est produite! La cle n'a pas pu être cree!";
		err.style = MB_ICONSTOP;
		break;
	case ERR_SUPRCLE:
		err.numero = 6;
		err.description = (char*)"La cle n'a pas pu être supprime! Veuillez verifier la base et le chemin indique!";
		err.style = MB_ICONSTOP;
		break;
	case ERR_SUPRVAL:
		err.numero = 7;
		err.description = (char*)"La valeur n'a pa pu être supprime!\nLe nom de la cle indique n'existe pas! Veuillez verifier le nom!";
		err.style = MB_ICONSTOP;
	}
	MsgBox(0,err.description, (char*)"Registre",err.style,IDI_ICON1);

}

HKEY ChoisirBase(char *base){
	HKEY tBase=0;
	if(strcmp(base,"HKEY_CURRENT_USER")==0)tBase = HKEY_CURRENT_USER;	
	else if(strcmp(base,"HKEY_USERS")==0)tBase = HKEY_USERS;
	else if(strcmp(base,"HKEY_LOCAL_MACHINE")==0)tBase = HKEY_LOCAL_MACHINE;
	else if(strcmp(base,"HKEY_CURRENT_CONFIG")==0)tBase = HKEY_CURRENT_CONFIG;
	else if(strcmp(base,"HKEY_CLASSES_ROOT")==0)tBase = HKEY_CLASSES_ROOT;
	return tBase;
}
unsigned long ChoisirType(char *type){
	unsigned long hResType=0;
	if(strcmp(type,"REG_NONE")==0)hResType = REG_NONE;	
	else if(strcmp(type,"REG_SZ")==0)hResType = REG_SZ;
	else if(strcmp(type,"REG_BINARY")==0)hResType = REG_BINARY;
	else if(strcmp(type,"REG_DWORD")==0)hResType = REG_DWORD;
	else if(strcmp(type,"REG_DWORD_BIG_ENDIAN")==0)hResType = REG_DWORD_BIG_ENDIAN;
	else if(strcmp(type,"REG_LINK")==0)hResType = REG_LINK;
	else if(strcmp(type,"REG_MULTI_SZ")==0)hResType = REG_MULTI_SZ;
	return hResType;
}
bool OuvrirCle(char *base, char *chemin, HKEY *hCle){
	HKEY hTempCle=0;
	returnValue = RegOpenKey(ChoisirBase(base), chemin, &hTempCle);
	if (returnValue != ERROR_SUCCESS)    {
		if(GestionErreur)	OnRegError(ERR_CLECHEMIN);		return false;
	}
	*hCle = hTempCle;
	return 	true;
}
char* LireValeur(HKEY hCle, char *nom, BOOL *OpRes){
	returnValue = RegQueryValueEx(hCle, nom, NULL, NULL, NULL, &dwLen);
	returnValue = RegQueryValueEx(hCle, nom, NULL, NULL, (LPBYTE)&dwKeyEn, &dwLen);
	if(returnValue != ERROR_SUCCESS)    {
		*OpRes = false;
		if(GestionErreur)	OnRegError(ERR_NOM);
		return (char*)"Erreur!";
	}
	*OpRes = true;
	return (char*)&dwKeyEn; 
}
bool EcrireValeur(HKEY hCle, char *nom, char *valeur, char *type){
	returnValue = RegSetValueEx(hCle,nom,NULL,ChoisirType(type),(PBYTE)valeur,strlen(valeur));
	if(returnValue != ERROR_SUCCESS)    {
		if(GestionErreur)	OnRegError(ERR_ECRIRE);	return false;
	}
	return true;
}
bool CreerCle(char *base, char *chemin, HKEY *hCle){
	HKEY hTempCle=0;
	long returnValue = RegCreateKey(ChoisirBase(base),chemin,&hTempCle);
	if(returnValue != ERROR_SUCCESS)    {
		if(GestionErreur)
			OnRegError(ERR_CREERCLE);
		return false;
	}
	*hCle = hTempCle;
	return true;
}
bool SupprimerCle(char *base, char *chemin){
	returnValue = RegDeleteKey(ChoisirBase(base),chemin);
	if(returnValue != ERROR_SUCCESS){
		if(GestionErreur)	OnRegError(ERR_SUPRCLE);		return false;
	}
	return true;
}
bool SupprimerValeur(char *base, char *chemin, char *nom){
	HKEY hTempCle=0;		
	if(!OuvrirCle(base,chemin,&hTempCle))		return false;
	returnValue = RegDeleteValue(hTempCle,nom);
	if(returnValue != ERROR_SUCCESS){
		if(GestionErreur)	OnRegError(ERR_SUPRVAL);		return false;
	}
	return true;
}
bool FermerCle(HKEY hCle){
	returnValue = RegCloseKey(hCle);
	if(returnValue != ERROR_SUCCESS)    {
		if(GestionErreur)	OnRegError(ERR_FERMER);		return false;
	}
	return true;
}
