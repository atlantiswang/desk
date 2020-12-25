#include "MainWindow.h"

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
}

LPCTSTR MainWindow::GetWindowClassName() const
{ 
    return _T("MainWindow");
}

CDuiString MainWindow::GetSkinFile()
{ 
    return _T("duilib.xml");
}