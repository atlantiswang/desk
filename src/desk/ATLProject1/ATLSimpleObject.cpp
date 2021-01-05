// ATLSimpleObject.cpp : Implementation of CATLSimpleObject

#include "stdafx.h"
#include "ATLSimpleObject.h"


// CATLSimpleObject

STDMETHODIMP CATLSimpleObject::Initialize(
    LPCITEMIDLIST pidlFolder, LPDATAOBJECT pDataObj, HKEY hProgID)
{
    FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
    STGMEDIUM stg = { TYMED_HGLOBAL };
    HDROP     hDrop;

    // Look for CF_HDROP data in the data object.
    if (FAILED(pDataObj->GetData(&fmt, &stg)))
    {
        // Nope! Return an "invalid argument" error back to Explorer.
        return E_INVALIDARG;
    }

    // Get a pointer to the actual data.
    hDrop = (HDROP)GlobalLock(stg.hGlobal);

    // Make sure it worked.
    if (NULL == hDrop)
        return E_INVALIDARG;

    // Sanity check - make sure there is at least one filename.
    UINT uNumFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
    HRESULT hr = S_OK;

    if (0 == uNumFiles)
    {
        GlobalUnlock(stg.hGlobal);
        ReleaseStgMedium(&stg);
        return E_INVALIDARG;
    }

    // Get the name of the first file and store it in our member variable m_szFile.
    if (0 == DragQueryFile(hDrop, 0, m_szFile, MAX_PATH))
        hr = E_INVALIDARG;

    GlobalUnlock(stg.hGlobal);
    ReleaseStgMedium(&stg);

    return hr;
}
HRESULT STDMETHODCALLTYPE CATLSimpleObject::QueryContextMenu(
    /* [annotation][in] */
    __in  HMENU hmenu,
    /* [annotation][in] */
    __in  UINT indexMenu,
    /* [annotation][in] */
    __in  UINT idCmdFirst,
    /* [annotation][in] */
    __in  UINT idCmdLast,
    /* [annotation][in] */
    __in  UINT uFlags)
{
    OutputDebugString(_T("desk:CATLSimpleObject::QueryContextMenu"));
    // If the flags include CMF_DEFAULTONLY then we shouldn't do anything.
    if (uFlags & CMF_DEFAULTONLY)
        return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);

    InsertMenu(hmenu, indexMenu, MF_BYPOSITION, idCmdFirst, _T("SimpleShlExt Test Item"));

    return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 1);
}

HRESULT STDMETHODCALLTYPE CATLSimpleObject::InvokeCommand(
    /* [annotation][in] */
    __in  CMINVOKECOMMANDINFO *pici)
{
    OutputDebugString(_T("desk:CATLSimpleObject::InvokeCommand"));
    // If lpVerb really points to a string, ignore this function call and bail out.
    if (0 != HIWORD(pici->lpVerb))
        return E_INVALIDARG;

    // Get the command index - the only valid one is 0.
    switch (LOWORD(pici->lpVerb))
    {
    case 0:
    {
        TCHAR szMsg[MAX_PATH + 32];

        wsprintf(szMsg, _T("The selected file was:\n\n%s"), m_szFile);

        MessageBox(pici->hwnd, szMsg, _T("SimpleShlExt"),
            MB_ICONINFORMATION);

        return S_OK;
    }
    break;

    default:
        return E_INVALIDARG;
        break;
    }
}

HRESULT STDMETHODCALLTYPE CATLSimpleObject::GetCommandString(
    /* [annotation][in] */
    __in  UINT_PTR idCmd,
    /* [annotation][in] */
    __in  UINT uType,
    /* [annotation][in] */
    __reserved  UINT *pReserved,
    /* [annotation][out] */
    __out_awcount(!(uType & GCS_UNICODE), cchMax)  LPSTR pszName,
    /* [annotation][in] */
    __in  UINT cchMax)
{
    USES_CONVERSION;

    // Check idCmd, it must be 0 since we have only one menu item.
    if (0 != idCmd)
        return E_INVALIDARG;

    // If Explorer is asking for a help string, copy our string into the
    // supplied buffer.
    if (uType & GCS_HELPTEXT)
    {
        LPCTSTR szText = _T("This is the simple shell extension's help");

        if (uType & GCS_UNICODE)
        {
            // We need to cast pszName to a Unicode string, and then use the
            // Unicode string copy API.
            lstrcpynW((LPWSTR)pszName, T2CW(szText), cchMax);
        }
        else
        {
            // Use the ANSI string copy API to return the help string.
            lstrcpynA(pszName, T2CA(szText), cchMax);
        }

        return S_OK;
    }

    return E_INVALIDARG;
}

STDMETHODIMP CATLSimpleObject::HandleMenuMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    OutputDebugString(_T("desk:CATLSimpleObject::HandleMenuMsg"));
    return E_NOTIMPL;
}

STDMETHODIMP CATLSimpleObject::HandleMenuMsg2(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    OutputDebugString(_T("desk:CATLSimpleObject::HandleMenuMsg2"));
    return E_NOTIMPL;
}
