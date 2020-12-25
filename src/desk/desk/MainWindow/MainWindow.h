#pragma once

#include "../../DuiLib/code/UIlib.h"

using namespace DuiLib;
class MainWindow : public WindowImplBase
{
public:
    MainWindow();
    ~MainWindow();
public:
    virtual LPCTSTR GetWindowClassName() const;
    virtual CDuiString GetSkinFile();
};

