; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServicesScannerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ServicesScanner.h"

ClassCount=3
Class1=CServicesScannerApp
Class2=CServicesScannerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SERVICESSCANNER_DIALOG

[CLS:CServicesScannerApp]
Type=0
HeaderFile=ServicesScanner.h
ImplementationFile=ServicesScanner.cpp
Filter=N

[CLS:CServicesScannerDlg]
Type=0
HeaderFile=ServicesScannerDlg.h
ImplementationFile=ServicesScannerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST1

[CLS:CAboutDlg]
Type=0
HeaderFile=ServicesScannerDlg.h
ImplementationFile=ServicesScannerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889

[DLG:IDD_SERVICESSCANNER_DIALOG]
Type=1
Class=CServicesScannerDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LIST1,listbox,1353777411

