#include <windows.h>
#include <sddl.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <exdisp.h>
#include <exdispid.h>
#include <commctrl.h>
#include <winsvc.h>
#include <cstdio>
#pragma comment(lib,"Comctl32")
#include <iostream.h>
void ErrorDescription(DWORD p_dwError);

int main()
{
    ENUM_SERVICE_STATUS service;
    
    DWORD dwBytesNeeded = 0;
    DWORD dwServicesReturned = 0;
    DWORD dwResumedHandle = 0;
    DWORD dwServiceType = SERVICE_WIN32 | SERVICE_DRIVER;
    SC_HANDLE hHandle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (NULL == hHandle) {
        ErrorDescription(GetLastError());
        return -1;
    }
    else {
        printf( "Open SCM sucessfully\n");
    }
    // Query services
    BOOL retVal = EnumServicesStatus(hHandle, dwServiceType, SERVICE_STATE_ALL, 
        &service, sizeof(ENUM_SERVICE_STATUS), &dwBytesNeeded, &dwServicesReturned,
        &dwResumedHandle);
    if (!retVal) {
        // Need big buffer
        if (ERROR_MORE_DATA == GetLastError()) {
            // Set the buffer
            DWORD dwBytes = sizeof(ENUM_SERVICE_STATUS) + dwBytesNeeded;
            ENUM_SERVICE_STATUS* pServices = NULL;
            pServices = new ENUM_SERVICE_STATUS [dwBytes];
            // Now query again for services
            EnumServicesStatus(hHandle, SERVICE_WIN32 | SERVICE_DRIVER, SERVICE_STATE_ALL, 
                pServices, dwBytes, &dwBytesNeeded, &dwServicesReturned, &dwResumedHandle);
            // now traverse each service to get information
            for (unsigned iIndex = 0; iIndex < dwServicesReturned; iIndex++) {
                
                cout << TEXT("Display Name") << (pServices + iIndex)->lpDisplayName << TEXT('\t');
                cout << TEXT("Service Name") << (pServices + iIndex)->lpServiceName << endl;                                    
            }
            delete [] pServices;
            pServices = NULL;
        }
        // there is any other reason
        else {
            ErrorDescription(GetLastError());
        }
    }
    if (!CloseServiceHandle(hHandle)) {
        ErrorDescription(GetLastError());
    }
    else {
        cout << "Close SCM sucessfully" << endl;
    }
    return 0;
}
// get the description of error
void ErrorDescription(DWORD p_dwError) {
    
    HLOCAL hLocal = NULL;
    
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
        NULL, p_dwError, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),(LPTSTR)&hLocal, 
        0, NULL);
    
    MessageBox(NULL, (LPCTSTR)LocalLock(hLocal), TEXT("Error"), MB_OK | MB_ICONERROR);
    LocalFree(hLocal);
}