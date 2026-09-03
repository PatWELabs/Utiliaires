// RemoveService.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include <sddl.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <winsvc.h>

#define WIN32_LEAN_AND_MEAN
#define WIN32_WINNT  0x0500
#pragma comment(lib,"Advapi32")

static char *jours[7] = {"dimanche", "lundi","mardi","mercredi","jeudi","vendredi","samedi"};
static char *mois[12] = {"janvier", "f้vrier","mars", "avril", "mai", "juin","juillet","ao๛t","septembre", "octobre", "novembre", "d้cembre"};
SYSTEMTIME st;
SC_HANDLE   schService;
SC_HANDLE   schSCManager;
SERVICE_STATUS          ssStatus;
SERVICE_STATUS_HANDLE   sshStatusHandle;
DWORD                   dwErr = 0;
TCHAR                   szErr[256];

LPTSTR GetLastErrorText( LPTSTR lpszBuf, DWORD dwSize ){
	DWORD dwRet;
	LPTSTR lpszTemp = NULL;
	dwRet = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_ARGUMENT_ARRAY,NULL,GetLastError(),LANG_NEUTRAL,(LPTSTR)&lpszTemp,0,NULL );
	if ( !dwRet || ( (long)dwSize < (long)dwRet+14 ) )
		lpszBuf[0] = TEXT('\0');
	else	{		lpszTemp[lstrlen(lpszTemp)-2] = TEXT('\0');		_stprintf( lpszBuf, TEXT("%s (0x%x)"), lpszTemp, GetLastError() );	}
	if ( lpszTemp )LocalFree((HLOCAL) lpszTemp );
	return lpszBuf;
}

int main(int argc, char* argv[]){
	SetConsoleTitle("Moteur de Suppression pour Services");
	GetLocalTime(&st);
    printf("\nษออออออออออออออออออออออหอออออออออออออออออออออออออออออออออออออป\n");
    printf("บ                      บ                                     บ\n");
    printf("บ Version: 7.0.015.213 บ %c Patrice Wachter-Ebling 1995-2015  บ\n",184);
    printf("บ                      บ                                     บ\n");
    printf("ฬออออออออออออออออออออออฮอออออออออออออออออออออออออออออออออออออน\n");
    printf("บ                      บ                                     บ\n");
    printf("บ Il est %.2d:%.2d:%.2d      บ Nous sommes %s, le %2d %.3s %4d  บ\n",st.wHour,st.wMinute,st.wSecond,jours[st.wDayOfWeek],st.wDay,mois[st.wMonth-1],st.wYear);
    printf("บ                      บ                                     บ\n");
    printf("ศออออออออออออออออออออออสอออออออออออออออออออออออออออออออออออออผ\n");
   	if (argc<2){
        printf("\n\n\tษอออออออหอออออออออออออออออออออออออออออออออออออออออออออออออออออป\n");
        printf("\tบ       บ                                                     บ\n");
        printf("\tบ USAGE บ RemoveService nom_du_service nom_affiche_du service บ\n");
        printf("\tบ       บ                                                     บ\n");
        printf("\tศอออออออสอออออออออออออออออออออออออออออออออออออออออออออออออออออผ\n");
		return -1;
	}
    printf("\nNom du service เ tuer : %s\nNom affich้ du service : %s\n\n",__argv[1],__argv[1]);
	schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_CONNECT);
	if ( schSCManager ) {
		  schService = OpenService(schSCManager, __argv[1], DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS);
		  if (schService) {
			  if ( ControlService( schService, SERVICE_CONTROL_STOP, &ssStatus ) )  {
				  _tprintf(TEXT("Stopping %s."), __argv[1]);Sleep( 1000 );
				  while ( QueryServiceStatus( schService, &ssStatus ) ){
					  if ( ssStatus.dwCurrentState == SERVICE_STOP_PENDING ) { 
						  _tprintf(TEXT("."));Sleep( 1000 ); 
					  } else {  
						  break;
					}
					if ( ssStatus.dwCurrentState == SERVICE_STOPPED ){ 
						_tprintf(TEXT("\n%s stopped.\n"),__argv[1]);
					}else{
						_tprintf(TEXT("\n%s failed to stop.\n"), __argv[1]);
					}
					if ( DeleteService(schService) ){
						_tprintf(TEXT("%s removed.\n"), __argv[1] );
					}else{
						_tprintf(TEXT("DeleteService failed - %s\n"), GetLastErrorText(szErr,256));
					}
					CloseServiceHandle(schService);
				  }else{
					  _tprintf(TEXT("OpenService failed - %s\n"), GetLastErrorText(szErr,256));
				  }
				  CloseServiceHandle(schSCManager);
			  }else{
				  _tprintf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText(szErr,256));
			  }
			  return 0;
		  }
		  }
	  }
}
