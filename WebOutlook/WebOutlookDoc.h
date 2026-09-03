// WebOutlookDoc.h : interface de la classe CWebOutlookDoc
//


#pragma once

class CWebOutlookDoc : public CDocument
{
protected: // création à partir de la sérialisation uniquement
	CWebOutlookDoc();
	DECLARE_DYNCREATE(CWebOutlookDoc)

// Attributs
public:

// Opérations
public:

// Substitutions
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implémentation
public:
	virtual ~CWebOutlookDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()

	// Fonctions générées de la table des répartitions OLE

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


