// Time2DecaDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "Time2Deca.h"
#include "Time2DecaDlg.h"
#include ".\time2decadlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int h,m,s;
char t[80];

// boîte de dialogue CTime2DecaDlg



CTime2DecaDlg::CTime2DecaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTime2DecaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTime2DecaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTime2DecaDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnEnChangeEdit3)
END_MESSAGE_MAP()


// gestionnaires de messages pour CTime2DecaDlg

BOOL CTime2DecaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	ReInitialiser();
	
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône. Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CTime2DecaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CTime2DecaDlg::OnQueryDragIcon(){return static_cast<HCURSOR>(m_hIcon);}
void CTime2DecaDlg::OnBnClickedOk(){
    GetDlgItemText(IDC_EDIT1,t,3);h=atoi(t);SetDlgItemInt(IDC_EDIT5,h*3600,1);
    GetDlgItemText(IDC_EDIT2,t,3);m=atoi(t);SetDlgItemInt(IDC_EDIT6,m*60,1);
    GetDlgItemText(IDC_EDIT3,t,3);s=atoi(t);SetDlgItemInt(IDC_EDIT7,s,1);
	sprintf(t,"%d.000000",(h*3600)+(m*60)+s);	SetDlgItemText(IDC_EDIT4,t);
}

void CTime2DecaDlg::ReInitialiser(void){    SetDlgItemText(IDC_EDIT1,"0");    SetDlgItemText(IDC_EDIT2,"0");    SetDlgItemText(IDC_EDIT3,"0");}
void CTime2DecaDlg::OnEnChangeEdit1(){GetDlgItemText(IDC_EDIT1,t,3);h=atoi(t);SetDlgItemInt(IDC_EDIT5,h*3600,1);}
void CTime2DecaDlg::OnEnChangeEdit2(){GetDlgItemText(IDC_EDIT2,t,3);m=atoi(t);SetDlgItemInt(IDC_EDIT6,m*60,1);}
void CTime2DecaDlg::OnEnChangeEdit3(){GetDlgItemText(IDC_EDIT3,t,3);s=atoi(t);SetDlgItemInt(IDC_EDIT7,s,1);}
