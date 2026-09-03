// ServiceSecureScanner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
SC_HANDLE sc;
char config[256];
char exe[260];
#define BUFFER 8192  
#define RRF_RT_ANY 0x0000ffff
typedef Service{
	LPCSTR NomService;
	LPCSTR NomAffiche;
	LPCSTR NomExe;
	DWORD   dwServiceType;
	DWORD   dwCurrentState;
	DWORD   dwState;
	DWORD   dwControlsAccepted;
	DWORD   dwWin32ExitCode;
	DWORD   dwServiceSpecificExitCode;
	DWORD   dwCheckPoint;
DWORD   dwWaitHint;
};

void ExtractRegExeInfo(LPCSTR NomService){
	char value[255];
	DWORD BufferSize = BUFFER;
	RegGetValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "SystemRoot", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);  
	std::cout << value << std::endl;  
	system("pause");  
 }

HKEY hKey; 
	LONG returnStatus; 
	DWORD dwType=REG_SZ;
	DWORD dwSize=255;
	char regKey[256];
	wsprintf(regKey,"SYSTEM\\CurrentControlSet\\Services\\%s",NomService);
	printf(regKey);
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, regKey, NULL,  KEY_ALL_ACCESS, &hKey);  
	RegQueryValueEx(hKey,"ImagePath", NULL, &dwType,(LPBYTE)&exe, &dwSize); 
	printf("\nExecutable: %s\n", exe); 
	RegCloseKey(hKey);
}

int WriteData(LPCSTR NomService, LPCSTR NomAffiche,	DWORD   dwServiceType,DWORD   dwCurrentState,DWORD   dwState,DWORD   dwControlsAccepted, DWORD   dwWin32ExitCode, DWORD   dwServiceSpecificExitCode, DWORD   dwCheckPoint,DWORD   dwWaitHint){
	char buffer[260];
	char buff[260];
	char clef[260];
	wsprintf(buffer,".\\config\\%s.inf",NomService);
	WritePrivateProfileString("Fiables","Affichage du service",NomAffiche,buffer);
	wsprintf(clef,"%.8d",dwState);
	WritePrivateProfileString("Fiables","Statuts",clef,buffer);
	wsprintf(clef,"%.8d",dwCurrentState);
	WritePrivateProfileString("Fiables","CurrentState",clef,buffer);
	wsprintf(clef,"%.8d",dwCheckPoint);
	WritePrivateProfileString("Fiables","CheckPoint",clef,buffer);
	wsprintf(clef,"%.8d",dwControlsAccepted);
	WritePrivateProfileString("Fiables","ControlsAccepted",clef,buffer);
	wsprintf(clef,"%.8d",dwServiceSpecificExitCode);
	WritePrivateProfileString("Fiables","ServiceSpecificExitCode",clef,buffer);
	wsprintf(clef,"%.8d",dwServiceType);
	WritePrivateProfileString("Fiables","ServiceType",clef,buffer);
	wsprintf(clef,"%.8d",dwWaitHint);
	WritePrivateProfileString("Fiables","WaitHint",clef,buffer);
	wsprintf(clef,"%.8d",dwWin32ExitCode);
	WritePrivateProfileString("Fiables","Win32ExitCode",clef,buffer);
	WritePrivateProfileString("Fiables","Executable",exe,buffer);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTitle("ServiceSecureScanner v:1.00 © ElectroNet 2016");
	GetCurrentDirectory(256,config);
	strcat(config,"\\ServicesScanner.inf");
	sc = ::OpenSCManager (NULL,NULL,SC_MANAGER_ENUMERATE_SERVICE);
	if (sc != NULL)	{
		ENUM_SERVICE_STATUS service_data, *lpservice;
		BOOL retVal;
		DWORD bytesNeeded,srvCount,resumeHandle = 0,srvType, srvState;
		srvType = SERVICE_WIN32;
		srvState = SERVICE_STATE_ALL;
		retVal = ::EnumServicesStatus (sc,srvType,srvState,&service_data,sizeof(service_data),
		&bytesNeeded,&srvCount,&resumeHandle);
		DWORD err = GetLastError();
		if ((retVal == FALSE) || err == ERROR_MORE_DATA){
			DWORD dwBytes = bytesNeeded + sizeof(ENUM_SERVICE_STATUS);
			lpservice = new ENUM_SERVICE_STATUS [dwBytes];
			EnumServicesStatus (sc,srvType,srvState,lpservice,dwBytes,&bytesNeeded,&srvCount,&resumeHandle);
		}
		char buffer[256];
		char clef[260];
		for(int i=0;i<srvCount;i++)	{
			printf("%.3d Nom du service : %s\nAffichage du service : %s \nStatuts:\nCurrentState %d\nCheckPoint %d\nControlsAccepted %d\nServiceSpecificExitCode %d\nServiceType %d\nWaitHint %d\nWin32ExitCode %d\n\n",i,lpservice[i].lpServiceName,lpservice[i].lpDisplayName,lpservice[i].ServiceStatus.dwCurrentState,lpservice[i].ServiceStatus.dwCheckPoint,lpservice[i].ServiceStatus.dwControlsAccepted,lpservice[i].ServiceStatus.dwServiceSpecificExitCode,lpservice[i].ServiceStatus.dwServiceType,lpservice[i].ServiceStatus.dwWaitHint,lpservice[i].ServiceStatus.dwWin32ExitCode);
			ExtractRegExeInfo(lpservice[i].lpServiceName);
			wsprintf(buffer,".\\config\\%s.inf",lpservice[i].lpServiceName);
			wsprintf(clef,"%.3d",i+1);
			WritePrivateProfileString("Fiables",clef,buffer,config);
			WriteData(lpservice[i].lpServiceName,lpservice[i].lpDisplayName,i	,lpservice[i].ServiceStatus.dwCurrentState,lpservice[i].ServiceStatus.dwCheckPoint,lpservice[i].ServiceStatus.dwControlsAccepted,lpservice[i].ServiceStatus.dwServiceSpecificExitCode,lpservice[i].ServiceStatus.dwServiceType,lpservice[i].ServiceStatus.dwWaitHint,lpservice[i].ServiceStatus.dwWin32ExitCode);
		}
	}
	return CloseServiceHandle(sc);
}

