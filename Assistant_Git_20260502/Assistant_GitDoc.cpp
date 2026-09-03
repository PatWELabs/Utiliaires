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

// Assistant_GitDoc.cpp : implémentation de la classe CAssistant_GitDoc
//

#include "stdafx.h"
#include "Assistant_Git.h"

#include "Assistant_GitDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAssistant_GitDoc

IMPLEMENT_DYNCREATE(CAssistant_GitDoc, CDocument)

BEGIN_MESSAGE_MAP(CAssistant_GitDoc, CDocument)
END_MESSAGE_MAP()


// construction ou destruction de CAssistant_GitDoc

CAssistant_GitDoc::CAssistant_GitDoc()
{
	// TODO : ajoutez ici le code d'une construction unique

}

CAssistant_GitDoc::~CAssistant_GitDoc()
{
}

BOOL CAssistant_GitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO : ajoutez ici le code de réinitialisation
	// (les documents SDI réutiliseront ce document)

	return TRUE;
}




// sérialisation de CAssistant_GitDoc

void CAssistant_GitDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO : ajoutez ici le code de stockage
	}
	else
	{
		// TODO : ajoutez ici le code de chargement
	}
}


// diagnostics pour CAssistant_GitDoc

#ifdef _DEBUG
void CAssistant_GitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAssistant_GitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// commandes pour CAssistant_GitDoc
