#include <windows.h>
#include <commdlg.h>
#include <commctrl.h>
#include <stdio.h>
#include "dismapi.h"

#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "comctl32.lib")


#ifdef _WIN64
#pragma comment(lib, "dismapi_x64.lib")
#define Titre L"DISM Image Explorer 64bits avec API DISM et StyleXP"
#define _suffix "_x64"
#else
#pragma comment(lib, "dismapi_x86.lib")
#define Titre L"DISM Image Explorer 32bits avec API DISM et StyleXP"
#define _suffix "_x86"
#endif
#pragma warning(disable: 4996) // for sprintf

#define ID_TB_OPEN          1001
#define ID_TB_EXPORT_TXT    1002
#define ID_TB_EXPORT_JSON   1003
#define ID_TB_APPLY         1004

HWND g_hWnd        = NULL;
HWND g_hList       = NULL;
HWND g_hToolbar    = NULL;
HIMAGELIST g_hImg  = NULL;
WNDCLASS wc;

WCHAR g_CurrentWim[MAX_PATH] = L"";

typedef enum _DismProcessorArchitecture
{
    DismProcessorArchitectureNone = 0,
    DismProcessorArchitectureX86 = 1,
    DismProcessorArchitectureX64 = 2,
    DismProcessorArchitectureArm = 3,
    DismProcessorArchitectureArm64 = 4,
} DismProcessorArchitecture;

