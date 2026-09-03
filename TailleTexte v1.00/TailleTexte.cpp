#include <windows.h>
#include <commctrl.h>
#include <shlobj.h>
#include <iostream>
#include <string>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shell32.lib")
#pragma warning(disable:4244)

#define ID_EDIT_INPUT    1001
#define ID_EDIT_OUTPUT   1002
#define ID_SLIDER_LEFT   1003
#define ID_SLIDER_RIGHT  1004
#define ID_BTN_RESET     1005
#define ID_BTN_COPY      1006
#define ID_BTN_PROFILE1  1007
#define ID_BTN_PROFILE2  1008
#define ID_BTN_PROFILE3  1009
#define ID_BTN_BROWSE    1010
#define ID_BTN_RENAME    1011

HWND hEditIn, hEditOut, hSliderLeft, hSliderRight;
HWND hBtnRename;
HWND hStatus;

// Compteurs pour la barre d’état
int g_FilesRenamed = 0;
int g_Errors = 0;
int g_Progress = 0; // 0–100

void UpdateStatusBar()
{
    char part0[64];
    char part1[64];
    char part2[64];

    wsprintf(part0, "Renommés : %d", g_FilesRenamed);
    wsprintf(part1, "Erreurs : %d", g_Errors);
    wsprintf(part2, "Progression : %d%%", g_Progress);

    SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)part0);
    SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)part1);
    SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)part2);
}

bool IsExistingFolder(const char* path)
{
    DWORD attr = GetFileAttributes(path);
    return (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY));
}

std::string BrowseForFolder(HWND owner, const char* title)
{
    BROWSEINFOA bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.hwndOwner = owner;
    bi.lpszTitle = title;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (!pidl) return "";

    char path[MAX_PATH];
    SHGetPathFromIDListA(pidl, path);
    CoTaskMemFree(pidl);
    return path;
}

void UpdateRenameButton()
{
    char buffer[512];
    GetWindowText(hEditIn, buffer, sizeof(buffer));

    if (IsExistingFolder(buffer))
        EnableWindow(hBtnRename, TRUE);
    else
        EnableWindow(hBtnRename, FALSE);
}

void UpdateOutput()
{
    char buffer[512];
    GetWindowText(hEditIn, buffer, sizeof(buffer));

    int len = lstrlen(buffer);
    if (len == 0) {
        SetWindowText(hEditOut, "");
        UpdateRenameButton();
        return;
    }

    int dotPos = -1;
    for (int i = len - 1; i >= 0; --i)
        if (buffer[i] == '.') { dotPos = i; break; }

    int leftCut = SendMessage(hSliderLeft, TBM_GETPOS, 0, 0);
    int rightCut = SendMessage(hSliderRight, TBM_GETPOS, 0, 0);

    int maxRightCut = (dotPos == -1) ? len : (len - dotPos - 1);
    if (rightCut > maxRightCut) rightCut = maxRightCut;

    int start = leftCut;
    int end = len - rightCut;
    if (start < 0) start = 0;
    if (end < start) end = start;

    char out[512];
    int j = 0;
    for (int i = start; i < end; ++i)
        out[j++] = buffer[i];
    out[j] = 0;

    SetWindowText(hEditOut, out);
    UpdateRenameButton();
}

void ApplyProfile(int left, int right)
{
    SendMessage(hSliderLeft, TBM_SETPOS, TRUE, left);
    SendMessage(hSliderRight, TBM_SETPOS, TRUE, right);
    UpdateOutput();
}

void CopyToClipboard(HWND hwnd, const char* text)
{
    if (!OpenClipboard(hwnd)) return;
    EmptyClipboard();

    size_t len = strlen(text) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), text, len);
    GlobalUnlock(hMem);

    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

