// WinIPping.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <winnetwk.h>
#include <dhcpcsdk.h>

#pragma comment( lib, "dhcpcsvc.lib" )
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "mpr.lib")

struct IPv4 {    unsigned char b1, b2, b3, b4;};
BOOL WINAPI EnumerateFunc(LPNETRESOURCE lpnr);
void DisplayStruct(int i, LPNETRESOURCE lpnrLocal);
BOOL RetrieveHostName(LPWSTR  pszAdapterName, CHAR   pszHostNameBuf[],DWORD dwHostNameBufSize);
ULONG UpdateHostNameLoop(LPWSTR pszAdapterName,CHAR pszHostNameBuf[],ULONG dwHostBufSize);

bool getMyIP(IPv4 & myIP){
    char szBuffer[1024];
	WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);
    if(::WSAStartup(wVersionRequested, &wsaData) != 0)        return false;    
    if(gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)    {WSACleanup(); return false;    }
    struct hostent *host = gethostbyname(szBuffer);
    if(host == NULL)    { WSACleanup(); return false;    }
    myIP.b1 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b1;
    myIP.b2 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b2;
    myIP.b3 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b3;
    myIP.b4 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b4;
    WSACleanup();
    return true;
}

int main(int argc, char* argv[])
{
	SetConsoleTitle("Exploration Reseau");
	struct hostent *he;
	struct in_addr ipv4addr;
	char ips[20];
	IPv4 ip;
	ip.b1=192;
	ip.b2=168;
	ip.b3=2;
    WSADATA wsaData;

    LPNETRESOURCE lpnr = NULL;

    if (EnumerateFunc(lpnr) == FALSE) {
        printf("Call to EnumerateFunc failed\n");
        return 1;
    } else
        return 0;
	for (int x=0;x<256; x++){
		ip.b4=x;
		wsprintf(ips,"%d.%d.%d.%d\n",ip.b1,ip.b2,ip.b3,ip.b4);
	//	inet_pton(AF_INET, ip, &ipv4addr);
//		ipv4addr.S_un.S_addr=ip;
//		he = gethostbyaddr(ipv4addr, sizeof ipv4addr, AF_INET);
		printf("IP: %s: ID: %s\n",ips, he->h_name);		
		getMyIP(ip);
	}
	
	return 0;
}
BOOL WINAPI EnumerateFunc(LPNETRESOURCE lpnr){
    DWORD dwResult, dwResultEnum;
    HANDLE hEnum;
    DWORD cbBuffer = 16384; 
    DWORD cEntries = -1;   
    LPNETRESOURCE lpnrLocal;   
	DWORD i;
    dwResult = WNetOpenEnum(RESOURCE_GLOBALNET,RESOURCETYPE_ANY,0,lpnr,&hEnum); 
    if (dwResult != NO_ERROR) {
        printf("WnetOpenEnum failed with error %d\n", dwResult);
        return FALSE;
    }
    lpnrLocal = (LPNETRESOURCE) GlobalAlloc(GPTR, cbBuffer);
    if (lpnrLocal == NULL) {
        printf("WnetOpenEnum failed with error %d\n", dwResult);
        return FALSE;
    }
    do {
        ZeroMemory(lpnrLocal, cbBuffer);
        dwResultEnum = WNetEnumResource(hEnum,&cEntries,lpnrLocal,&cbBuffer); 
        if (dwResultEnum == NO_ERROR) {
            for (i = 0; i < cEntries; i++) {
                DisplayStruct(i, &lpnrLocal[i]);
                if (RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage& RESOURCEUSAGE_CONTAINER))
                    if (!EnumerateFunc(&lpnrLocal[i]))
                        printf("EnumerateFunc returned FALSE\n");
            }
        }
        else if (dwResultEnum != ERROR_NO_MORE_ITEMS) {
            printf("WNetEnumResource failed with error %d\n", dwResultEnum);
            break;
        }
    }
    while (dwResultEnum != ERROR_NO_MORE_ITEMS);
    GlobalFree((HGLOBAL) lpnrLocal);
    dwResult = WNetCloseEnum(hEnum);
    if (dwResult != NO_ERROR) {
        printf("WNetCloseEnum failed with error %d\n", dwResult);
        return FALSE;
    }
    return TRUE;
}

