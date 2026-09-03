// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#define BUFFER 8192  
#define RRF_RT_ANY 0x0000ffff

#pragma once
#include <Windows.h>
#include <WinSvc.h>
#include <Winreg.h>
#include <iostream>
#include <tchar.h>
#include <Shlwapi.h>

#pragma comment (lib,"Shlwapi.lib")
#pragma comment (lib,"Advapi32.lib")
typedef int (__cdecl *MYPROC)(LPWSTR); 


// TODO: reference additional headers your program requires here
