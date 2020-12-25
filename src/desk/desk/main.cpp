// desk.cpp : Defines the entry point for the application.
//

#include <Windows.h>
#include "../DuiLib/code/UIlib.h"

using namespace DuiLib;

class CDuiFrameWnd : public WindowImplBase
{
public:
    virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
    virtual CDuiString GetSkinFile() { return _T("duilib.xml"); }
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    std::wstring instancePath = CPaintManagerUI::GetInstancePath();
    instancePath.replace(instancePath.end() - wcslen(_T("Debug\\")), instancePath.end(), _T("release\\"));
    CPaintManagerUI::SetResourcePath(instancePath.c_str());

    CDuiFrameWnd duiFrame;
    duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    duiFrame.CenterWindow();
    duiFrame.ShowModal();
    return 0;
}
