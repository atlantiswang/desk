#include "MainWindow.h"
#include "MsgDlg/MsgDlg.h"
#include "sqlite3/Sqlite3Adaptor.h"

DUI_BEGIN_MESSAGE_MAP(MainWindow, WindowImplBase)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_END_MESSAGE_MAP()

MainWindow::MainWindow():
    m_sqliteAdaptor(new Sqlite3Adaptor)
{
}

MainWindow::~MainWindow()
{
    m_sqliteAdaptor->UnInit();
}

void MainWindow::InitWindow()
{
    m_sqliteAdaptor->Init("desk.db");
    m_sqliteAdaptor->Sqlite3Open();
    m_sqliteAdaptor->SetLastRunTime("53545");
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
