#include "StdAfx.h"
#include ".\icon.h"

TIcon::TIcon(void){}
TIcon::~TIcon(void){}
UINT TIcon::WriteIconHeader(HANDLE hFile, int nImages){
    ICONHEADER iconheader;
    DWORD nWritten;
    iconheader.idReserved = 0;
    iconheader.idType = 1;
    iconheader.idCount = nImages; 
    WriteFile( hFile, &iconheader, sizeof(iconheader), &nWritten, 0);
    return nWritten;
}

UINT TIcon::NumBitmapBytes(BITMAP *pBitmap){
    int nWidthBytes = pBitmap->bmWidthBytes;
    if(nWidthBytes & 3)  nWidthBytes = (nWidthBytes + 4) & ~3;
    return nWidthBytes * pBitmap->bmHeight;
}

UINT TIcon::WriteIconImageHeader(HANDLE hFile, BITMAP *pbmpColor, BITMAP *pbmpMask){
    BITMAPINFOHEADER biHeader;
    DWORD nWritten;
    UINT nImageBytes;
    nImageBytes = NumBitmapBytes(pbmpColor) + NumBitmapBytes(pbmpMask);
    ZeroMemory(&biHeader, sizeof(biHeader));
    biHeader.biSize = sizeof(biHeader);
    biHeader.biWidth = pbmpColor->bmWidth;
    biHeader.biHeight = pbmpColor->bmHeight * 2;
    biHeader.biPlanes = pbmpColor->bmPlanes;
    biHeader.biBitCount = pbmpColor->bmBitsPixel;
    biHeader.biSizeImage = nImageBytes;
    WriteFile(hFile, &biHeader, sizeof(biHeader), &nWritten, 0);
    if(pbmpColor->bmBitsPixel == 2 || pbmpColor->bmBitsPixel == 8)
    { }
    return nWritten;
}

BOOL TIcon::GetIconBitmapInfo(HICON hIcon, ICONINFO *pIconInfo, BITMAP *pbmpColor, BITMAP *pbmpMask){
    if(!GetIconInfo(hIcon, pIconInfo)) return FALSE;
    if(!GetObject(pIconInfo->hbmColor, sizeof(BITMAP), pbmpColor))return FALSE;
    if(!GetObject(pIconInfo->hbmMask, sizeof(BITMAP), pbmpMask))return FALSE;
    return TRUE;
}

UINT TIcon::WriteIconDirectoryEntry(HANDLE hFile, int nIdx, HICON hIcon, UINT nImageOffset){
    ICONINFO iconInfo;
    ICONDIR iconDir;
    BITMAP bmpColor,bmpMask;
    DWORD nWritten;
    UINT nColorCount,nImageBytes;
    GetIconBitmapInfo(hIcon, &iconInfo, &bmpColor, &bmpMask);
    nImageBytes = NumBitmapBytes(&bmpColor) + NumBitmapBytes(&bmpMask);
    if(bmpColor.bmBitsPixel >= 8)   nColorCount = 0;
    else  nColorCount = 1 << (bmpColor.bmBitsPixel * bmpColor.bmPlanes);
    iconDir.bWidth = (BYTE)bmpColor.bmWidth;
    iconDir.bHeight = (BYTE)bmpColor.bmHeight;
    iconDir.bColorCount = nColorCount;
    iconDir.bReserved = 0;
    iconDir.wPlanes = bmpColor.bmPlanes;
    iconDir.wBitCount = bmpColor.bmBitsPixel;
    iconDir.dwBytesInRes = sizeof(BITMAPINFOHEADER) + nImageBytes;
    iconDir.dwImageOffset = nImageOffset;
    WriteFile(hFile, &iconDir, sizeof(iconDir), &nWritten, 0);
    DeleteObject(iconInfo.hbmColor);
    DeleteObject(iconInfo.hbmMask);
    return nWritten;
}

UINT TIcon::WriteIconData(HANDLE hFile, HBITMAP hBitmap){
    BITMAP bmp;
    int i;
    BYTE * pIconData;
    UINT nBitmapBytes;
    DWORD nWritten;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);
    nBitmapBytes = NumBitmapBytes(&bmp);
    pIconData = (BYTE *)malloc(nBitmapBytes);
    GetBitmapBits(hBitmap, nBitmapBytes, pIconData);
    for(i = bmp.bmHeight - 1; i >= 0; i--)   {
        WriteFile(hFile,pIconData + (i * bmp.bmWidthBytes),bmp.bmWidthBytes, &nWritten, 0);
        if(bmp.bmWidthBytes & 3)  {  DWORD padding = 0;  WriteFile(hFile, &padding, 4 - bmp.bmWidthBytes, &nWritten, 0); }
    }
    free(pIconData);
    return nBitmapBytes;
}

BOOL TIcon::SaveIcon3(TCHAR *szIconFile, HICON hIcon[], int nNumIcons){
    HANDLE hFile;
    int i;
    int * pImageOffset;
    if(hIcon == 0 || nNumIcons < 1)  return FALSE;
    hFile = CreateFile(szIconFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if(hFile == INVALID_HANDLE_VALUE)  return FALSE;
    WriteIconHeader(hFile, nNumIcons);
    SetFilePointer(hFile, sizeof(ICONDIR) * nNumIcons, 0, FILE_CURRENT);
    pImageOffset = (int *)malloc(nNumIcons * sizeof(int));
    for(i = 0; i < nNumIcons; i++)   {
        ICONINFO iconInfo;
        BITMAP bmpColor, bmpMask;
        GetIconBitmapInfo(hIcon[i], &iconInfo, &bmpColor, &bmpMask);
        pImageOffset[i] = SetFilePointer(hFile, 0, 0, FILE_CURRENT);
        WriteIconImageHeader(hFile, &bmpColor, &bmpMask);
        WriteIconData(hFile, iconInfo.hbmColor);
        WriteIconData(hFile, iconInfo.hbmMask);
        DeleteObject(iconInfo.hbmColor);
        DeleteObject(iconInfo.hbmMask);
    }
    SetFilePointer(hFile, sizeof(ICONHEADER), 0, FILE_BEGIN);
    for(i = 0; i < nNumIcons; i++){   WriteIconDirectoryEntry(hFile, i, hIcon[i], pImageOffset[i]);  }
    free(pImageOffset);
    CloseHandle(hFile);
    return TRUE;
}


int TIcon::SaveIcon(TCHAR* filename, TCHAR* iconFile) {
    HICON hIconLarge;
    HICON hIconSmall;
    BOOL ret;
    if ( ExtractIconEx(filename, 0, &hIconLarge, &hIconSmall, 1) == 0 ) {       return 1;    }
    ret = SaveIcon3(iconFile, &hIconSmall, 1);
    if ( ret ) {  return 0;    }
    return -1;
}