DismImageInfo* g_pInfos = NULL;
UINT g_ImageCount       = 0;
static const char* ArchToString(UINT arch)
{
    switch (arch) {
    case DismProcessorArchitectureX86:   return "x86";
    case DismProcessorArchitectureX64:   return "x64";
    case DismProcessorArchitectureArm:   return "ARM";
    case DismProcessorArchitectureArm64: return "ARM64";
    default:                             return "Unknown";
    }
}
int MsgBoxA(HWND hDlg, char* lpszText, char* lpszCaption, DWORD dwStyle, int lpszIcon) {
    MSGBOXPARAMSA lpmbp;
    lpmbp.hInstance = wc.hInstance;
    lpmbp.cbSize = sizeof(MSGBOXPARAMSA);
    lpmbp.hwndOwner = hDlg;
    lpmbp.dwLanguageId = MAKELANGID(0x0800, 0x0800); //par defaut celui du systeme
    lpmbp.lpszText = lpszText;
    lpmbp.lpszCaption = lpszCaption;
    lpmbp.dwStyle = dwStyle | 0x00000080L;
    lpmbp.lpszIcon = (LPCSTR)lpszIcon;
    lpmbp.lpfnMsgBoxCallback = 0;
    return  MessageBoxIndirectA(&lpmbp);
}
int MsgBoxW(HWND hDlg, WCHAR* lpszText, WCHAR* lpszCaption, DWORD dwStyle, int lpszIcon) {
    MSGBOXPARAMS lpmbp;
    lpmbp.hInstance = wc.hInstance;
    lpmbp.cbSize = sizeof(MSGBOXPARAMSA);
    lpmbp.hwndOwner = hDlg;
    lpmbp.dwLanguageId = MAKELANGID(0x0800, 0x0800); //par defaut celui du systeme
    lpmbp.lpszText = lpszText;
    lpmbp.lpszCaption = lpszCaption;
    lpmbp.dwStyle = dwStyle | 0x00000080L;
    lpmbp.lpszIcon = (LPCWSTR)lpszIcon;
    lpmbp.lpfnMsgBoxCallback = 0;
    return  MessageBoxIndirectW(&lpmbp);
}
#if defined(UNICODE) || defined(_UNICODE)
#define MsgBox  MsgBoxW
#else
#define MsgBox  MsgBoxA
#endif
static void LibererArchive()
{
    if (g_pInfos) {
        DismDelete(g_pInfos);
        g_pInfos = NULL;
        g_ImageCount = 0;
    }
}
static void BuildLanguagesString(DismString* langs, UINT count, char* out, int max)
{
    out[0] = 0;
    if (!langs || count == 0) return;
    char tmp[256];
    for (UINT i = 0; i < count; ++i) {
        char buf[128];
        WideCharToMultiByte(CP_ACP, 0, langs[i].Value, -1, buf, sizeof(buf), NULL, NULL);
        if (i == 0)
            wsprintfA(tmp, "%s", buf);
        else
            wsprintfA(tmp, "%s,%s", out, buf);
        lstrcpynA(out, tmp, max);
    }
}
static void InsererElementListe(int row,const char* indexStr,const char* name,const char* desc,const char* arch,const char* editionId,const char* displayName,const char* languages)
{
    LVITEMA item;
    ZeroMemory(&item, sizeof(item));
    item.mask = LVIF_TEXT | LVIF_IMAGE;
    item.iItem = row;
    item.iSubItem = 0;
    item.pszText = (LPSTR)indexStr;
    if (!strcmp(arch, "x86"))      item.iImage = 0;
    else if (!strcmp(arch, "x64")) item.iImage = 1;
    else                           item.iImage = 2;
    ListView_InsertItem(g_hList, &item);
    ListView_SetItemText(g_hList, row, 1, (LPWSTR)name);
    ListView_SetItemText(g_hList, row, 2, (LPWSTR)desc);
    ListView_SetItemText(g_hList, row, 3, (LPWSTR)arch);
    ListView_SetItemText(g_hList, row, 4, (LPWSTR)editionId);
    ListView_SetItemText(g_hList, row, 5, (LPWSTR)displayName);
    ListView_SetItemText(g_hList, row, 6, (LPWSTR)languages);
}
static void CreerListeImages()
{
    g_hImg = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, 3, 3);
    HICON hX86   = LoadIcon(NULL, IDI_APPLICATION);
    HICON hX64   = LoadIcon(NULL, IDI_WINLOGO);
    HICON hOther = LoadIcon(NULL, IDI_QUESTION);
    ImageList_AddIcon(g_hImg, hX86);
    ImageList_AddIcon(g_hImg, hX64);
    ImageList_AddIcon(g_hImg, hOther);
    ListView_SetImageList(g_hList, g_hImg, LVSIL_SMALL);
}
static void CreerBoutonCommande(HWND hWnd)
{
    RECT rc;
	GetClientRect(hWnd, &rc);
    CreateWindowEx(WS_EX_DLGMODALFRAME, WC_BUTTON, L"Ouvrir", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 1, 0, 90, 30, hWnd, (HMENU)ID_TB_OPEN, wc.hInstance, NULL);
    CreateWindowEx( WS_EX_DLGMODALFRAME, WC_BUTTON, L"Exporter TXT", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 91, 0, 108, 30, hWnd, (HMENU)ID_TB_EXPORT_TXT, wc.hInstance, NULL);
    CreateWindowEx( WS_EX_DLGMODALFRAME, WC_BUTTON, L"Exporter JSON", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 200, 0, 110, 30, hWnd, (HMENU)ID_TB_EXPORT_JSON, wc.hInstance, NULL);
    CreateWindowEx(WS_EX_DLGMODALFRAME, WC_BUTTON, L"Appliquer", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 310, 0, 90, 30, hWnd, (HMENU)ID_TB_APPLY, wc.hInstance, NULL);
    CreateWindowEx(WS_EX_DLGMODALFRAME, WC_BUTTON, L"Quitter", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, rc.right-92, 0, 90, 30, hWnd, (HMENU)IDCANCEL, wc.hInstance, NULL);
}
static BOOL ChargerArchiveAvecDism(LPCWSTR wimPath)
{
    HRESULT hr;
    DismSession session = 0;
    LibererArchive();
    hr = DismInitialize(DismLogErrorsWarningsInfo, NULL, NULL);
    if (FAILED(hr)) {MsgBox(g_hWnd, (WCHAR*)L"DismInitialize a échoué", (WCHAR*) Titre, MB_OK,102);return FALSE;}
    hr = DismOpenSession(wimPath, NULL, NULL, &session);
    if (FAILED(hr)) {
        MsgBox(g_hWnd, (WCHAR*)L"DismOpenSession a échoué", (WCHAR*) Titre, MB_OK,102);
        DismShutdown();
        return FALSE;
    }
    hr = DismGetImageInfo(wimPath, &g_pInfos, &g_ImageCount);
    if (FAILED(hr)) {
        MsgBox(g_hWnd, (WCHAR*)L"DismGetImageInfo a échoué", (WCHAR*) Titre, MB_OK,102);
        DismCloseSession(session);
        DismShutdown();
        return FALSE;
    }
    DismCloseSession(session);
    DismShutdown();
    return TRUE;
}
static BOOL RemplirListeAvecInfosDism()
{
    if (!g_pInfos || g_ImageCount == 0)return FALSE;
    ListView_DeleteAllItems(g_hList);
    for (UINT i = 0; i < g_ImageCount; ++i) {
        char indexStr[16];
        wsprintfA(indexStr, "%u", g_pInfos[i].ImageIndex);
        char name[256] = "";
        char desc[512] = "";
        char editionId[128] = "";
        char displayName[256] = "";
        char arch[32] = "";
        char languages[256] = "";
        if (g_pInfos[i].ImageName)          WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].ImageName, -1, name, sizeof(name), NULL, NULL);
        if (g_pInfos[i].ImageDescription)   WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].ImageDescription, -1, desc, sizeof(desc), NULL, NULL);
        if (g_pInfos[i].EditionId)          WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].EditionId, -1, editionId, sizeof(editionId), NULL, NULL);
        if (g_pInfos[i].ProductName)        WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].ProductName, -1, displayName, sizeof(displayName), NULL, NULL);
        const char* a = ArchToString(g_pInfos[i].Architecture);
        lstrcpynA(arch, a, sizeof(arch));
        BuildLanguagesString(g_pInfos[i].Language,g_pInfos[i].LanguageCount,languages,sizeof(languages));
        InsererElementListe(i, indexStr, name, desc, arch, editionId, displayName, languages);
    }
    return TRUE;
}
static BOOL ChargerArchive(HWND hWnd)
{
    char fileA[MAX_PATH] = { 0 };
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = "WIM/ESD Files\0*.wim;*.esd\0All Files\0*.*\0";
    ofn.lpstrFile = fileA;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;
    if (!GetOpenFileNameA(&ofn))return FALSE;
    MultiByteToWideChar(CP_ACP, 0, fileA, -1, g_CurrentWim, MAX_PATH);
    if (!ChargerArchiveAvecDism(g_CurrentWim))return FALSE;
    return RemplirListeAvecInfosDism();
}
static BOOL EnregistrerFichier(HWND hWnd, const char* filter, char* outPath, DWORD max)
{
    ZeroMemory(outPath, max);
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = outPath;
    ofn.nMaxFile = max;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    if (!GetSaveFileNameA(&ofn)) return FALSE;
    return TRUE;
}
static BOOL ExporterTexte(HWND hWnd)
{
    if (!g_pInfos || g_ImageCount == 0) { MsgBox(hWnd, (WCHAR*)L"Aucune image à exporter", (WCHAR*) Titre,MB_OK, 102);return FALSE;    }
    char path[MAX_PATH];
    if (!EnregistrerFichier(hWnd, "Text Files\0*.txt\0All Files\0*.*\0", path, sizeof(path)))return FALSE;
    FILE* f = fopen(path, "w");
    if (!f) {MsgBox(hWnd, (WCHAR*)L"Impossible d'ouvrir le fichier", (WCHAR*) Titre, MB_OK,102);return FALSE;}
    for (UINT i = 0; i < g_ImageCount; ++i) {
        char name[256] = "";
        char desc[512] = "";
        char editionId[128] = "";
        char displayName[256] = "";
        char arch[32] = "";
        char languages[256] = "";
        if (g_pInfos[i].ImageName) WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].ImageName, -1, name, sizeof(name), NULL, NULL);
        if (g_pInfos[i].ImageDescription) WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].ImageDescription, -1, desc, sizeof(desc), NULL, NULL);
        if (g_pInfos[i].EditionId)WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].EditionId, -1, editionId, sizeof(editionId), NULL, NULL);
        if (g_pInfos[i].ProductName) WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].ProductName, -1, displayName, sizeof(displayName), NULL, NULL);
        const char* a = ArchToString(g_pInfos[i].Architecture);
        lstrcpynA(arch, a, sizeof(arch));
        BuildLanguagesString(g_pInfos[i].Language,g_pInfos[i].LanguageCount,languages,sizeof(languages));
        fprintf(f,
            "Index: %u\n"
            "Nom: %s\n"
            "Description: %s\n"
            "Architecture: %s\n"
            "EditionID: %s\n"
            "Nom du produit: %s\n"
            "Langues: %s\n\n",
            g_pInfos[i].ImageIndex,name, desc, arch, editionId, displayName, languages);
    }
    fclose(f);
    return TRUE;
}
static BOOL ExporterJson(HWND hWnd)
{
    if (!g_pInfos || g_ImageCount == 0) {MsgBox(hWnd, (WCHAR*)L"Aucune image à exporter", (WCHAR*) Titre, MB_OK,102);return FALSE;}
    char path[MAX_PATH];
    if (!EnregistrerFichier(hWnd, "JSON Files\0*.json\0All Files\0*.*\0", path, sizeof(path)))return FALSE;
    FILE* f = fopen(path, "w");
    if (!f) {MsgBox(hWnd, (WCHAR*)L"Impossible d'ouvrir le fichier", (WCHAR*) Titre, MB_OK,102);return FALSE;}
    fprintf(f, "[\n");
    for (UINT i = 0; i < g_ImageCount; ++i) {
        char name[256] = "";
        char desc[512] = "";
        char editionId[128] = "";
        char displayName[256] = "";
        char arch[32] = "";
        char languages[256] = "";
        if (g_pInfos[i].ImageName) WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].ImageName, -1, name, sizeof(name), NULL, NULL);
        if (g_pInfos[i].ImageDescription) WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].ImageDescription, -1, desc, sizeof(desc), NULL, NULL);
        if (g_pInfos[i].EditionId)WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].EditionId, -1, editionId, sizeof(editionId), NULL, NULL);
        if (g_pInfos[i].ProductName)WideCharToMultiByte(CP_ACP, 0, g_pInfos[i].ProductName, -1, displayName, sizeof(displayName), NULL, NULL);
        const char* a = ArchToString(g_pInfos[i].Architecture);
        lstrcpynA(arch, a, sizeof(arch));
        BuildLanguagesString(g_pInfos[i].Language,g_pInfos[i].LanguageCount,languages,sizeof(languages));
        fprintf(f,
            "  {\n"
            "    \"Index\": %u,\n"
            "    \"Nom\": \"%s\",\n"
            "    \"Description\": \"%s\",\n"
            "    \"Architecture\": \"%s\",\n"
            "    \"EditionID\": \"%s\",\n"
            "    \"Nom du produit\": \"%s\",\n"
            "    \"Langue\": \"%s\"\n"
            "  }%s\n",g_pInfos[i].ImageIndex,name, desc, arch, editionId, displayName, languages,(i + 1 < g_ImageCount) ? "," : "");
    }
    fprintf(f, "]\n");
    fclose(f);
    return TRUE;
}
static void DeployerImage(HWND hWnd)
{
    int sel = ListView_GetNextItem(g_hList, -1, LVNI_SELECTED);
    if (sel < 0) {MsgBox(hWnd, (WCHAR*)L"Aucune image sélectionnée", (WCHAR*) Titre, MB_OK,102);return;}
    WCHAR indexStr[16];
    ListView_GetItemText(g_hList, sel, 0, indexStr, sizeof(indexStr));
    WCHAR msg[256];
    wsprintf(msg,L"Image sélectionnée : index %s\nPrête pour ton provisioning.",indexStr);
    MsgBox(hWnd, msg, (WCHAR*) Titre, MB_OK | MB_OK,102);
}
static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        InitCommonControls();
        g_hList = CreateWindow(WC_LISTVIEW, L"",WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS,0, 70, 800, 500,hWnd, (HMENU)2,GetModuleHandle(NULL), NULL);
        ListView_SetExtendedListViewStyle(g_hList,LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
        LVCOLUMN col;
        ZeroMemory(&col, sizeof(col));
        col.mask = LVCF_TEXT | LVCF_WIDTH;
        col.pszText =(LPWSTR)L"Index";        col.cx = 50;  ListView_InsertColumn(g_hList, 0, &col);
        col.pszText = (LPWSTR)L"Name";         col.cx = 150; ListView_InsertColumn(g_hList, 1, &col);
        col.pszText = (LPWSTR)L"Description";  col.cx = 200; ListView_InsertColumn(g_hList, 2, &col);
        col.pszText = (LPWSTR)L"Arch";         col.cx = 70;  ListView_InsertColumn(g_hList, 3, &col);
        col.pszText = (LPWSTR)L"EditionID";    col.cx = 120; ListView_InsertColumn(g_hList, 4, &col);
        col.pszText = (LPWSTR)L"Produit";  col.cx = 150; ListView_InsertColumn(g_hList, 5, &col);
        col.pszText = (LPWSTR)L"Langues";    col.cx = 150; ListView_InsertColumn(g_hList, 6, &col);
        CreerListeImages();
        CreerBoutonCommande(hWnd);
    }
    break;
    case WM_SIZE:
    {
		RECT rc;
		GetClientRect(hWnd, &rc);
        MoveWindow(GetDlgItem(hWnd,IDCANCEL),rc.right-92, 0, 90,30, TRUE);
        MoveWindow(g_hList, 0, 30, rc.right, rc.bottom - 50, TRUE);
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_TB_OPEN:        ChargerArchive(hWnd);break;
        case ID_TB_EXPORT_TXT:  ExporterTexte(hWnd);break;
        case ID_TB_EXPORT_JSON: ExporterJson(hWnd);break;
        case ID_TB_APPLY:       DeployerImage(hWnd);break;
        case IDCANCEL:          LibererArchive();PostQuitMessage(0);break;
        }
        break;
    case WM_DESTROY:
        LibererArchive();
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"LecteurWim";
    wc.hIcon = LoadIcon(wc.hInstance, (LPWSTR)102);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    RegisterClass(&wc);
	g_hWnd = CreateWindow(wc.lpszClassName,Titre, WS_OVERLAPPED |WS_CAPTION |WS_SYSMENU,CW_USEDEFAULT, CW_USEDEFAULT,820, 600,NULL, NULL, hInst, NULL);
    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
