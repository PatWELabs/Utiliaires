#include "StdAfx.h"
#include <Windows.h>
#include <stdio.h>
#include <assert.h>
#include "tbitmap.h"

void errhandler(char* txt, HWND hwnd){ MessageBox(hwnd,txt,"TBitmap.Class.CreateBitmap",MB_OK|MB_ICONERROR);}
char* SetNameFormDate(){
	SYSTEMTIME st;
	char tmp[80];
	GetLocalTime(&st);
	sprintf(tmp,"%.4d-%.2d-%.2d_%.2d-%.2d-%.2d-%.2d.BMP",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	return tmp;
}
TBitmap::TBitmap(void){}
TBitmap::~TBitmap(void){}
PBITMAPINFO TBitmap::CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp){ 
	BITMAP bmp; 
	PBITMAPINFO pbmi; 
	WORD cClrBits; 
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) MessageBox(hwnd,"GetObject","TBitmap.Class.CreateBitmap",MB_OK|MB_ICONERROR); 
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
	if (cClrBits == 1) cClrBits = 1; 
	else if (cClrBits <= 4) cClrBits = 4; 
	else if (cClrBits <= 8) cClrBits = 8; 
	else if (cClrBits <= 16) cClrBits = 16; 
	else if (cClrBits <= 24) cClrBits = 24; 
	else					 cClrBits = 32; 
	if (cClrBits < 24) pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits)); 
	else 
	pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER)); 
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	pbmi->bmiHeader.biWidth = bmp.bmWidth; 
	pbmi->bmiHeader.biHeight = bmp.bmHeight; 
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
	if (cClrBits < 24)pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 
	pbmi->bmiHeader.biCompression = BI_RGB; 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8 * pbmi->bmiHeader.biHeight; 
	pbmi->bmiHeader.biClrImportant = 0; 
	return pbmi; 
} 
/*HRESULT TBitmap::WriteBitmap(HBITMAP bitmap, char* pathname) {
 HRESULT hr = S_OK;
 BITMAP bm_info = { 0 };
 if (!GetObject(bitmap, sizeof(bm_info), &bm_info)) hr = E_FAIL;
 IWICImagingFactory* factory = NULL;
 if (SUCCEEDED(hr))
 hr = CoCreateInstance(&CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, &IID_IWICImagingFactory, &factory);
 IWICBitmap* wic_bitmap = NULL;
 if (SUCCEEDED(hr))
 hr = IWICImagingFactory_CreateBitmapFromHBITMAP(factory, bitmap, NULL,
 WICBitmapIgnoreAlpha,
 &wic_bitmap);

 // (4) Create an IWICStream instance, and attach it to a filename.
 IWICStream* stream = NULL;
 if (SUCCEEDED(hr))
 hr = IWICImagingFactory_CreateStream(factory, &stream);
 if (SUCCEEDED(hr))
 hr = IWICStream_InitializeFromFilename(stream, pathname, GENERIC_WRITE);

 // (5) Create an IWICBitmapEncoder instance, and associate it with the stream.
 IWICBitmapEncoder* encoder = NULL;
 if (SUCCEEDED(hr))
 hr = IWICImagingFactory_CreateEncoder(factory, &GUID_ContainerFormatBmp, NULL,
 &encoder);
 if (SUCCEEDED(hr))
 hr = IWICBitmapEncoder_Initialize(encoder, (IStream*)stream,
 WICBitmapEncoderNoCache);

 // (6) Create an IWICBitmapFrameEncode instance, and initialize it
 // in compliance with the source HBITMAP.
 IWICBitmapFrameEncode* frame = NULL;
 if (SUCCEEDED(hr))
 hr = IWICBitmapEncoder_CreateNewFrame(encoder, &frame, NULL);
 if (SUCCEEDED(hr))
 hr = IWICBitmapFrameEncode_Initialize(frame, NULL);
 if (SUCCEEDED(hr))
 hr = IWICBitmapFrameEncode_SetSize(frame, bm_info.bmWidth, bm_info.bmHeight);
 if (SUCCEEDED(hr)) {
 GUID pixel_format = GUID_WICPixelFormat24bppBGR;
 hr = IWICBitmapFrameEncode_SetPixelFormat(frame, &pixel_format);
 }

 // (7) Write bitmap data to the frame.
 if (SUCCEEDED(hr))
 hr = IWICBitmapFrameEncode_WriteSource(frame, (IWICBitmapSource*)wic_bitmap,
 NULL);

 // (8) Commit frame and data to stream.
 if (SUCCEEDED(hr))
 hr = IWICBitmapFrameEncode_Commit(frame);
 if (SUCCEEDED(hr))
 hr = IWICBitmapEncoder_Commit(encoder);

 // Cleanup
 if (frame)
 IWICBitmapFrameEncode_Release(frame);
 if (encoder)
 IWICBitmapEncoder_Release(encoder);
 if (stream)
 IWICStream_Release(stream);
 if (wic_bitmap)
 IWICBitmap_Release(wic_bitmap);
 if (factory)
 IWICImagingFactory_Release(factory);

 return hr;
}
*/
int TBitmap::SaveHwnd2Bmp(HWND hDlg,char* nom){
	BITMAP bmp; 
	PBITMAPINFO pbmi; 
	WORD cClrBits; 
	HDC hdc[2];
	HBITMAP hbitmap;
	RECT rect;
	GetClientRect(hDlg, &rect);
	hdc[0] = GetWindowDC(hDlg);
	hbitmap = CreateCompatibleBitmap(hdc[0], rect.right, rect.bottom); 
	hdc[1] = CreateCompatibleDC(hdc[0]);
	SelectObject(hdc[1], hbitmap); 
	BitBlt (hdc[1],0,0,rect.right,rect.bottom,hdc[0],0,0,SRCCOPY);
	if (!GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bmp)) errhandler("GetObject", hDlg); 
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
	if (cClrBits == 1) cClrBits = 1; 
	else if (cClrBits <= 4) cClrBits = 4; 
	else if (cClrBits <= 8) cClrBits = 8; 
	else if (cClrBits <= 16) cClrBits = 16; 
	else if (cClrBits <= 24) cClrBits = 24; 
	else					 cClrBits = 32; 
	if (cClrBits < 24) pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits)); 
	else pbmi = (PBITMAPINFO) LocalAlloc(LPTR,sizeof(BITMAPINFOHEADER)); 
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	pbmi->bmiHeader.biWidth = bmp.bmWidth; 
	pbmi->bmiHeader.biHeight = bmp.bmHeight; 
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
	if (cClrBits < 24) pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 
	pbmi->bmiHeader.biCompression = BI_RGB; 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8 * pbmi->bmiHeader.biHeight; 
	pbmi->bmiHeader.biClrImportant = 0; 
	return pbmi->bmiHeader.biBitCount; 
}
BOOL TBitmap::SaveHBITMAPToFile(HBITMAP hBitmap, LPCTSTR lpszFileName){
	HDC hDC;
	int iBits;
	WORD wBitCount;
	DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	BITMAP Bitmap0;
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	HANDLE fh, hDib, hPal, hOldPal2 = NULL;
	hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)		 wBitCount = 1;
	else if (iBits <= 4) wBitCount = 4;
	else if (iBits <= 8) wBitCount = 8;
	else			 wBitCount = 24;
	GetObject(hBitmap, sizeof(Bitmap0), (LPSTR)&Bitmap0);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap0.bmWidth;
	bi.biHeight = -Bitmap0.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 256;
	dwBmBitsSize = ((Bitmap0.bmWidth * wBitCount + 31) & ~31) / 8* Bitmap0.bmHeight;
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal){hDC = GetDC(NULL);hOldPal2 = SelectPalette(hDC, (HPALETTE)hPal, FALSE);RealizePalette(hDC);}
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap0.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+ dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	if (hOldPal2){SelectPalette(hDC, (HPALETTE)hOldPal2, TRUE);RealizePalette(hDC);ReleaseDC(NULL, hDC);}
	fh = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE) return FALSE;
	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}
