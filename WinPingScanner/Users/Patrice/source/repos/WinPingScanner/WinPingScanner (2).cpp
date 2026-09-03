// WinPingScanner.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define ICMP_ECHO_REPLY 0
#define ICMP_DEST_UNREACH 3
#define ICMP_TTL_EXPIRE 11
#define ICMP_ECHO_REQUEST 8
#define MAX_LOADSTRING 100
#define ICMP_MIN 8
#define DEFAULT_PACKET_SIZE 32
#define DEFAULT_TTL 30
#define MAX_PING_DATA_SIZE 1024
#define MAX_PING_PACKET_SIZE (MAX_PING_DATA_SIZE + sizeof(IPHeader))
#define INFO_BUFFER_SIZE 1024
#pragma comment(lib,"ws2_32")

// Global Variables:
HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING],szWindowClass[MAX_LOADSTRING];
HWND hListe;
WNDCLASSEX wcex;
HWND hWnd;
DWORD i;
TCHAR  infoBuf[INFO_BUFFER_SIZE];
DWORD  bufCharCount = INFO_BUFFER_SIZE;
char buf[256];

struct IPHeader {BYTE h_len:4;BYTE version:4;BYTE tos;USHORT total_len;USHORT ident;USHORT flags;BYTE ttl;BYTE proto;USHORT checksum;ULONG source_ip;ULONG dest_ip;};
struct ICMPHeader {BYTE type;BYTE code;USHORT checksum;USHORT id;USHORT seq;ULONG timestamp; };

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcIP(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
USHORT ip_checksum(USHORT* buffer, int size);
int setup_for_ping(char* host, int ttl, SOCKET& sd, sockaddr_in& dest);
int send_ping(SOCKET sd, const sockaddr_in& dest,ICMPHeader* send_buf, int packet_size);
int recv_ping(SOCKET sd, sockaddr_in& source, IPHeader* recv_buf,int packet_size);
int decode_reply(IPHeader* reply, int bytes, sockaddr_in* from);
void init_ping_packet(ICMPHeader* icmp_hdr, int packet_size, int seq_no);
int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf,int packet_size);
int ScanneIP(char* argv);
void SendText2Box(char* Text);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR     lpCmdLine,int       nCmdShow){
	MSG msg;
	HACCEL hAccelTable;
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINPINGSCANNER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	if (!InitInstance (hInstance, nCmdShow)) {return FALSE;	}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_WINPINGSCANNER);
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {TranslateMessage(&msg);DispatchMessage(&msg);}
	}return msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_WINPINGSCANNER);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)CreateSolidBrush(RGB(128,128,128));
	wcex.lpszMenuName	= (LPCSTR)IDC_WINPINGSCANNER;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	return RegisterClassEx(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
	RECT rc;
	hInst = hInstance;
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION|WS_SYSMENU|WS_THICKFRAME| DS_CENTER,CW_USEDEFAULT, CW_USEDEFAULT, 480, 320, NULL, NULL, hInstance, NULL);
	if (!hWnd) {      return FALSE;   }
	hListe = CreateWindow("LISTBOX", "",WS_CHILD|WS_VISIBLE|WS_THICKFRAME/**/,0, 0, 400, 250, hWnd, (HMENU)1000, hInstance, NULL);
	GetClientRect(hListe,&rc);
	MoveWindow(hWnd,rc.left,rc.top,rc.right+32,rc.bottom+32,1);
	SendMessage( hListe,LB_RESETCONTENT,0,0 );
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	switch (message) 	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			switch (wmId){
	
			case ID_IPSCAN:
					wsprintf(szHello,"WinPingScanner est un outil réseau et ne doit pas etre détourné");
					SendText2Box(szHello);
				   DialogBox(hInst, (LPCTSTR)IDD_DIALOG_IP, hWnd, (DLGPROC)DlgProcIP);
				   break;
			case IDM_ABOUT:
					wsprintf(szHello,"WinPingScanner est un outil réseau et ne doit pas etre détourné");
					SendText2Box(szHello);
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			RECT rt;
			GetClientRect(hWnd, &rt);
		//	DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:{
		char buff[256];
		SYSTEM_INFO siSysInfo;
		GetSystemInfo(&siSysInfo); 
		wsprintf(buff,"OEM ID: %d\n", siSysInfo.dwOemId);
		SendMessage( GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING,0,(LPARAM)buff );
		wsprintf(buff,"Number of processors: d\n", siSysInfo.dwNumberOfProcessors); 
		SendMessage( GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING,0,(LPARAM)buff );
		wsprintf(buff,"Page size: %d\n", siSysInfo.dwPageSize); 
		SendMessage( GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING,0,(LPARAM)buff );
		wsprintf(buff,"Processor type: %d\n", siSysInfo.dwProcessorType); 
		SendMessage( GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING,0,(LPARAM)buff );
		wsprintf(buff,"Minimum application address: %d\n", siSysInfo.lpMinimumApplicationAddress); 
		SendMessage( GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING,0,(LPARAM)buff );
		wsprintf(buff,"Maximum application address: %d\n",siSysInfo.lpMaximumApplicationAddress); 
		SendMessage( GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING,0,(LPARAM)buff );
		wsprintf(buff,"Active processor mask: %d\n",siSysInfo.dwActiveProcessorMask); 
		SendMessage( GetDlgItem(hDlg,IDC_LIST1),LB_ADDSTRING,0,(LPARAM)buff );
		   }
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
USHORT ip_checksum(USHORT* buffer, int size) {
    unsigned long cksum = 0;
    while (size > 1) {cksum += *buffer++; size -= sizeof(USHORT);}
    if (size) { cksum += *(UCHAR*)buffer;  }
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >> 16);
    return (USHORT)(~cksum);
}
int recv_ping(SOCKET sd, sockaddr_in& source, IPHeader* recv_buf,int packet_size){
    int fromlen = sizeof(source);
    int bread = recvfrom(sd, (char*)recv_buf, packet_size + sizeof(IPHeader), 0,(sockaddr*)&source, &fromlen);
    if (bread == SOCKET_ERROR) {
        	SendText2Box("read failed: ");
			if (WSAGetLastError() == WSAEMSGSIZE) {	SendText2Box("buffer too small");
        }else {
            SendText2Box((LPSTR)(int)WSAGetLastError() );
        }
        return -1;
    }
    return 0;
}
int decode_reply(IPHeader* reply, int bytes, sockaddr_in* from){
    unsigned short header_len = reply->h_len * 4;
    ICMPHeader* icmphdr = (ICMPHeader*)((char*)reply + header_len);
    if (bytes < header_len + ICMP_MIN) {  
	wsprintf(buf,"too few bytes from %s", inet_ntoa(from->sin_addr) );       return -1;    }
    else if (icmphdr->type != ICMP_ECHO_REPLY) {
        if (icmphdr->type != ICMP_TTL_EXPIRE) {
            if (icmphdr->type == ICMP_DEST_UNREACH) {SendText2Box("Destination unreachable");}else {
				wsprintf(buf,"Unknown ICMP packet type %d received",int(icmphdr->type) );SendText2Box(buf);  return -1;
        }
    }
    else if (icmphdr->id != (USHORT)GetCurrentProcessId()) { return -2;   }
    int nHops = int(256 - reply->ttl);
    if (nHops == 192) {nHops = 1; }
    else if (nHops == 128) {nHops = 0; }
		wsprintf(buf,"bytes from %s  icmp_seq %d" , inet_ntoa(from->sin_addr),icmphdr->seq );SendText2Box(buf); 
		if (icmphdr->type == ICMP_TTL_EXPIRE) {SendText2Box("TTL expired."); 
		} else {
			wsprintf(buf,"Hop:%d time:%d ms.",nHops ,(nHops == 1 ? "" : "s,  ") , (GetTickCount() - icmphdr->timestamp));SendText2Box(buf);} 
    }

    return 0;
}int setup_for_ping(char* host, int ttl, SOCKET& sd, sockaddr_in& dest){
    sd = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, 0, 0, 0);
    if (sd == INVALID_SOCKET) {cerr << "Failed to create raw socket: " << WSAGetLastError() <<endl; return -1;}
    if (setsockopt(sd, IPPROTO_IP, IP_TTL, (const char*)&ttl, sizeof(ttl)) == SOCKET_ERROR) {wsprintf(buf,"TTL setsockopt failed:  %d ",WSAGetLastError() );SendText2Box(buf); return -1;}
    memset(&dest, 0, sizeof(dest));
    unsigned int addr = inet_addr(host);
    if (addr != INADDR_NONE) {dest.sin_addr.s_addr = addr;dest.sin_family = AF_INET;}
    else {
        hostent* hp = gethostbyname(host);
        if (hp != 0) {memcpy(&(dest.sin_addr), hp->h_addr, hp->h_length);dest.sin_family = hp->h_addrtype;}
        else {
	//		wsprintf(buf,"Unknown ICMP packet type %d received",int(icmphdr->type) );SendText2Box(buf);
			wsprintf(buf,"Failed to resolve %s", host );SendText2Box(buf);
             return -1;
        }
    }
    return 0;
}

