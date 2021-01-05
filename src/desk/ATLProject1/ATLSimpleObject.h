// ATLSimpleObject.h : Declaration of the CATLSimpleObject

#pragma once
#include "resource.h"       // main symbols



#include "ATLProject1_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CATLSimpleObject

class ATL_NO_VTABLE CATLSimpleObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CATLSimpleObject, &CLSID_ATLSimpleObject>,
	public IDispatchImpl<IATLSimpleObject, &IID_IATLSimpleObject, &LIBID_ATLProject1Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IShellExtInit,       //通用初始化
    public IContextMenu3        //右键菜单扩展、右键拖动扩展
{
public:
	CATLSimpleObject()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ATLSIMPLEOBJECT)

BEGIN_COM_MAP(CATLSimpleObject)
	COM_INTERFACE_ENTRY(IATLSimpleObject)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IShellExtInit)
    COM_INTERFACE_ENTRY(IContextMenu)
    COM_INTERFACE_ENTRY(IContextMenu2)
    COM_INTERFACE_ENTRY(IContextMenu3)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

    // IShellExtInit
    STDMETHODIMP Initialize(LPCITEMIDLIST, LPDATAOBJECT, HKEY);

    // IContextMenu
    STDMETHODIMP GetCommandString(UINT_PTR, UINT, UINT*, LPSTR, UINT);
    STDMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO);
    STDMETHODIMP QueryContextMenu(HMENU, UINT, UINT, UINT, UINT);

    // IContextMenu2
    STDMETHODIMP HandleMenuMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);

    // IContextMenu3
    STDMETHODIMP HandleMenuMsg2(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
protected:
    TCHAR m_szFile[MAX_PATH];
};

OBJECT_ENTRY_AUTO(__uuidof(ATLSimpleObject), CATLSimpleObject)
