#pragma once

#include <atlbase.h>
#include <ShObjIdl_core.h>

DEFINE_GUID(IID_IShellFolder3, 0x711b2cfd, 0x93d1, 0x422b, 0xbd,0xf4,0x69,0xbe,0x92,0x3f,0x24,0x49);
EXTERN_C const IID IID_IShellFolder3;

#if defined(__cplusplus) && !defined(CINTERFACE)

//New IShellFolder3 interface after Windows 7. (add some methods and interface id has been changed)
//Original interface(vista) struct from Geoff Chappell's homepage 'https://www.geoffchappell.com/studies/windows/shell/shell32/interfaces/ishellfolder3.htm'

MIDL_INTERFACE("711B2CFD-93D1-422B-BDF4-69BE923F2449")
IShellFolder3 : public IShellFolder2
{
public:
	virtual HRESULT STDMETHODCALLTYPE CreateFilteredIDList(PVOID pFilterCon /* IFilterCondition  */,INT unknownFilterListType,IPropertyStore* store,PITEMID_CHILD* pPidl) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetFilteredIDListType(PCITEMID_CHILD pidl, INT unknownFilterListType) = 0;
	virtual HRESULT STDMETHODCALLTYPE ModifyFilteredIDList(PCITEMID_CHILD pidl, PVOID pFilterCon /* IFilterCondition  */,PITEMID_CHILD* pPidl) = 0;
	virtual HRESULT STDMETHODCALLTYPE ReparentFilteredIDList(PCIDLIST_RELATIVE pidl,PIDLIST_RELATIVE* pPidl) = 0;
	virtual HRESULT STDMETHODCALLTYPE CreateStackedIDList(PROPERTYKEY* pKey,PIDLIST_ABSOLUTE* pPidl) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetStackedKey(PROPERTYKEY* pKey) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetStackData(REFIID iid, void** ppv) = 0; //New Method after Windows 7
	virtual HRESULT STDMETHODCALLTYPE EnumObjectsEx(HWND hwnd,IBindCtx* ctx,ULONG ulongVal, PVOID pFilter /* IItemFilter */, LPENUMIDLIST* pEnumList) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetConditions(PROPERTYKEY* pKey,PVOID pQueryUnit ,REFIID riid,PVOID* ppvOut) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetAutoListFlags(ULONG* flags) = 0;
};

#endif