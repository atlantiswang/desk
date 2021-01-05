#include "SetDlg.h"

DUI_BEGIN_MESSAGE_MAP(SetDlg, WindowImplBase)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_END_MESSAGE_MAP()

SetDlg::SetDlg()
{
}

SetDlg::~SetDlg()
{
}

void SetDlg::InitWindow()
{
}

CDuiString SetDlg::GetSkinFile()
{
    return _T("XML_SET");
}

LPCTSTR SetDlg::GetWindowClassName() const
{
    return _T("SETSSS");
}

void SetDlg::OnClick(TNotifyUI& msg)
{
    if (msg.pSender->GetName() == _T("closebtn"))
    {
        DestroyWindow(m_hWnd);
    }
    else if (msg.pSender->GetName() == _T("ok"))
    {
        DestroyWindow(m_hWnd);
    }
}