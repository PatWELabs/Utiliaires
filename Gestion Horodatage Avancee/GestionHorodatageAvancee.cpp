#include <windows.h>
#include <commctrl.h>
#include <shlobj.h>
#include <iostream>
#include <string>
#include <Richedit.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shell32.lib")
#pragma warning(disable:4244)
#pragma warning(disable:4996)
#pragma warning(disable:28251)

// IDs
#define ID_BTN_TIME          1100
#define ID_EDIT_CRT          1101
#define ID_EDIT_MOD          1102
#define ID_EDIT_ACC          1103
#define ID_BTN_APPLY_RECUR   1104
#define ID_DTP_TIME          1105
#define ID_CALENDAR          1106
#define ID_BTN_SYNC       1107

HWND hEditIn;
HWND hEditCrt, hEditMod, hEditAcc;
HWND hBtnApplyRec;
HWND hCalendar, hTimePicker;

static void ConvertirFiletimeVersTexte(const FILETIME& ft, char* out)
{
    SYSTEMTIME st;
    FileTimeToSystemTime(&ft, &st);
    wsprintf(out, "%04d-%02d-%02d %02d:%02d:%02d",st.wYear, st.wMonth, st.wDay,st.wHour, st.wMinute, st.wSecond);
}
static bool ConvertirTexteVersFILETIME(const char* txt, FILETIME& ft)
{
    SYSTEMTIME st;
    ZeroMemory(&st, sizeof(st));
    int y, m, d, hh, mm, ss;
    if (sscanf(txt, "%d-%d-%d %d:%d:%d", &y, &m, &d, &hh, &mm, &ss) != 6)return false;
    st.wYear = y;
    st.wMonth = m;
    st.wDay = d;
    st.wHour = hh;
    st.wMinute = mm;
    st.wSecond = ss;
    return SystemTimeToFileTime(&st, &ft);
}
static bool RetouverLaDateDepuisCalendrier(HWND hCalendar, HWND hTimePicker, FILETIME& ftOut)
{
    SYSTEMTIME stDate{}, stTime{}, stFinal{};
    if (!MonthCal_GetCurSel(hCalendar, &stDate))return false;
    if (!SendMessage(hTimePicker, DTM_GETSYSTEMTIME, 0, (LPARAM)&stTime)) return false;
    stFinal.wYear = stDate.wYear;
    stFinal.wMonth = stDate.wMonth;
    stFinal.wDay = stDate.wDay;
    stFinal.wHour = stTime.wHour;
    stFinal.wMinute = stTime.wMinute;
    stFinal.wSecond = stTime.wSecond;
    stFinal.wMilliseconds = 0;
    return SystemTimeToFileTime(&stFinal, &ftOut);
}
static bool TesterExistanceDossier(const char* path)
{
    DWORD attr = GetFileAttributes(path);
    return (attr != INVALID_FILE_ATTRIBUTES &&  (attr & FILE_ATTRIBUTE_DIRECTORY));
}
static void AppliquerDatesAuFichier(const char* path, const FILETIME& ftCrt, const FILETIME& ftAcc, const FILETIME& ftMod)
{
    HANDLE h = CreateFileA(path, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (h != INVALID_HANDLE_VALUE)
    {
        SetFileTime(h, &ftCrt, &ftAcc, &ftMod);
        CloseHandle(h);
    }
}
static void AppliquerRecursivement(const char* folder,const FILETIME& ftCrt,const FILETIME& ftAcc,const FILETIME& ftMod)
{
    char search[MAX_PATH];
    wsprintf(search, "%s\\*.*", folder);
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(search, &fd);
    if (h == INVALID_HANDLE_VALUE) return;
    do {
        if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))continue;
        char full[MAX_PATH];
        wsprintf(full, "%s\\%s", folder, fd.cFileName);
        AppliquerDatesAuFichier(full, ftCrt, ftAcc, ftMod);
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            AppliquerRecursivement(full, ftCrt, ftAcc, ftMod);
    } while (FindNextFileA(h, &fd));
    FindClose(h);
}
static void ColorationRougeSiformatIncorrect(HWND hEdit)
{
    char txt[64];
    GetWindowText(hEdit, txt, sizeof(txt));
    FILETIME ft;
    bool ok = ConvertirTexteVersFILETIME(txt, ft);
    SendMessage(hEdit, EM_SETSEL, 0, -1);
    if (!ok)
        SendMessage(hEdit, EM_SETBKGNDCOLOR, 0, RGB(255, 200, 200));
    else
        SendMessage(hEdit, EM_SETBKGNDCOLOR, 0, RGB(255, 255, 255));
}
static LRESULT CALLBACK FenetrePrincipale(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        InitCommonControls();
        hEditIn = CreateWindow("EDIT", "",WS_CHILD | WS_VISIBLE | WS_BORDER,10, 10, 300, 22, hwnd, NULL, NULL, NULL);
        hEditCrt = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,10, 50, 200, 22, hwnd, (HMENU)ID_EDIT_CRT, NULL, NULL);
        hEditMod = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,10, 80, 200, 22, hwnd, (HMENU)ID_EDIT_MOD, NULL, NULL);
        hEditAcc = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,10, 110, 200, 22, hwnd, (HMENU)ID_EDIT_ACC, NULL, NULL);
        hCalendar = CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME,MONTHCAL_CLASS, "",WS_CHILD | WS_VISIBLE,380, 2, 240, 200, hwnd, (HMENU)ID_CALENDAR, NULL, NULL);
        hTimePicker = CreateWindow(DATETIMEPICK_CLASS, "",WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,10, 140, 200, 22, hwnd, (HMENU)ID_DTP_TIME, NULL, NULL);
        hBtnApplyRec = CreateWindow("BUTTON", "Appliquer recursivement",WS_CHILD | WS_VISIBLE,10, 180, 200, 25, hwnd, (HMENU)ID_BTN_APPLY_RECUR, NULL, NULL);
        CreateWindow("BUTTON", "Synchroniser dates",WS_CHILD | WS_VISIBLE,220, 180, 150, 25, hwnd, (HMENU)ID_BTN_SYNC, NULL, NULL);
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_BTN_SYNC:
        {
            FILETIME ft;
            if (!RetouverLaDateDepuisCalendrier(hCalendar, hTimePicker, ft))
            {
                MessageBox(hwnd, "Date invalide.", "Erreur", MB_OK);
                break;
            }
            char txt[64];
            ConvertirFiletimeVersTexte(ft, txt);
            SetWindowText(hEditCrt, txt);
            SetWindowText(hEditMod, txt);
            SetWindowText(hEditAcc, txt);
            ColorationRougeSiformatIncorrect(hEditCrt);
            ColorationRougeSiformatIncorrect(hEditMod);
            ColorationRougeSiformatIncorrect(hEditAcc);
            MessageBox(hwnd, "Dates synchronisees.", "OK", MB_OK);
        }
        break;
        case ID_BTN_APPLY_RECUR:
        {
            char folder[512];
            GetWindowText(hEditIn, folder, sizeof(folder));
            if (!TesterExistanceDossier(folder))
            {
                MessageBox(hwnd, "Dossier invalide.", "Erreur", MB_OK);
                break;
            }
            FILETIME ft;
            if (!RetouverLaDateDepuisCalendrier(hCalendar, hTimePicker, ft))
            {
                MessageBox(hwnd, "Date invalide.", "Erreur", MB_OK);
                break;
            }
            AppliquerDatesAuFichier(folder, ft, ft, ft);
            AppliquerRecursivement(folder, ft, ft, ft);
            MessageBox(hwnd, "Horodatage applique à toute l’arborescence.", "OK", MB_OK);
        }
        break;
        case ID_EDIT_CRT:
        case ID_EDIT_MOD:
        case ID_EDIT_ACC:
            if (HIWORD(wParam) == EN_CHANGE)
                ColorationRougeSiformatIncorrect((HWND)lParam);
            break;

        }
        break;
    case WM_NOTIFY:
    {
        NMHDR* hdr = (NMHDR*)lParam;

        if (hdr->idFrom == ID_CALENDAR && ((hdr->code == MCN_SELCHANGE) || (hdr->code == MCN_SELECT)))
        {
            FILETIME ft;
            if (RetouverLaDateDepuisCalendrier(hCalendar, hTimePicker, ft))
            {
                char txt[64];
                ConvertirFiletimeVersTexte(ft, txt);
                SetWindowText(hEditCrt, txt);
                SetWindowText(hEditMod, txt);
                SetWindowText(hEditAcc, txt);
                ColorationRougeSiformatIncorrect(hEditCrt);
                ColorationRougeSiformatIncorrect(hEditMod);
                ColorationRougeSiformatIncorrect(hEditAcc);
            }
        }
        if (hdr->idFrom == ID_DTP_TIME && hdr->code == DTN_DATETIMECHANGE)
        {
            FILETIME ft;
            if (RetouverLaDateDepuisCalendrier(hCalendar, hTimePicker, ft))
            {
                char txt[64];
                ConvertirFiletimeVersTexte(ft, txt);
                SetWindowText(hEditCrt, txt);
                SetWindowText(hEditMod, txt);
                SetWindowText(hEditAcc, txt);
                ColorationRougeSiformatIncorrect(hEditCrt);
                ColorationRougeSiformatIncorrect(hEditMod);
                ColorationRougeSiformatIncorrect(hEditAcc);
            }
        }
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
    InitCommonControls();

    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = FenetrePrincipale;
    wc.hInstance = hInst;
    wc.lpszClassName = "HorodatageApp";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIconA(wc.hInstance, (LPCSTR)101);
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("HorodatageApp","Gestion Horodatage Avancee",WS_OVERLAPPED |WS_CAPTION |WS_SYSMENU |WS_THICKFRAME,CW_USEDEFAULT, CW_USEDEFAULT,650, 260,NULL, NULL, hInst, NULL);
    ShowWindow(hwnd, nShow);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}