void DisplayStruct(int i, LPNETRESOURCE lpnrLocal)
{
    printf("NETRESOURCE[%d] Scope: ", i);
    switch (lpnrLocal->dwScope) {
    case (RESOURCE_CONNECTED):
        printf("connected\n");
        break;
    case (RESOURCE_GLOBALNET):
        printf("all resources\n");
        break;
    case (RESOURCE_REMEMBERED):
        printf("remembered\n");
        break;
    default:
        printf("unknown scope %d\n", lpnrLocal->dwScope);
        break;
    }

    printf("NETRESOURCE[%d] Type: ", i);
    switch (lpnrLocal->dwType) {
    case (RESOURCETYPE_ANY):
        printf("any\n");
        break;
    case (RESOURCETYPE_DISK):
        printf("disk\n");
        break;
    case (RESOURCETYPE_PRINT):
        printf("print\n");
        break;
    default:
        printf("unknown type %d\n", lpnrLocal->dwType);
        break;
    }

    printf("NETRESOURCE[%d] DisplayType: ", i);
    switch (lpnrLocal->dwDisplayType) {
    case (RESOURCEDISPLAYTYPE_GENERIC):
        printf("generic\n");
        break;
    case (RESOURCEDISPLAYTYPE_DOMAIN):
        printf("domain\n");
        break;
    case (RESOURCEDISPLAYTYPE_SERVER):
        printf("server\n");
        break;
    case (RESOURCEDISPLAYTYPE_SHARE):
        printf("share\n");
        break;
    case (RESOURCEDISPLAYTYPE_FILE):
        printf("file\n");
        break;
    case (RESOURCEDISPLAYTYPE_GROUP):
        printf("group\n");
        break;
    case (RESOURCEDISPLAYTYPE_NETWORK):
        printf("network\n");
        break;
    default:
        printf("unknown display type %d\n", lpnrLocal->dwDisplayType);
        break;
    }

    printf("NETRESOURCE[%d] Usage: 0x%x = ", i, lpnrLocal->dwUsage);
    if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONNECTABLE)
        printf("connectable ");
    if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONTAINER)
        printf("container ");
    printf("\n");

    printf("NETRESOURCE[%d] Localname: %S\n", i, lpnrLocal->lpLocalName);
    printf("NETRESOURCE[%d] Remotename: %S\n", i, lpnrLocal->lpRemoteName);
    printf("NETRESOURCE[%d] Comment: %S\n", i, lpnrLocal->lpComment);
    printf("NETRESOURCE[%d] Provider: %S\n", i, lpnrLocal->lpProvider);
    printf("\n");
}

BOOL RetrieveHostName(LPWSTR  pszAdapterName,CHAR   pszHostNameBuf[],DWORD dwHostNameBufSize){
    DWORD dwError, dwSize;
    CHAR TmpBuffer[1000];
	DHCPCAPI_PARAMS DhcpApiHostNameParams = {0,OPTION_HOST_NAME, FALSE,NULL,0}; 
    DHCPCAPI_PARAMS_ARRAY RequestParams = {1,&DhcpApiHostNameParams};
    DHCPCAPI_PARAMS_ARRAY SendParams = {0, NULL};
    dwSize = sizeof(TmpBuffer);
    dwError = DhcpRequestParams(DHCPCAPI_REQUEST_SYNCHRONOUS,NULL,pszAdapterName,NULL, SendParams, RequestParams,(PBYTE) TmpBuffer, &dwSize, NULL);
    if( ERROR_MORE_DATA == dwError ) { }
    if( NO_ERROR == dwError )     {
            if( DhcpApiHostNameParams.nBytesData )  {
                CopyMemory(pszHostNameBuf, DhcpApiHostNameParams.Data,DhcpApiHostNameParams.nBytesData);
                pszHostNameBuf[DhcpApiHostNameParams.nBytesData] = '\0';
                return TRUE;
            }
    }
    return FALSE;
}
ULONG UpdateHostNameLoop(LPWSTR pszAdapterName,CHAR pszHostNameBuf[], ULONG dwHostBufSize){
    DWORD dwError;
    HANDLE hEvent;
    DHCPCAPI_PARAMS DhcpApiHostNameParams = { 0, OPTION_HOST_NAME,FALSE,NULL,0};
    DHCPCAPI_PARAMS_ARRAY DhcpApiParamsArray = {1,&DhcpApiHostNameParams};
    dwError = DhcpRegisterParamChange(DHCPCAPI_REGISTER_HANDLE_EVENT,NULL, pszAdapterName, NULL,DhcpApiParamsArray,(LPVOID)&hEvent);
    if( ERROR_SUCCESS != dwError ) return dwError;
    while( WAIT_OBJECT_0 == WaitForSingleObject(hEvent, INFINITE) )     {
        ResetEvent(hEvent);
        dwError = RetrieveHostName(pszAdapterName, pszHostNameBuf, dwHostBufSize );
        break;
    }
    (void)DhcpDeRegisterParamChange(DHCPCAPI_REGISTER_HANDLE_EVENT,NULL, (LPVOID) hEvent);
    return dwError;
}