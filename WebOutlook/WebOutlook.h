// WebOutlook.h : fichier d'en-tête principal pour l'application WebOutlook
//
#pragma once

#ifndef __AFXWIN_H__
	#error inclut 'stdafx.h' avant d'inclure ce fichier pour PCH
#endif

#include "resource.h"       // symboles principaux


// CWebOutlookApp :
// Consultez WebOutlook.cpp pour l'implémentation de cette classe
//

class CWebOutlookApp : public CWinApp
{
public:
	CWebOutlookApp();


// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation
	COleTemplateServer m_server;
		// Objet serveur pour la création de document
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWebOutlookApp theApp;