void init_ping_packet(ICMPHeader* icmp_hdr, int packet_size, int seq_no){
    icmp_hdr->type = ICMP_ECHO_REQUEST;
    icmp_hdr->code = 0;
    icmp_hdr->checksum = 0;
    icmp_hdr->id = (USHORT)GetCurrentProcessId();
    icmp_hdr->seq = seq_no;
    icmp_hdr->timestamp = GetTickCount();
    const unsigned long int deadmeat = 0xDEADBEEF;
    char* datapart = (char*)icmp_hdr + sizeof(ICMPHeader);
    int bytes_left = packet_size - sizeof(ICMPHeader);
    while (bytes_left > 0) { memcpy(datapart, &deadmeat, min(int(sizeof(deadmeat)),bytes_left));
        bytes_left -= sizeof(deadmeat);
        datapart += sizeof(deadmeat);
    }
    icmp_hdr->checksum = ip_checksum((USHORT*)icmp_hdr, packet_size);
}

int send_ping(SOCKET sd, const sockaddr_in& dest, ICMPHeader* send_buf,int packet_size){
    cout << "Sending " << packet_size << " bytes to " <<inet_ntoa(dest.sin_addr) << "..." << flush;
    int bwrote = sendto(sd, (char*)send_buf, packet_size, 0,(sockaddr*)&dest, sizeof(dest));
    if (bwrote == SOCKET_ERROR) {cerr << "send failed: " << WSAGetLastError() << endl;return -1;    }
    else if (bwrote < packet_size) {     cout << "sent " << bwrote << " bytes..." << flush;    }
    return 0;
}
int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf,int packet_size){
    send_buf = (ICMPHeader*)new char[packet_size];  
    if (send_buf == 0) {cerr << "Failed to allocate output buffer." << endl;        return -1;    }
    recv_buf = (IPHeader*)new char[MAX_PING_PACKET_SIZE];
    if (recv_buf == 0) {   cerr << "Failed to allocate output buffer." << endl;        return -1;    }
    return 0;
}

