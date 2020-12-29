#pragma once

#include "../../DuiLib/code/UIlib.h"
using namespace DuiLib;

class MainWindow : public WindowImplBase
{
public:
    MainWindow();
    ~MainWindow();
    DUI_DECLARE_MESSAGE_MAP()
public:
    virtual void InitWindow();
    virtual CDuiString GetSkinFile();
    virtual LPCTSTR GetWindowClassName() const;
public:
    void OnClick(TNotifyUI& msg);
};
