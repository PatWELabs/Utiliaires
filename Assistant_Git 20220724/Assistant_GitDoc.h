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

// Assistant_GitDoc.h : interface de la classe CAssistant_GitDoc
//


#pragma once


class CAssistant_GitDoc : public CDocument
{
protected: // création à partir de la sérialisation uniquement
	CAssistant_GitDoc();
	DECLARE_DYNCREATE(CAssistant_GitDoc)

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
	virtual ~CAssistant_GitDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};


