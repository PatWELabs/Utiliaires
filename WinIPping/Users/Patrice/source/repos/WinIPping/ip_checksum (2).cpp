//ip_checksum.cpp

#include <windows.h>

USHORT ip_checksum(USHORT* buffer, int size) {
    unsigned long cksum = 0;
    while (size > 1) {        cksum += *buffer++;        size -= sizeof(USHORT);    }
    if (size) {        cksum += *(UCHAR*)buffer;    }
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >> 16);
    return (USHORT)(~cksum);
}
}