#pragma once
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

typedef struct{    WORD idReserved,idType,idCount; } ICONHEADER;
typedef struct{
    BYTE bWidth,bHeight,bColorCount,bReserved;
    WORD wPlanes,wBitCount;
    DWORD dwBytesInRes,dwImageOffset;
} ICONDIR;
typedef struct{   BITMAPINFOHEADER biHeader; } ICONIMAGE;

class TIcon
{
public:
	TIcon(void);
	~TIcon(void);
	UINT WriteIconHeader(HANDLE hFile, int nImages);
	UINT NumBitmapBytes(BITMAP *pBitmap);
	UINT WriteIconImageHeader(HANDLE hFile, BITMAP *pbmpColor, BITMAP *pbmpMask);
	BOOL GetIconBitmapInfo(HICON hIcon, ICONINFO *pIconInfo, BITMAP *pbmpColor, BITMAP *pbmpMask);
	UINT WriteIconDirectoryEntry(HANDLE hFile, int nIdx, HICON hIcon, UINT nImageOffset);
	UINT WriteIconData(HANDLE hFile, HBITMAP hBitmap);
	BOOL SaveIcon3(TCHAR *szIconFile, HICON hIcon[], int nNumIcons);
	int SaveIcon(TCHAR* filename, TCHAR* iconFile);
};
/*int _tmain(int argc, TCHAR* argv[]) {
    if ( argc < 3 ) {
        printf("Usage: <exe/dll file> <output ico file>");
        return EXIT_FAILURE;
    }
    _tprintf(_T("src = %s\n"), argv[1]);
    _tprintf(_T("dest = %s\n"), argv[2]);
    saveIcon(argv[1], argv[2]);

    return 0;
}*/