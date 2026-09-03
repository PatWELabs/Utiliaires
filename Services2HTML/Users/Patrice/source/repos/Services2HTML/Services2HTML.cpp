// Services2HTML.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
SC_HANDLE sc;
char config[256];
char exe[260];
struct Service{
	LPCSTR NomService;
	LPCSTR NomAffiche;
	LPCSTR NomExe;
	DWORD dwServiceType;
	DWORD dwCurrentState;
	DWORD dwState;
	DWORD dwControlsAccepted;
	DWORD dwWin32ExitCode;
	DWORD dwServiceSpecificExitCode;
	DWORD dwCheckPoint;
	DWORD   dwWaitHint;
};

struct reg2{
	char  Description[1024];
	char  DisplayName[1024];
	char  ImagePath[1024];
	char  ObjectName[1024];
	char  RequiredPrivileges[1024];
	char FilePath[1024];
};
HKEY hCle;
FILE *f;
reg2 rg;
Service svr;

int _tmain(int argc, _TCHAR* argv[]){
	SetConsoleTitle("Service2HTML Scanner v:1.00 © ElectroNet 2016");
	GetCurrentDirectory(256,config);
	strcat(config,"\\SecureServices.html");
	f=fopen(config,"w+");
	fprintf(f,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\"> 		<html><head><title>Services Fiables</title><meta name=\"GENERATOR\" content=\"Microsoft Visual Studio .NET 7.1\"><meta name=\"vs_targetSchema\" content=\"http://schemas.microsoft.com/intellisense/ie5\"></head><body> 		<TABLE id=\"Table1\" borderColor=\"aqua\" cellSpacing=\"1\" borderColorDark=\"fuchsia\" cellPadding=\"1\"borderColorLight=\"blue\" border=\"1\"> 		<TR><TD>Nom du Service</TD><TD>Nom Affiché</TD><TD>Execution</TD><TD>Type</TD><TD>CurrentState</TD><TD>State</TD><TD>Controls</TD><TD>ExitCode</TD><TD>SpecificExitCode</TD><TD>CheckPoint</TD><TD>WaitHint</TD><TD>ObjectName</TD><TD>RequiredPrivileges</TD></TR>");
	char regKey[256];
	DWORD dwType = REG_SZ;
	HKEY hKey = 0;
	DWORD value_length = 1024;
	printf( "Service Application Extracteur v:1.00\n%c Patrice Wächter-Ebling 2015-2016\n\n",184 );  

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
		for(int i=0;i<srvCount;i++)	{
			printf("%.3d Nom du service : %s\nAffichage du service : %s \nStatuts:\nCurrentState %d\nCheckPoint %d\nControlsAccepted %d\nServiceSpecificExitCode %d\nServiceType %d\nWaitHint %d\nWin32ExitCode %d\n\n",i,lpservice[i].lpServiceName,lpservice[i].lpDisplayName,lpservice[i].ServiceStatus.dwCurrentState,lpservice[i].ServiceStatus.dwCheckPoint,lpservice[i].ServiceStatus.dwControlsAccepted,lpservice[i].ServiceStatus.dwServiceSpecificExitCode,lpservice[i].ServiceStatus.dwServiceType,lpservice[i].ServiceStatus.dwWaitHint,lpservice[i].ServiceStatus.dwWin32ExitCode);
			svr.NomService=lpservice[i].lpServiceName;
			svr.NomAffiche=lpservice[i].lpDisplayName;
			svr.dwCurrentState=lpservice[i].ServiceStatus.dwCurrentState;
			svr.dwCheckPoint=lpservice[i].ServiceStatus.dwCheckPoint;
			svr.dwControlsAccepted=lpservice[i].ServiceStatus.dwControlsAccepted;
			svr.dwServiceSpecificExitCode=lpservice[i].ServiceStatus.dwServiceSpecificExitCode;
			svr.dwServiceType=lpservice[i].ServiceStatus.dwServiceType;
			svr.dwWaitHint=lpservice[i].ServiceStatus.dwWaitHint;
			svr.dwWin32ExitCode=lpservice[i].ServiceStatus.dwWin32ExitCode;
			wsprintf(regKey,"SYSTEM\\CurrentControlSet\\Services\\%s",lpservice[i].lpServiceName);
			printf("Service : %s\nRegistre : HKEY_LOCAL_MACHINE\\%s\n",lpservice[i].lpServiceName,regKey);
			RegOpenKey(HKEY_LOCAL_MACHINE,regKey,&hKey);
			RegQueryValueEx(hKey,"ObjectName" , NULL, &dwType, (LPBYTE)&rg.ObjectName, &value_length);
			RegQueryValueEx(hKey,"Description" , NULL, &dwType, (LPBYTE)&rg.Description, &value_length);
			RegQueryValueEx(hKey,"ImagePath" , NULL, &dwType, (LPBYTE)&rg.ImagePath, &value_length);
			RegQueryValueEx(hKey,"RequiredPrivileges" , NULL, &dwType, (LPBYTE)&rg.RequiredPrivileges, &value_length);
			svr.NomExe=rg.ImagePath;
			strcpy(rg.FilePath,rg.ImagePath);
			PathRemoveFileSpec(rg.FilePath);
			printf("Executable : %s\nAutorité : %s\nDescription : %s\nDisplayName : %s\nRequiredPrivileges : %s\nFilePath : %s\n",rg.ImagePath,rg.ObjectName,rg.Description,rg.DisplayName,rg.RequiredPrivileges,rg.FilePath);
			fprintf(f,"<TR><TD>%s</TD><TD>%s</TD><TD>%s</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD></TR>\n",svr.NomAffiche,svr.NomService,svr.NomExe,svr.dwServiceType,svr.dwCurrentState,svr.dwState,svr.dwControlsAccepted,svr.dwWin32ExitCode,svr.dwServiceSpecificExitCode,svr.dwCheckPoint,svr.dwWaitHint,rg.ObjectName,rg.RequiredPrivileges);
			printf("%s/Affichage du service %s\n",svr.NomService,svr.NomService);
			printf("%s/Nom du service %s\n",svr.NomService,svr.NomAffiche);
			printf("%s/Executable %s\n",svr.NomService,svr.NomExe);
			printf("%s/CheckPoint %d\n",svr.NomService,svr.dwCheckPoint);
			printf("%s/ControlsAccepted %d\n",svr.NomService,svr.dwControlsAccepted);
			printf("%s/ServiceSpecificExitCode %d\n",svr.NomService,svr.dwServiceSpecificExitCode);
			printf("%s/ServiceType %d\n",svr.NomService,svr.dwServiceType);
			printf("%s/WaitHint %d\n",svr.NomService,svr.dwWaitHint);
			printf("%s/Win32ExitCode %d\n",svr.NomService,svr.dwWin32ExitCode);
			printf("%s/CurrentState %d\n",svr.NomService,svr.dwCurrentState);
			printf("%s/Statuts %d\n",svr.NomService,svr.dwState);
		}
	}
	fprintf(f,"</TABLE></body></html>");
	return CloseServiceHandle(sc);

}

