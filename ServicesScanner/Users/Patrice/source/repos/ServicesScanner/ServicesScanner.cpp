// ServicesScanner.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ServicesScanner.h"
#include "ServicesScannerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServicesScannerApp

BEGIN_MESSAGE_MAP(CServicesScannerApp, CWinApp)
	//{{AFX_MSG_MAP(CServicesScannerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServicesScannerApp construction

CServicesScannerApp::CServicesScannerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CServicesScannerApp object

CServicesScannerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CServicesScannerApp initialization

BOOL CServicesScannerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

	CServicesScannerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
