// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#if !defined(_WIN32_IE)
#define _WIN32_IE 0x0600
#endif
#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT  0x503
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <ole2.h>          
#include <shlobj.h>
#include <olectl.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include ".\icon.h"
#pragma comment(lib,"comctl32")
#pragma comment(lib,"shlwapi")
#pragma comment(lib, "oleaut32.lib")
