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

// Assistant_GitView.h : interface de la classe CAssistant_GitView
//


#pragma once


class CAssistant_GitView : public CFormView
{
protected: // création à partir de la sérialisation uniquement
	CAssistant_GitView();
	DECLARE_DYNCREATE(CAssistant_GitView)

public:
	enum{ IDD = IDD_ASSISTANT_GIT_FORM };

// Attributs
public:
	CAssistant_GitDoc* GetDocument() const;

// Opérations
public:

// Substitutions
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
	virtual void OnInitialUpdate(); // premier appel après la construction

// Implémentation
public:
	virtual ~CAssistant_GitView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // version de débogage dans Assistant_GitView.cpp
inline CAssistant_GitDoc* CAssistant_GitView::GetDocument() const
   { return reinterpret_cast<CAssistant_GitDoc*>(m_pDocument); }
#endif

