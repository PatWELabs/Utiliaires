// Time2Deca.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error inclut 'stdafx.h' avant d'inclure ce fichier pour PCH
#endif

#include "resource.h"		// symboles principaux


// CTime2DecaApp :
// Consultez Time2Deca.cpp pour l'implémentation de cette classe
//

class CTime2DecaApp : public CWinApp
{
public:
	CTime2DecaApp();

// Substitutions
	public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CTime2DecaApp theApp;
