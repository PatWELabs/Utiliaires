// CalculateurVolumiqueDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "math.h"
#include "CalculateurVolumique.h"
#include "CalculateurVolumiqueDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning(disable:4996)
WCHAR status;
	float excavation[24] = { 0 };
	float pente[12][1][1] = { 0,0,0 };

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

CCalculateurVolumiqueDlg::CCalculateurVolumiqueDlg(CWnd* pParent /*=nullptr*/): CDialog(IDD_CALCULATEURVOLUMIQUE_DIALOG, pParent){	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);}
void CCalculateurVolumiqueDlg::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX); DDX_Control(pDX, IDC_COMBO1, pente1);
	DDX_Control(pDX, IDC_COMBO2, pente2);
}
BEGIN_MESSAGE_MAP(CCalculateurVolumiqueDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCalculateurVolumiqueDlg::OnBnClickedOk)
END_MESSAGE_MAP()
BOOL CCalculateurVolumiqueDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	CreateStatusWindowW(WS_VISIBLE | WS_CHILD, L"©Patrice Waechter-Ebling 2023\tv:1.0.0.1\tPrototype", this->m_hWnd, 6000);
	CalculeMatricePente();
	return TRUE; 
}

void CCalculateurVolumiqueDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
void CCalculateurVolumiqueDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CCalculateurVolumiqueDlg::OnQueryDragIcon(){return static_cast<HCURSOR>(m_hIcon);}
char* CCalculateurVolumiqueDlg::Float2String(float valeur){char tmp[80];sprintf(tmp, "%F", valeur);return tmp;}
char* CCalculateurVolumiqueDlg::Int2String(float valeur){char tmp[80];sprintf(tmp, "%d",(int) valeur);return tmp;}
void CCalculateurVolumiqueDlg::String2Matrice(int Item, int position){	char data[25];	GetDlgItemText(Item, data, sizeof(data));	excavation[position] = atof(data);}
float CCalculateurVolumiqueDlg::mm3enM3(float valeur){return valeur/1000000000;}
char* CCalculateurVolumiqueDlg::AffichePente(int Degre, int Position){char tmp[80]; sprintf(tmp, "%d (1/%d)", Degre, Position); return tmp;}


void CCalculateurVolumiqueDlg::OnBnClickedOk()
{
	String2Matrice(IDC_EDIT1, 0); //diametre
	String2Matrice(IDC_EDIT4, 1); //longueur
	String2Matrice(IDC_EDIT2, 2); //Profondeur sommet tuyau
	String2Matrice(IDC_EDIT9, 3); // degagement tuyau

	String2Matrice(IDC_EDIT6, 12);//épaisseur couche2
	String2Matrice(IDC_EDIT7, 13);//épaisseur couche3
	String2Matrice(IDC_EDIT8, 14);//épaisseur couche4
	excavation[15] = excavation[12] * (excavation[0] + excavation[3]);
	excavation[16] = excavation[13] * (excavation[0] + excavation[3]);
	excavation[17] = excavation[14] * (excavation[0] + excavation[3]);
	excavation[4] = excavation[0] / 2; //rayon du tuyau
	excavation[5] = pow(excavation[4], 2) * 3.14159 * excavation[1]; //volume occupé par le tuyau
	SetDlgItemText(IDC_EDIT10, Float2String(mm3enM3(excavation[5]))); //convertion en m³
	excavation[6] = excavation[2] + excavation[0]; //hauteur top tuyau
	SetDlgItemText(IDC_EDIT3, Float2String(excavation[6])); //hauteur bas du tuyau
	String2Matrice(IDC_EDIT5, 7);//stocque l'epaisseur de l'assise
	excavation[8] = (excavation[0] + (excavation[3] * 2)) ; //largeur tranchee excavation
	excavation[9] = excavation[8] * excavation[1]; //surface tranchee excavation
	excavation[10] = excavation[9] * (excavation[7] + excavation[6]);//Volume excave incluant l'assise
	excavation[11] = ((excavation[0] + excavation[3]) * (excavation[0] + excavation[7])) - excavation[5] - (excavation[1] * excavation[7] * excavation[0]); //volume couche1
	SetDlgItemText(IDC_EDIT11, Float2String(mm3enM3(excavation[9] * excavation[7])));
	SetDlgItemText(IDC_EDIT15, Float2String(mm3enM3(excavation[11])));

}


void CCalculateurVolumiqueDlg::CalculeMatricePente()
{
	for (int x = 12; x>0; x--) {
		pente[x][0][0] =  45/x; //affiche la valeur en degrés
		pente1.AddString(AffichePente(pente[x][0][0], x));
		pente2.AddString(AffichePente(pente[x][0][0], x));
	}
}


