VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Assistant d'importation MDB ODBC"
   ClientHeight    =   5970
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   10185
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5970
   ScaleWidth      =   10185
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.ListBox List1 
      Height          =   3960
      Left            =   120
      TabIndex        =   12
      Top             =   1920
      Width           =   3375
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Connexion"
      Height          =   255
      Left            =   360
      TabIndex        =   11
      Top             =   1560
      Width           =   975
   End
   Begin VB.TextBox txtVersionConfig 
      Height          =   285
      Left            =   5040
      TabIndex        =   10
      Text            =   "0.00.00"
      Top             =   120
      Width           =   735
   End
   Begin VB.TextBox txtSqlUserID 
      Height          =   285
      Left            =   1320
      TabIndex        =   5
      Text            =   "sa"
      Top             =   480
      Width           =   2175
   End
   Begin VB.TextBox txtServeurSQL 
      Height          =   285
      Left            =   1320
      TabIndex        =   4
      Text            =   ".\SQLEXPRESS"
      Top             =   120
      Width           =   2175
   End
   Begin VB.TextBox txtPasswd 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   1320
      PasswordChar    =   "#"
      TabIndex        =   3
      Text            =   "Password01$"
      Top             =   840
      Width           =   2175
   End
   Begin VB.TextBox txtCatalogue 
      Height          =   285
      Left            =   1320
      TabIndex        =   2
      Text            =   "AutoGRB"
      Top             =   1200
      Width           =   2175
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Patcher"
      Height          =   285
      Left            =   5880
      TabIndex        =   1
      Top             =   120
      Width           =   975
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   480
      Top             =   2160
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Login"
      Height          =   195
      Left            =   120
      TabIndex        =   9
      Top             =   480
      Width           =   390
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Serveur SQL"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   120
      Width           =   975
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Password"
      Height          =   195
      Left            =   120
      TabIndex        =   7
      Top             =   840
      Width           =   690
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Catalogue"
      Height          =   195
      Left            =   120
      TabIndex        =   6
      Top             =   1200
      Width           =   720
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Version config SQL"
      Height          =   195
      Left            =   3600
      TabIndex        =   0
      Top             =   120
      Width           =   1365
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    txtVersionConfig.Text = Left(Year(Now), 1) & "." & Right(Year(Now), 2) & "." & Right("000" + CStr((Month(Now) - 1) * 30 + Day(Now)), 3)
    Dim rstPara As adodb.Recordset
    Set rstPara = New adodb.Recordset
    rstPara.Open "SELECT * FROM GRB_Config", oleSql, adOpenDynamic, adLockOptimistic
    rstPara("DerniereVersion") = txtVersionConfig.Text
    rstPara.Update
    rstPara.Close
    Set rstPara = Nothing
End Sub
Private Sub Command2_Click()
txtVersionConfig.Text = odbc.GetConfigVersion()
End Sub
Private Sub Form_Load()
txtVersionConfig.ToolTipText = txtVersionConfig.Text
EnumTablesSQL
End Sub

