// TraceReseau.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

// C program to display hostname
// and IP address
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <errno.h>
#include <sys/types.h>
#pragma comment(lib, "Ws2_32.lib")

void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}
void checkHostEntry(struct hostent* hostentry)
{
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}
void checkIPbuffer(char* IPbuffer)
{
    if (NULL == IPbuffer)
    {
        perror("inet_ntoa");
        exit(1);
    }
}

// Driver code
int main()
{
    char hostbuffer[256];
    char* IPbuffer;
    struct hostent* host_entry;
    int hostname;
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);
    IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));
    printf("IP: %s => %s\n", IPbuffer, hostbuffer);
    return 0;
}
