VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Analyse recursive"
   ClientHeight    =   6570
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   10500
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6570
   ScaleWidth      =   10500
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command3 
      Caption         =   "Quitter"
      Height          =   375
      Left            =   9600
      TabIndex        =   6
      Top             =   0
      Width           =   855
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Generer"
      Height          =   375
      Left            =   8640
      TabIndex        =   5
      Top             =   0
      Width           =   855
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Selectioner le dossier de travail"
      Height          =   375
      Left            =   5880
      TabIndex        =   4
      Top             =   0
      Width           =   2655
   End
   Begin VB.ListBox List1 
      Height          =   2985
      Left            =   120
      TabIndex        =   1
      Top             =   3360
      Width           =   10215
   End
   Begin VB.ListBox dossiers 
      Height          =   2790
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   10215
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Fichiers"
      Height          =   555
      Index           =   1
      Left            =   120
      TabIndex        =   3
      Top             =   3120
      Width           =   1500
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Arborescence"
      Height          =   195
      Index           =   0
      Left            =   240
      TabIndex        =   2
      Top             =   0
      Width           =   990
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim colInPaths As Collection
Dim colOutpaths As Collection
Dim sInputPath As String
Dim sOutputPath As String
Dim sInputPath2 As String
Dim sOutputPath2 As String
Dim lTotalProcess As Long
Dim SearchPath As String, FindStr As String
Dim FileSize As Long
Dim NumFiles As Integer, NumDirs As Integer
Dim AppStringName As String
Dim cTempCollection As Collection

Private Declare Function FindFirstFile Lib "Kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Private Declare Function FindNextFile Lib "Kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Private Declare Function GetFileAttributes Lib "Kernel32" Alias "GetFileAttributesA" (ByVal lpFileName As String) As Long
Private Declare Function FindClose Lib "Kernel32" (ByVal hFindFile As Long) As Long
Private Declare Sub CoTaskMemFree Lib "ole32.dll" (ByVal hMem As Long)
Private Declare Function lstrcat Lib "Kernel32" Alias "lstrcatA" (ByVal lpString1 As String, ByVal lpString2 As String) As Long
Private Declare Function SHBrowseForFolder Lib "shell32" (lpbi As BrowseInfo) As Long
Private Declare Function SHGetPathFromIDList Lib "shell32" (ByVal pidList As Long, ByVal lpBuffer As String) As Long

Const MAX_PATH = 260
Const MAXDWORD = &HFFFF
Const INVALID_HANDLE_VALUE = -1
Const FILE_ATTRIBUTE_ARCHIVE = &H20
Const FILE_ATTRIBUTE_DIRECTORY = &H10
Const FILE_ATTRIBUTE_HIDDEN = &H2
Const FILE_ATTRIBUTE_NORMAL = &H80
Const FILE_ATTRIBUTE_READONLY = &H1
Const FILE_ATTRIBUTE_SYSTEM = &H4
Const FILE_ATTRIBUTE_TEMPORARY = &H100
Const BIF_RETURNONLYFSDIRS = 1

Private Type BrowseInfo
    lngHwnd        As Long
    pIDLRoot       As Long
    pszDisplayName As Long
    lpszTitle      As Long
    ulFlags        As Long
    lpfnCallback   As Long
    lParam         As Long
    iImage         As Long
End Type
Private Type FILETIME
   dwLowDateTime As Long
   dwHighDateTime As Long
End Type
Enum ListPaths
   PathsAndFilenames = 1
   FilenamesOnly = 2
   PathsOnly = 3
End Enum
Dim ListSelected As ListPaths
Private Type WIN32_FIND_DATA
   dwFileAttributes As Long
   ftCreationTime As FILETIME
   ftLastAccessTime As FILETIME
   ftLastWriteTime As FILETIME
   nFileSizeHigh As Long
   nFileSizeLow As Long
   dwReserved0 As Long
   dwReserved1 As Long
   cFileName As String * MAX_PATH
   cAlternate As String * 14
End Type

Dim dWork As String
Private Sub Command1_Click()
    dWork = BrowseForFolder(0, Command1.Value)
    Dim cfList As New Collection
   ' Set cfList =
    DoFileSystemSearch dWork, "*.*", PathsAndFilenames
End Sub

Private Sub Command2_Click()
Open dWork & "\dossiers.inf" For Output As #1
Print #1, "[Folder]"
For x = 0 To dossiers.ListCount - 1
Print #1, x + 1 & "=" & Right$(dossiers.List(x), Len(dossiers.List(x)) - Len(dWork) - 1)
Next
Close 1
Open dWork & "\fichiers.inf" For Output As #1
Print #1, "[Files]"
For x = 0 To List1.ListCount - 1
Print #1, x + 1 & "=" & Right$(List1.List(x), Len(List1.List(x)) - Len(dWork) - 1)
Next
Close 1
Open dWork & "\RCDatas.cpp" For Output As #1
Print #1, "CreateArboretum(char* Path){"
For x = 0 To dossiers.ListCount - 1
Print #1, "CreateDirectory(" + Chr(34) + "%s\" & Right$(dossiers.List(x), Len(dossiers.List(x)) - Len(dWork) - 1) + Chr(34) + ",Path);"
Next
Print #1, "}"
Close 1

