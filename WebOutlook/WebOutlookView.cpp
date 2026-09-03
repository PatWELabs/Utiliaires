// WebOutlookView.cpp : implémentation de la classe CWebOutlookView
//

#include "stdafx.h"
#include "WebOutlook.h"

#include "WebOutlookDoc.h"
#include "WebOutlookView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWebOutlookView

IMPLEMENT_DYNCREATE(CWebOutlookView, CHtmlView)

BEGIN_MESSAGE_MAP(CWebOutlookView, CHtmlView)
	// Commandes d'impression standard
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

// construction ou destruction de CWebOutlookView

CWebOutlookView::CWebOutlookView()
{
	EnableActiveAccessibility();
	// TODO : ajoutez ici le code d'une construction

}

CWebOutlookView::~CWebOutlookView()
{
}

BOOL CWebOutlookView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO : Changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

void CWebOutlookView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	Navigate2(_T("https://outlook.live.com/owa/?id=64855&owa=1&owasuffix=owa%2f&path=/mail/inbox"),NULL,NULL);
}


// impression de CWebOutlookView



// diagnostics pour CWebOutlookView

#ifdef _DEBUG
void CWebOutlookView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CWebOutlookView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CWebOutlookDoc* CWebOutlookView::GetDocument() const // la version non déboguée est en ligne
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWebOutlookDoc)));
	return (CWebOutlookDoc*)m_pDocument;
}
#endif //_DEBUG


// gestionnaires de messages pour CWebOutlookView
