// ServicesScannerDlg.h : header file
//

#include "afxwin.h"
#include "afxcmn.h"
#if !defined(AFX_SERVICESSCANNERDLG_H__22B834CB_A5BB_4A25_8DD4_F25F493293DB__INCLUDED_)
#define AFX_SERVICESSCANNERDLG_H__22B834CB_A5BB_4A25_8DD4_F25F493293DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CServicesScannerDlg dialog

class CServicesScannerDlg : public CDialog
{
// Construction
public:
	CServicesScannerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CServicesScannerDlg)
	enum { IDD = IDD_SERVICESSCANNER_DIALOG };
	CListBox	m_scan;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServicesScannerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CServicesScannerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CListBox trusted;
	afx_msg void OnBnClickedButton1();
	CProgressCtrl progress;
	afx_msg void OnAboutbox();
	afx_msg void OnBnClickedOk();
	int WriteData(int index, LPCSTR NomService,LPCSTR NomAffiche);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICESSCANNERDLG_H__22B834CB_A5BB_4A25_8DD4_F25F493293DB__INCLUDED_)
