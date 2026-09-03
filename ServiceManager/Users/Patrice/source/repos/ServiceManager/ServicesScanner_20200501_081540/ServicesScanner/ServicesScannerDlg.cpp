// ServicesScannerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServicesScanner.h"
#include "ServicesScannerDlg.h"
#include ".\servicesscannerdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
SC_HANDLE sc;
char config[256];

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CServicesScannerDlg::CServicesScannerDlg(CWnd* pParent /*=NULL*/)	: CDialog(CServicesScannerDlg::IDD, pParent){
	//{{AFX_DATA_INIT(CServicesScannerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServicesScannerDlg::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServicesScannerDlg)
	DDX_Control(pDX, IDC_LIST1, m_scan);
	DDX_Control(pDX, IDC_LIST2, trusted);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_PROGRESS1, progress);
}

BEGIN_MESSAGE_MAP(CServicesScannerDlg, CDialog)
	//{{AFX_MSG_MAP(CServicesScannerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_COMMAND(IDM_ABOUTBOX, OnAboutbox)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CServicesScannerDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()){
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);
	//strcpy(config,);
	wsprintf(config,"%s",__argv[0]);
	PathRenameExtension(config,".ini");
	MessageBox(config,AfxGetApp()->m_pszExeName,0);

	return TRUE; 
}

void CServicesScannerDlg::OnSysCommand(UINT nID, LPARAM lParam){
	if ((nID & 0xFFF0) == IDM_ABOUTBOX){
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}	else	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
void CServicesScannerDlg::OnPaint() {
	if (IsIconic())	{
		CPaintDC dc(this); 
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}else{
		CDialog::OnPaint();
	}
}

HCURSOR CServicesScannerDlg::OnQueryDragIcon(){	return (HCURSOR) m_hIcon;}
void CServicesScannerDlg::OnOK(){
	sc = ::OpenSCManager (NULL,NULL,SC_MANAGER_ENUMERATE_SERVICE);
	if (sc != NULL)	{
		ENUM_SERVICE_STATUS service_data, *lpservice;
		BOOL retVal;
		DWORD bytesNeeded,srvCount,resumeHandle = 0,srvType, srvState;
		srvType = SERVICE_WIN32;
		srvState = SERVICE_STATE_ALL;
		retVal = ::EnumServicesStatus (sc,srvType,srvState,&service_data,sizeof(service_data),
		&bytesNeeded,&srvCount,&resumeHandle);
		DWORD err = GetLastError();
		if ((retVal == FALSE) || err == ERROR_MORE_DATA){
			DWORD dwBytes = bytesNeeded + sizeof(ENUM_SERVICE_STATUS);
			lpservice = new ENUM_SERVICE_STATUS [dwBytes];
			EnumServicesStatus (sc,srvType,srvState,lpservice,dwBytes,&bytesNeeded,&srvCount,&resumeHandle);
		}
		char buffer[256];
		progress.SetRange(0,(short)srvCount);
		progress.SetBkColor(RGB(128,128,128));
		for(int i=0;i<srvCount;i++)	{
			wsprintf(buffer,"\"%s\" \"%s\"",lpservice[i].lpServiceName,lpservice[i].lpDisplayName);
			progress.SetPos(i);
			m_scan.AddString(buffer);
			SetDlgItemInt(IDC_STATUT,i,0);
		}
	}
	CloseServiceHandle(sc);
}

void CServicesScannerDlg::OnDblclkList1() 
{
	char buffer[256];
	char cmd[256];
	m_scan.GetText(m_scan.GetCurSel(),buffer);
	if (MessageBox(buffer,"RemoveService",MB_YESNO|MB_ICONHAND|MB_ICONSTOP|MB_DEFBUTTON2)==0x06){
		wsprintf(cmd,"RemoveService.exe %s",buffer);
		system(cmd);
	}
}

void CServicesScannerDlg::OnBnClickedButton1()
{
	sc = ::OpenSCManager (NULL,NULL,SC_MANAGER_ENUMERATE_SERVICE);
	if (sc != NULL)	{
		ENUM_SERVICE_STATUS service_data, *lpservice;
		BOOL retVal;
		DWORD bytesNeeded,srvCount,resumeHandle = 0,srvType, srvState;
		srvType = SERVICE_WIN32;
		srvState = SERVICE_STATE_ALL;
		retVal = ::EnumServicesStatus (sc,srvType,srvState,&service_data,sizeof(service_data),
		&bytesNeeded,&srvCount,&resumeHandle);
		DWORD err = GetLastError();
		if ((retVal == FALSE) || err == ERROR_MORE_DATA){
			DWORD dwBytes = bytesNeeded + sizeof(ENUM_SERVICE_STATUS);
			lpservice = new ENUM_SERVICE_STATUS [dwBytes];
			EnumServicesStatus (sc,srvType,srvState,lpservice,dwBytes,&bytesNeeded,&srvCount,&resumeHandle);
		}
		char buffer[256];
		for(int i=0;i<srvCount;i++)	{
			wsprintf(buffer,"\"%s\" \"%s\"",lpservice[i].lpServiceName,lpservice[i].lpDisplayName);
			trusted.AddString(buffer);
			SetDlgItemInt(IDC_STATUT,i,0);
			WriteData(i,lpservice[i].lpServiceName,lpservice[i].lpDisplayName);
		}
	}
	CloseServiceHandle(sc);
}

void CServicesScannerDlg::OnAboutbox()
{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
}

void CServicesScannerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

int CServicesScannerDlg::WriteData(int index, LPCSTR NomService, LPCSTR NomAffiche)
{
	char buff[260];
	char clef[260];
	wsprintf(buff,"%d",index);
	WritePrivateProfileString("Fiables","index",buff,config);
	wsprintf(clef,"n%.7d",index);
	WritePrivateProfileString("Fiables",clef,NomService,config);
	wsprintf(clef,"a%.7d",index);
	WritePrivateProfileString("Fiables",clef,NomAffiche,config);
	return 0;
}