// Stub de renommage récursif : ici tu pluggeras ton vrai moteur
void RecursiveRename(const char* folder)
{
    g_FilesRenamed = 0;
    g_Errors = 0;
    g_Progress = 0;
    UpdateStatusBar();

    // Exemple : simulation de progression
    for (int i = 0; i <= 10; ++i)
    {
        // Simuler 10 fichiers renommés, 2 erreurs
        g_FilesRenamed += 1;
        if (i % 4 == 0) g_Errors += 1;

        g_Progress = (i * 100) / 10;
        UpdateStatusBar();
        Sleep(50);
    }

    MessageBox(NULL, "Renommage récursif terminé (stub).", folder, MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        InitCommonControls();

        hEditIn = CreateWindow("EDIT", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            10, 10, 300, 25, hwnd, (HMENU)ID_EDIT_INPUT, NULL, NULL);

        hEditOut = CreateWindow("EDIT", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY,
            10, 45, 300, 25, hwnd, (HMENU)ID_EDIT_OUTPUT, NULL, NULL);

        hSliderLeft = CreateWindow(TRACKBAR_CLASS, "",
            WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
            10, 80, 300, 30, hwnd, (HMENU)ID_SLIDER_LEFT, NULL, NULL);

        hSliderRight = CreateWindow(TRACKBAR_CLASS, "",
            WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
            10, 120, 300, 30, hwnd, (HMENU)ID_SLIDER_RIGHT, NULL, NULL);

        SendMessage(hSliderLeft, TBM_SETRANGE, TRUE, MAKELONG(0, 50));
        SendMessage(hSliderRight, TBM_SETRANGE, TRUE, MAKELONG(0, 50));

        CreateWindow("BUTTON", "Reset",
            WS_CHILD | WS_VISIBLE,
            320, 10, 80, 25, hwnd, (HMENU)ID_BTN_RESET, NULL, NULL);

        CreateWindow("BUTTON", "Copier",
            WS_CHILD | WS_VISIBLE,
            320, 45, 80, 25, hwnd, (HMENU)ID_BTN_COPY, NULL, NULL);

        CreateWindow("BUTTON", "Profil 1",
            WS_CHILD | WS_VISIBLE,
            10, 160, 80, 25, hwnd, (HMENU)ID_BTN_PROFILE1, NULL, NULL);

        CreateWindow("BUTTON", "Profil 2",
            WS_CHILD | WS_VISIBLE,
            100, 160, 80, 25, hwnd, (HMENU)ID_BTN_PROFILE2, NULL, NULL);

        CreateWindow("BUTTON", "Profil 3",
            WS_CHILD | WS_VISIBLE,
            190, 160, 80, 25, hwnd, (HMENU)ID_BTN_PROFILE3, NULL, NULL);

        CreateWindow("BUTTON", "Parcourir…",
            WS_CHILD | WS_VISIBLE,
            320, 80, 80, 25, hwnd, (HMENU)ID_BTN_BROWSE, NULL, NULL);

        hBtnRename = CreateWindow("BUTTON", "Renommer",
            WS_CHILD | WS_VISIBLE | WS_DISABLED,
            320, 120, 80, 25, hwnd, (HMENU)ID_BTN_RENAME, NULL, NULL);

        // Barre d’état
        hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE, "", hwnd, 2000);
        int parts[3];
        RECT rc;
        GetClientRect(hwnd, &rc);
        int width = rc.right - rc.left;
        parts[0] = width / 3;
        parts[1] = 2 * width / 3;
        parts[2] = -1;
        SendMessage(hStatus, SB_SETPARTS, 3, (LPARAM)parts);

        g_FilesRenamed = 0;
        g_Errors = 0;
        g_Progress = 0;
        UpdateStatusBar();

        UpdateOutput();
    }
    break;

    case WM_SIZE:
        if (hStatus)
            SendMessage(hStatus, WM_SIZE, wParam, lParam);
        break;

    case WM_HSCROLL:
        UpdateOutput();
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_EDIT_INPUT:
            if (HIWORD(wParam) == EN_CHANGE)
                UpdateOutput();
            break;

        case ID_BTN_RESET:
            SetWindowText(hEditIn, "");
            SetWindowText(hEditOut, "");
            SendMessage(hSliderLeft, TBM_SETPOS, TRUE, 0);
            SendMessage(hSliderRight, TBM_SETPOS, TRUE, 0);
            g_FilesRenamed = 0;
            g_Errors = 0;
            g_Progress = 0;
            UpdateStatusBar();
            UpdateOutput();
            break;

        case ID_BTN_COPY:
        {
            char out[512];
            GetWindowText(hEditOut, out, sizeof(out));
            CopyToClipboard(hwnd, out);
        }
        break;

        case ID_BTN_PROFILE1: ApplyProfile(2, 2); break;
        case ID_BTN_PROFILE2: ApplyProfile(5, 3); break;
        case ID_BTN_PROFILE3: ApplyProfile(10, 0); break;

        case ID_BTN_BROWSE:
        {
            std::string folder = BrowseForFolder(hwnd, "Choisir un dossier");
            if (!folder.empty())
                SetWindowText(hEditIn, folder.c_str());
            UpdateOutput();
        }
        break;

        case ID_BTN_RENAME:
        {
            char folder[512];
            GetWindowText(hEditIn, folder, sizeof(folder));
            if (IsExistingFolder(folder))
                RecursiveRename(folder);
        }
        break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nShow)
{
    CoInitialize(NULL);

    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "CutApp";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("CutApp", "Découpe + Renommage récursif + Barre d’état",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        440, 280, NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, nShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CoUninitialize();
    return msg.wParam;
}