void TBitmap::CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC){ 
	HANDLE hf; 
	BITMAPFILEHEADER hdr;
	PBITMAPINFOHEADER pbih;
	LPBYTE lpBits;
	DWORD dwTotal,cb,dwTmp; 
	BYTE *hp;
	pbih = (PBITMAPINFOHEADER) pbi; 
	lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
	if (!lpBits) errhandler("GlobalAlloc", hwnd); 
	if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS)) {errhandler("GetDIBits", hwnd); }
	hf = CreateFile(pszFile, GENERIC_READ | GENERIC_WRITE, (DWORD) 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL); 
	if (hf == INVALID_HANDLE_VALUE) errhandler("CreateFile", hwnd); 
	hdr.bfType = 0x4d42; 
	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage); 
	hdr.bfReserved1 = 0; 
	hdr.bfReserved2 = 0; 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof (RGBQUAD); 
	if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp, NULL)) {errhandler("Entete Fichier BMP", hwnd); }
	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) + pbih->biClrUsed * sizeof (RGBQUAD), (LPDWORD) &dwTmp, ( NULL)))errhandler("Info BMP", hwnd); 
	dwTotal = cb = pbih->biSizeImage; 
	hp = lpBits; 
	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) errhandler("WriteFile", hwnd); 
	if (!CloseHandle(hf)) errhandler("CloseHandle", hwnd); 
	GlobalFree((HGLOBAL)lpBits);
}
PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp){ 
	BITMAP bmp; 
	PBITMAPINFO pbmi; 
	WORD cClrBits; 
	assert(GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)); 
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
	if (cClrBits == 1) cClrBits = 1; 
	else if (cClrBits <= 4) cClrBits = 4; 
	else if (cClrBits <= 8) cClrBits = 8; 
	else if (cClrBits <= 16) cClrBits = 16; 
	else if (cClrBits <= 24) cClrBits = 24; 
	else cClrBits = 32; 
	if (cClrBits < 24) pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits)); 
	else pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER)); 
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	pbmi->bmiHeader.biWidth = bmp.bmWidth; 
	pbmi->bmiHeader.biHeight = bmp.bmHeight; 
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
	if (cClrBits < 24) pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 
	pbmi->bmiHeader.biCompression = BI_RGB; 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8 * pbmi->bmiHeader.biHeight; 
	pbmi->bmiHeader.biClrImportant = 0; 
	return pbmi; 
 } 

