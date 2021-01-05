// ATLProject1.cpp : Implementation of DLL Exports.

//
// Note: COM+ 1.0 Information:
//      Please remember to run Microsoft Transaction Explorer to install the component(s).
//      Registration is not done by default.

#include "stdafx.h"
#include "resource.h"
#include "ATLProject1_i.h"
#include "dllmain.h"


using namespace ATL;

// Used to determine whether the DLL can be unloaded by OLE.
_Use_decl_annotations_
STDAPI DllCanUnloadNow(void)
{
	return _AtlModule.DllCanUnloadNow();
}

// Returns a class factory to create an object of the requested type.
_Use_decl_annotations_
STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry.
_Use_decl_annotations_
STDAPI DllRegisterServer(void)
{
    if (0 == (GetVersion() & 0x80000000UL))
    {
        CRegKey reg;
        LONG    lRet;

        lRet = reg.Open(HKEY_LOCAL_MACHINE,
            _T("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"),
            KEY_SET_VALUE);

        if (ERROR_SUCCESS != lRet)
            return E_ACCESSDENIED;

        lRet = reg.SetStringValue(
            _T("{46c25b09-ca5e-432e-ba34-f56f120a5b28}"),
            _T("Desk extension"));

        if (ERROR_SUCCESS != lRet)
            return E_ACCESSDENIED;
    }
	// registers object, typelib and all interfaces in typelib
	HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}

// DllUnregisterServer - Removes entries from the system registry.
_Use_decl_annotations_
STDAPI DllUnregisterServer(void)
{
    /*  取消注册为系统扩展
*/
    if (0 == (GetVersion() & 0x80000000UL))
    {
        CRegKey reg;
        LONG lRet = reg.Open(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"), KEY_SET_VALUE);
        if (ERROR_SUCCESS == lRet)
        {
            lRet = reg.DeleteValue(_T("{46c25b09-ca5e-432e-ba34-f56f120a5b28}"));
        }
        reg.Close();
    }
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

// DllInstall - Adds/Removes entries to the system registry per user per machine.
STDAPI DllInstall(BOOL bInstall, _In_opt_  LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if (pszCmdLine != nullptr)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ATL::AtlSetPerUserRegistration(true);
		}
	}

	if (bInstall)
	{
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}

	return hr;
}