End Sub

Private Sub Command3_Click()
End
End Sub

Private Function BrowseForFolder(ByVal lngHwnd As Long, ByVal strPrompt As String) As String

    On Error GoTo ehBrowseForFolder 'Trap for errors

    Dim intNull As Integer
    Dim lngIDList As Long, lngResult As Long
    Dim strPath As String
    Dim udtBI As BrowseInfo

    'Set API properties (housed in a UDT)
    With udtBI
        .lngHwnd = lngHwnd
        .lpszTitle = lstrcat(strPrompt, "")
        .ulFlags = BIF_RETURNONLYFSDIRS
    End With

    'Display the browse folder...
    lngIDList = SHBrowseForFolder(udtBI)

    If lngIDList <> 0 Then
        'Create string of nulls so it will fill in with the path
        strPath = String(MAX_PATH, 0)

        'Retrieves the path selected, places in the null
         'character filled string
        lngResult = SHGetPathFromIDList(lngIDList, strPath)

        'Frees memory
        Call CoTaskMemFree(lngIDList)

        'Find the first instance of a null character,
         'so we can get just the path
        intNull = InStr(strPath, vbNullChar)
        'Greater than 0 means the path exists...
        If intNull > 0 Then
            'Set the value
            strPath = Left(strPath, intNull - 1)
        End If
    End If

    'Return the path name
    BrowseForFolder = strPath
    Exit Function 'Abort

ehBrowseForFolder:

    'Return no value
    BrowseForFolder = Empty

End Function
Function StripNulls(OriginalStr As String) As String
   If (InStr(OriginalStr, Chr(0)) > 0) Then
       OriginalStr = Left(OriginalStr, InStr(OriginalStr, Chr(0)) - 1)
   End If
   StripNulls = OriginalStr
End Function

Function FindFilesAPI(ByVal Path As String, ByVal SearchStr As String, ByVal FileCount As Integer, ByVal DirCount As Integer)


   Dim FileName As String ' Walking filename variable...
   Dim DirName As String ' SubDirectory Name
   Dim dirNames() As String ' Buffer for directory name entries
   Dim nDir As Integer ' Number of directories in this path
   Dim i As Integer ' For-loop counter...
   Dim hSearch As Long ' Search Handle
   Dim WFD As WIN32_FIND_DATA
   Dim Cont As Integer
   If Right(Path, 1) <> "\" Then Path = Path & "\"
   ' Search for subdirectories.
   nDir = 0
   ReDim dirNames(nDir)
   Cont = True
   hSearch = FindFirstFile(Path & "*", WFD)
   If hSearch <> INVALID_HANDLE_VALUE Then
       Do While Cont
       DirName = StripNulls(WFD.cFileName)
       ' Ignore the current and encompassing directories.
        If (DirName <> ".") And (DirName <> "..") Then
           ' Check for directory with bitwise comparison.
           If GetFileAttributes(Path & DirName) And FILE_ATTRIBUTE_DIRECTORY Then
           If InStr(1, Path & DirName, "Processed") = 0 Then
               dirNames(nDir) = DirName
               dossiers.AddItem Path & DirName
               DirCount = DirCount + 1
               nDir = nDir + 1
               ReDim Preserve dirNames(nDir)
           End If
           End If
       End If
       Cont = FindNextFile(hSearch, WFD) 'Get next subdirectory.
       Loop
       Cont = FindClose(hSearch)
   End If
   ' Walk through this directory and sum file sizes.
   hSearch = FindFirstFile(Path & SearchStr, WFD)
   Cont = True
   If hSearch <> INVALID_HANDLE_VALUE Then
       While Cont
           FileName = StripNulls(WFD.cFileName)
           If (FileName <> ".") And (FileName <> "..") Then
               FindFilesAPI = FindFilesAPI + (WFD.nFileSizeHigh * MAXDWORD) + WFD.nFileSizeLow
               FileCount = FileCount + 1
               
               If InStr(1, Path & FileName, "SYSTEM FILES") <> 0 Then
               
                   '// SYSTEM FILES DIRECTORY
               
               Else
               
                   '// OTHER DIRECTORIES
                   
                   cTempCollection.Add Path & FileName
                   List1.AddItem Path & FileName
               
               End If
               
           End If
           Cont = FindNextFile(hSearch, WFD) ' Get next file
       Wend
       Cont = FindClose(hSearch)
   End If
   ' If there are sub-directories...
   If nDir > 0 Then
       ' Recursively walk into them...
       For i = 0 To nDir - 1
           FindFilesAPI = FindFilesAPI + FindFilesAPI(Path & dirNames(i) & "\", SearchStr, FileCount, DirCount)
       Next i
   End If
End Function

Private Function DoFileSystemSearch(ByVal sPath As String, ByVal sFilter As String, ByVal ListAction As ListPaths) As Collection

   ListSelected = ListAction
   
   Set cTempCollection = New Collection
   
   FindFilesAPI sPath, sFilter, NumFiles, NumDirs
   
   Set DoFileSystemSearch = cTempCollection
   MsgBox cTempCollection.Count, vbInformation, "Collection"

End Function


