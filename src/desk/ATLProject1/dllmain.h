// dllmain.h : Declaration of module class.

class CATLProject1Module : public ATL::CAtlDllModuleT< CATLProject1Module >
{
public :
	DECLARE_LIBID(LIBID_ATLProject1Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECT1, "{9bf40ff3-ea2c-413e-9262-5feca1a49354}")
};

extern class CATLProject1Module _AtlModule;
