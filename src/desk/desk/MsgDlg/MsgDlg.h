#pragma once

#include "../../DuiLib/code/UIlib.h"
using namespace DuiLib;

class MsgDlg : public WindowImplBase
{
public:
    MsgDlg();
    ~MsgDlg();
    DUI_DECLARE_MESSAGE_MAP()
public:
    virtual void InitWindow();
    virtual CDuiString GetSkinFile();
    virtual LPCTSTR GetWindowClassName() const;
    void OnClick(TNotifyUI& msg);
};
