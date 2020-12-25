// desk.cpp : Defines the entry point for the application.
//
#include <Windows.h>
#include "../DuiLib/code/UIlib.h"
#include "MainWindow/MainWindow.h"
#include <memory>

using namespace DuiLib;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    std::wstring instancePath = CPaintManagerUI::GetInstancePath();
    instancePath.replace(instancePath.end() - wcslen(_T("Debug\\")), instancePath.end(), _T("release\\"));
    CPaintManagerUI::SetResourcePath(instancePath.c_str());
    std::unique_ptr<MainWindow> pMainWnd(new MainWindow);
    pMainWnd->Create(NULL, _T("MainWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pMainWnd->CenterWindow();
    pMainWnd->ShowModal();
    return 0;
}
