#pragma once
char* SetNameFormDate();

class TBitmap{
public:
	TBitmap(void);
	~TBitmap(void);
	int SaveHwnd2Bmp(HWND hDlg,char* nom);
	PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
	PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
	BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCTSTR lpszFileName);
	void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
	void CreateBMPFile(LPTSTR pszFile, HBITMAP hBMP);
};