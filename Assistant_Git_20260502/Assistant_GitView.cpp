// Ce code source des exemples MFC illustre l'utilisation de l'interface utilisateur Microsoft Office Fluent MFC 
// (interface utilisateur "Fluent UI"). Il est fourni uniquement en tant que référence complémentaire du 
// Guide de référence Microsoft Foundation Classes et de la documentation électronique associée 
// inclus avec les logiciels de la bibliothèque MFC C++.  
// Les termes du contrat de licence pour la copie, l'utilisation ou la distribution de l'interface utilisateur Fluent sont disponibles séparément.  
// Pour en savoir plus sur notre programme de licence de l'interface utilisateur Fluent, visitez 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// Tous droits réservés.

// Assistant_GitView.cpp : implémentation de la classe CAssistant_GitView
//

#include "stdafx.h"
#include "Assistant_Git.h"

#include "Assistant_GitDoc.h"
#include "Assistant_GitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAssistant_GitView

IMPLEMENT_DYNCREATE(CAssistant_GitView, CFormView)

BEGIN_MESSAGE_MAP(CAssistant_GitView, CFormView)
END_MESSAGE_MAP()

// construction ou destruction de CAssistant_GitView

CAssistant_GitView::CAssistant_GitView()
	: CFormView(CAssistant_GitView::IDD)
{
	// TODO : ajoutez ici du code de construction

}

CAssistant_GitView::~CAssistant_GitView()
{
}

void CAssistant_GitView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CAssistant_GitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO : changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CAssistant_GitView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	MessageBox("Voulez vous Creer une application complete?",AfxGetApp()->m_pszAppName,MB_YESNO|MB_ICONQUESTION);
	ResizeParentToFit();

}

void CAssistant_GitView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAssistant_GitView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// diagnostics pour CAssistant_GitView

#ifdef _DEBUG
void CAssistant_GitView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAssistant_GitView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CAssistant_GitDoc* CAssistant_GitView::GetDocument() const // la version non Debug est inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAssistant_GitDoc)));
	return (CAssistant_GitDoc*)m_pDocument;
}
#endif //_DEBUG


// gestionnaires de messages pour CAssistant_GitView