void CreateBMPFile(LPTSTR pszFile, HBITMAP hBMP) { 
	BITMAPFILEHEADER hdr;
	BYTE *hp;
	DWORD dwTotal,cb, dwTmp; 
	HDC hDC = CreateCompatibleDC(GetWindowDC(GetDesktopWindow()));
	SelectObject(hDC, hBMP);
	PBITMAPINFO pbi = CreateBitmapInfoStruct(hBMP);
	PBITMAPINFOHEADER pbih = (PBITMAPINFOHEADER) pbi; 
	LPBYTE lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
	assert(lpBits) ;
	assert(GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS));
	HANDLE hf = CreateFile(pszFile, GENERIC_READ | GENERIC_WRITE, (DWORD) 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,(HANDLE) NULL); 
	assert(hf != INVALID_HANDLE_VALUE) ;
	hdr.bfType = 0x4d42;
	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage); 
	hdr.bfReserved1 = 0; 
	hdr.bfReserved2 = 0; 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed 	* sizeof (RGBQUAD); 
	assert(WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 	(LPDWORD) &dwTmp, NULL)); 
	assert(WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) + pbih->biClrUsed * sizeof (RGBQUAD), 	(LPDWORD) &dwTmp, ( NULL)));
	dwTotal = cb = pbih->biSizeImage; 
	hp = lpBits; 
	assert(WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)); 
	assert(CloseHandle(hf)); 
	GlobalFree((HGLOBAL)lpBits);
}