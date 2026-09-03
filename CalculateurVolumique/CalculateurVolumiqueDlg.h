// CalculateurVolumiqueDlg.h : fichier d'en-tête
//

#pragma once


// boîte de dialogue CCalculateurVolumiqueDlg
class CCalculateurVolumiqueDlg : public CDialog
{
public:
	CCalculateurVolumiqueDlg(CWnd* pParent = NULL);	// constructeur standard

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATEURVOLUMIQUE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	char* Float2String(float valeur);
	afx_msg void OnBnClickedOk();
	void String2Matrice(int Item, int position);
	float mm3enM3(float valeur);
	void CalculeMatricePente();
	CComboBox pente1;
	CComboBox pente2;
	char* Int2String(float valeur);
	char* AffichePente(int Degre, int Position);
};
