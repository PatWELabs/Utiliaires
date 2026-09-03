VERSION 5.00
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Convertisseur Proper Case"
   ClientHeight    =   6375
   ClientLeft      =   45
   ClientTop       =   315
   ClientWidth     =   11130
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6375
   ScaleWidth      =   11130
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command2 
      Caption         =   "&Quitter"
      Height          =   375
      Left            =   9840
      TabIndex        =   4
      Top             =   5640
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Convertir"
      Height          =   375
      Left            =   8640
      TabIndex        =   3
      Top             =   5640
      Width           =   1215
   End
   Begin VB.FileListBox File1 
      Height          =   5355
      Hidden          =   -1  'True
      Left            =   2520
      System          =   -1  'True
      TabIndex        =   2
      Top             =   120
      Width           =   8535
   End
   Begin VB.DirListBox Dir1 
      Height          =   5040
      Left            =   0
      TabIndex        =   1
      Top             =   480
      Width           =   2415
   End
   Begin VB.DriveListBox Drive1 
      Height          =   315
      Left            =   0
      TabIndex        =   0
      Top             =   120
      Width           =   2415
   End
   Begin VB.Label Label1 
      BackColor       =   &H80000018&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000017&
      Height          =   255
      Left            =   0
      TabIndex        =   5
      Top             =   6120
      Width           =   11175
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function MoveFile Lib "kernel32" Alias "MoveFileA" (ByVal lpExistingFileName As String, ByVal lpNewFileName As String) As Long
Private Sub Command1_Click()
    For x = 0 To File1.ListCount - 1
    MoveFile File1.Path & "\" & File1.List(x), File1.Path & "\" & StrConv(File1.List(x), vbProperCase)
    Next

End Sub
Private Sub Command2_Click()
    End
End Sub
Private Sub Dir1_Change()
    File1.Path = Dir1.Path
End Sub
Private Sub Drive1_Change()
    ChDrive Drive1.Drive
    Dir1.Path = Drive1.Drive
End Sub
Private Sub File1_Click()
    MoveFile File1.Path & "\" & File1.List(File1.ListIndex), File1.Path & "\" & StrConv(File1.List(File1.ListIndex), vbProperCase)
End Sub
Private Sub Form_Load()
Me.Label1.Caption = Me.Caption
End Sub
