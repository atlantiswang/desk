#include "MainWindow.h"
#include "../MsgDlg/MsgDlg.h"

DUI_BEGIN_MESSAGE_MAP(MainWindow, WindowImplBase)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_END_MESSAGE_MAP()

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitWindow()
{
}

LPCTSTR MainWindow::GetWindowClassName() const
{ 
    return _T("MainWindow");
}

CDuiString MainWindow::GetSkinFile()
{ 
    return _T("XML_MAINWINDOW");
}

void MainWindow::OnClick(TNotifyUI& msg)
{
    if (msg.pSender->GetName() == _T("closebtn"))
    {
        MsgDlg exitDlg;
        exitDlg.Create(m_hWnd, _T("exitdlg"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
        exitDlg.CenterWindow();
        if (exitDlg.ShowModal() == IDOK)
        {
            Close(IDOK);
        }
    }
}
