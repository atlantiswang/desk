#include "MsgDlg.h"

DUI_BEGIN_MESSAGE_MAP(MsgDlg, WindowImplBase)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_END_MESSAGE_MAP()

MsgDlg::MsgDlg()
{
}

MsgDlg::~MsgDlg()
{
}

void MsgDlg::InitWindow()
{
}

CDuiString MsgDlg::GetSkinFile()
{
    return _T("XML_MSG");
}

LPCTSTR MsgDlg::GetWindowClassName() const
{
    return _T("MSGSSS");
}

void MsgDlg::OnClick(TNotifyUI& msg)
{
    if (msg.pSender->GetName() == _T("closebtn"))
    {
        Close(IDCANCEL);
    }
    else if (msg.pSender->GetName() == _T("ok"))
    {
        Close(IDOK);
    }
}