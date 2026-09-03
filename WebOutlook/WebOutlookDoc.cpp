// WebOutlookDoc.cpp : implémentation de la classe CWebOutlookDoc
//

#include "stdafx.h"
#include "WebOutlook.h"

#include "WebOutlookDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWebOutlookDoc

IMPLEMENT_DYNCREATE(CWebOutlookDoc, CDocument)

BEGIN_MESSAGE_MAP(CWebOutlookDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CWebOutlookDoc, CDocument)
END_DISPATCH_MAP()

// Remarque : La prise en charge de IID_IWebOutlook a été ajoutée afin de prendre en charge la liaison de type sécurisé
//  fournie par VBA. Cet IID doit correspondre au GUID qui est associé à
//  dispinterface dans le fichier .IDL.

// {386E986D-3157-4AAF-9B08-B249087403DB}
static const IID IID_IWebOutlook =
{ 0x386E986D, 0x3157, 0x4AAF, { 0x9B, 0x8, 0xB2, 0x49, 0x8, 0x74, 0x3, 0xDB } };

BEGIN_INTERFACE_MAP(CWebOutlookDoc, CDocument)
	INTERFACE_PART(CWebOutlookDoc, IID_IWebOutlook, Dispatch)
END_INTERFACE_MAP()


// construction ou destruction de CWebOutlookDoc

CWebOutlookDoc::CWebOutlookDoc()
{
	// TODO : ajoutez ici le code d'une construction unique

	EnableAutomation();

	AfxOleLockApp();
}

CWebOutlookDoc::~CWebOutlookDoc()
{
	AfxOleUnlockApp();
}

BOOL CWebOutlookDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO : ajoutez ici le code de réinitialisation
	// (les documents SDI réutiliseront ce document)

	return TRUE;
}




// sérialisation de CWebOutlookDoc

void CWebOutlookDoc::Serialize(CArchive& ar)
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


// diagnostics pour CWebOutlookDoc

#ifdef _DEBUG
void CWebOutlookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWebOutlookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// commandes pour CWebOutlookDoc
