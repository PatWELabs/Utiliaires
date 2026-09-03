#include <windows.h>
#include <commdlg.h>
#include <stdio.h>

#pragma comment(lib, "comdlg32.lib")
WNDCLASS wc;

// ------------------------------------------------------------
//  Lecture brute du XML dans un WIM/ESD (bloc "xml" LZX compressé)
//  Ici : version simplifiée — recherche du XML en clair dans le fichier
//  (fonctionne pour la majorité des ESD/WIM modernes)
// ------------------------------------------------------------
bool ExtractXmlFromWim(LPCTSTR path, char* outXml, DWORD maxSize)
{
    HANDLE h = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) return false;

    DWORD fileSize = GetFileSize(h, NULL);
    if (fileSize == INVALID_FILE_SIZE || fileSize < 4096) {
        CloseHandle(h);
        return false;
    }

    BYTE* buffer = (BYTE*)HeapAlloc(GetProcessHeap(), 0, fileSize);
    if (!buffer) {
        CloseHandle(h);
        return false;
    }

    DWORD read = 0;
    ReadFile(h, buffer, fileSize, &read, NULL);
    CloseHandle(h);

    // Recherche naïve du XML en clair
    const char* start = strstr((char*)buffer, "<WIM>");
    const char* end = strstr((char*)buffer, "</WIM>");

    if (!start || !end) {
        HeapFree(GetProcessHeap(), 0, buffer);
        return false;
    }

    end += 6; // longueur "</WIM>"

    DWORD len = (DWORD)(end - start);
    if (len >= maxSize) len = maxSize - 1;

    memcpy(outXml, start, len);
    outXml[len] = 0;

    HeapFree(GetProcessHeap(), 0, buffer);
    return true;
}

// ------------------------------------------------------------
//  Extraction des noms d’images depuis le XML
// ------------------------------------------------------------
int ParseImageNames(const char* xml, char names[][128], int maxNames)
{
    int count = 0;
    const char* p = xml;

    while (count < maxNames) {
        const char* tag = strstr(p, "<NAME>");
        if (!tag) break;

        tag += 6;
        const char* end = strstr(tag, "</NAME>");
        if (!end) break;

        int len = (int)(end - tag);
        if (len > 127) len = 127;

        memcpy(names[count], tag, len);
        names[count][len] = 0;

        count++;
        p = end + 7;
    }

    return count;
}

// ------------------------------------------------------------
//  Globals
// ------------------------------------------------------------
HWND g_hWnd;
HWND g_radioButtons[32];
int  g_imageCount = 0;

// ------------------------------------------------------------
//  Création dynamique des boutons radio
// ------------------------------------------------------------
void CreateRadioButtons(HWND hWnd, char names[][128], int count)
{
    for (int i = 0; i < count; i++) {
        g_radioButtons[i] = CreateWindowA(
            "BUTTON",
            names[i],
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            20, 60 + i * 25,
            300, 22,
            hWnd,
            (HMENU)(1000 + i),
            GetModuleHandle(NULL),
            NULL
        );
    }
}

// ------------------------------------------------------------
//  Ouvrir un fichier WIM/ESD
// ------------------------------------------------------------
BOOL OpenWimFile(HWND hWnd)
{
    WCHAR file[MAX_PATH] = { 0 };

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = L"WIM/ESD Files\0*.wim;*.esd\0All Files\0*.*\0";
    ofn.lpstrFile = file;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;

    if (!GetOpenFileName(&ofn))
        return FALSE;

    char xml[200000];
    if (!ExtractXmlFromWim(file, xml, sizeof(xml))) {
        MessageBox(hWnd, L"Impossible d'extraire le XML",wc.lpszClassName , MB_ICONERROR);
        return FALSE;
    }

    char names[32][128];
    g_imageCount = ParseImageNames(xml, names, 32);

    if (g_imageCount == 0) {
        MessageBox(hWnd, L"Aucune image trouvée", wc.lpszClassName, MB_ICONERROR);
        return FALSE;
    }

    CreateRadioButtons(hWnd, names, g_imageCount);
    return TRUE;
}

// ------------------------------------------------------------
//  WinProc
// ------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE:
        CreateWindow(L"BUTTON", L"Ouvrir WIM/ESD",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 20, 150, 25,
            hWnd, (HMENU)1,
            GetModuleHandle(NULL), NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            OpenWimFile(hWnd);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// ------------------------------------------------------------
//  WinMain
// ------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"WIMESDAPP";
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

    RegisterClass(&wc);

    g_hWnd = CreateWindow(wc.lpszClassName , L"Analyse WIM/ESD",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 600,
        NULL, NULL, hInst, NULL);

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