int ScanneIP(char* argv){
    int seq_no = 0;
    ICMPHeader* send_buf = 0;
    IPHeader* recv_buf = 0;
    int packet_size = DEFAULT_PACKET_SIZE;
    int ttl = DEFAULT_TTL;
    int temp = DEFAULT_PACKET_SIZE;  if (temp != 0) {packet_size = temp;}
    packet_size = max(sizeof(ICMPHeader), min(MAX_PING_DATA_SIZE, (unsigned int)packet_size));
    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) {   cerr << "Failed to find Winsock 2.1 or better." << endl;  return 1;    }
    SOCKET sd;
	sockaddr_in dest, source;if (setup_for_ping(argv, ttl, sd, dest) < 0) {goto cleanup;}
	if (allocate_buffers(send_buf, recv_buf, packet_size) < 0) {goto cleanup;}
	init_ping_packet(send_buf, packet_size, seq_no);
	if (send_ping(sd, dest, send_buf, packet_size) >= 0) {
		while (1) {
            if (recv_ping(sd, source, recv_buf, MAX_PING_PACKET_SIZE) < 0) {
                unsigned short header_len = recv_buf->h_len * 4;
                ICMPHeader* icmphdr = (ICMPHeader*)((char*)recv_buf + header_len);
                if (icmphdr->seq != seq_no) {cerr << "bad sequence number!" << endl; continue;} else { break; }
            }
            if (decode_reply(recv_buf, packet_size, &source) != -2) {break;}
        }
    }
cleanup:
    delete[]send_buf;
    delete[]recv_buf;
    WSACleanup();
    return 0;
}
void SendText2Box(char* Text){SendMessage( hListe,LB_ADDSTRING,0,(LPARAM)Text );}
BOOL CALLBACK DlgProcIP(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG: {
			bufCharCount = INFO_BUFFER_SIZE;
			GetComputerName( infoBuf, &bufCharCount );SetDlgItemText(hwnd,IDC_USERNAME2,infoBuf ); 
			GetUserName( infoBuf, &bufCharCount );SetDlgItemText(hwnd,IDC_USERNAME,infoBuf );
	      return TRUE;
	}
	case WM_COMMAND:
	{
            switch(LOWORD(wParam))
            {
                case IDOK:
		{
		     DWORD ipAddress = 0;
		     char * TempIp,ServerIp;
		     struct in_addr addr;
 
		     SendDlgItemMessage(hwnd, IDC_IPADDRESS1, IPM_GETADDRESS, 0, (lParam) &ipAddress);
		     addr.s_addr = (long)ipAddress;
		     TempIp = inet_ntoa(addr);
		   //  strcpy(&ServerIp, TempIp);
					
		  //   
			 SetDlgItemText(hwnd, IDC_IPADDRESS1, inet_ntoa(addr));
 
		//     SendMessage(hWnd, WM_START_WINSOCK, 0, 0);
             EndDialog(hwnd, IDOK);
		     return true;
		}
            }
	    break;
	}
        default:
            return FALSE;
    }
    return TRUE;
}