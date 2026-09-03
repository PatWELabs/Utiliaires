Attribute VB_Name = "ODBC"
Public odbc As adodb.Connection
Public oleSql As adodb.Connection
    Dim sDerniereVersion As String
Public Function OuvrirConnection(ByVal CheminDb As String) As Boolean
    If odbc Is Nothing Then
        Set odbc = New adodb.Connection
        sdsn = "Provider=Microsoft.Jet.OLEDB.4.0;User ID = Admin;Data Source=" & CheminBD & ";Persist Security Info=False"
        Call odbc.Open(sdsn)
        OuvrirConnection = True
    Else
        Call MsgBox("La base de donnée est introuvable!" & vbNewLine & "Vérifiez votre connexion réseau!", vbOKOnly, App.ProductName)
        OuvrirConnection = False
    End If
End Function
Public Function EnumTablesSQL()
Dim tblSQL As adodb.Recordset
   If ConnectSQL(Form1.txtServeurSQL, Form1.txtSqlUserID, Form1.txtPasswd, Form1.txtCatalogue) = True Then
        Set tblSQL = New adodb.Recordset
        tblSQL.Open "SELECT NAME FROM SYS.OBJECTS WHERE TYPE='U' ORDER BY CREATE_DATE", oleSql, adOpenDynamic, adLockOptimistic
        Do While Not tblSQL.EOF
            If tblSQL.Fields("NAME").Value <> "" Then
            Form1.List1.AddItem tblSQL.Fields("NAME").Value
            End If
            Loop
            tblSQL.MoveNext
        End If
End Function
Public Function ConnectSQL(ByVal Serveur As String, ByVal uid As String, pwd As String, ByVal Catalogue As String) As Boolean
    If odbc Is Nothing Then
        Set oleSql = New adodb.Connection
       ' sdsn = "Driver={SQL Server};Server=" + Serveur + ";Database=" + Catalogue + ";Uid=" + uid + ";Pwd=" + pwd + ";"
       sdsn = "Provider=MSOLEDBSQL;Server=" + Serveur + ";Database=" + Catalogue + ";Trusted_Connection=yes;" 'trusted connexion
    Call oleSql.Open(sdsn)
        ConnectSQL = True
    Else
        Call MsgBox("La base de donnée est introuvable!" & vbNewLine & "Vérifiez votre connexion réseau!", vbOKOnly, App.ProductName)
        ConnectSQL = False
    End If
End Function
Public Function FermerConnection()
If Not odbc Is Nothing Then
    Call odbc.Close
    Set odbc = Nothing
End If
End Function
Public Function GetConfigVersion() As String
    Dim rstConfig As adodb.Recordset
    If ConnectSQL(Form1.txtServeurSQL, Form1.txtSqlUserID, Form1.txtPasswd, Form1.txtCatalogue) = True Then
        Set rstConfig = New adodb.Recordset
        rstConfig.Open "SELECT DerniereVersion FROM GRB_Config", oleSql, adOpenDynamic, adLockOptimistic
        If rstConfig.EOF = False Then
            If rstConfig.Fields("DerniereVersion").Value <> "" Then
                sDerniereVersion = rstConfig.Fields("DerniereVersion").Value
                Exit Function
            End If
            rstConfig.MoveNext
        End If
    End If
    GetConfigVersion = "iinconnue"
    Call rstConfig.Close
    Set rstConfig = Nothing
End Function

