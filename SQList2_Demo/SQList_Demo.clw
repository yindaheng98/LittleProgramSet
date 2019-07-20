; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSQList_DemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SQList_Demo.h"

ClassCount=3
Class1=CSQList_DemoApp
Class2=CSQList_DemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SQLIST_DEMO_DIALOG

[CLS:CSQList_DemoApp]
Type=0
HeaderFile=SQList_Demo.h
ImplementationFile=SQList_Demo.cpp
Filter=N

[CLS:CSQList_DemoDlg]
Type=0
HeaderFile=SQList_DemoDlg.h
ImplementationFile=SQList_DemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST_ORIG

[CLS:CAboutDlg]
Type=0
HeaderFile=SQList_DemoDlg.h
ImplementationFile=SQList_DemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SQLIST_DEMO_DIALOG]
Type=1
Class=CSQList_DemoDlg
ControlCount=6
Control1=IDC_OPEN,button,1342242816
Control2=IDC_INSERT,button,1342242816
Control3=IDC_LIST_ORIG,SysListView32,1350631424
Control4=IDC_LIST_DEAL,SysListView32,1350631424
Control5=IDC_DEL,button,1342242816
Control6=IDC_CLEAR,button,1342242816

