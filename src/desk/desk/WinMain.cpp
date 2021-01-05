// desk.cpp : Defines the entry point for the application.
//
#include "resource.h"
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

    // 设置当前的工作目录
    CPaintManagerUI::SetCurrentPath(instancePath.c_str());

#ifdef _DEBUG
    instancePath.replace(instancePath.end() - wcslen(_T("Debug\\")), instancePath.end(), _T("release\\"));
#endif

    // 设置资源的三种方法
#if 1
    instancePath += _T("res\\");
    CPaintManagerUI::SetResourcePath(instancePath.c_str());
#elif 0
    CPaintManagerUI::SetResourcePath(instancePath.c_str());
    CPaintManagerUI::SetResourceZip(_T("res.zip"));
#else
    HRSRC hResource = ::FindResource(NULL, MAKEINTRESOURCE(IDR_ZIPRES), _T("ZIPRES"));
    HGLOBAL hg = LoadResource(hInstance, hResource);
    int nResData = SizeofResource(hInstance, hResource);
    CPaintManagerUI::SetResourceZip((LPBYTE)::LockResource(hg), nResData);
#endif

    if (!CResourceManager::GetInstance()->LoadResource(_T("res.xml"), NULL))
    {
        return -1;
    }

    std::unique_ptr<MainWindow> pMainWnd(new MainWindow);
    pMainWnd->Create(NULL, _T("MainWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pMainWnd->CenterWindow();
    pMainWnd->ShowModal();
    return 0;
}
