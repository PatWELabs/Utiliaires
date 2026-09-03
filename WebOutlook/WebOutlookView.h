// WebOutlookView.h : interface de la classe CWebOutlookView
//


#pragma once


class CWebOutlookView : public CHtmlView
{
protected: // création à partir de la sérialisation uniquement
	CWebOutlookView();
	DECLARE_DYNCREATE(CWebOutlookView)

// Attributs
public:
	CWebOutlookDoc* GetDocument() const;

// Opérations
public:

// Substitutions
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // premier appel après la construction

// Implémentation
public:
	virtual ~CWebOutlookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // version de débogage dans WebOutlookView.cpp
inline CWebOutlookDoc* CWebOutlookView::GetDocument() const
   { return reinterpret_cast<CWebOutlookDoc*>(m_pDocument); }
#endif

