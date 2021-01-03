#pragma once

#include <atlbase.h>
//Undocumented Interface.

//655d1685-2bfd-4f7f-ad22-5ab61c8d8798
const IID IID_IBindScopeDialog = { 0x655d1685,0x2bfd,0x4f7f,{0xad,0x22,0x5a,0xb6,0x1c,0x8d,0x87,0x98} };

#if defined(__cplusplus) && !defined(CINTERFACE)

MIDL_INTERFACE("655d1685-2bfd-4f7f-ad22-5ab61c8d8798")
IBindScopeDialog : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE AddScopeItem(PVOID pItem) = 0;
	virtual HRESULT STDMETHODCALLTYPE RemoveScopeItem(PVOID pItem) = 0;
	virtual HRESULT STDMETHODCALLTYPE IsItemIncluded(PVOID pItem,int index) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetKnownScopeID(REFIID riid) = 0;
	virtual HRESULT STDMETHODCALLTYPE IsEmpty() = 0;
	virtual HRESULT STDMETHODCALLTYPE Flatten() = 0;
	virtual HRESULT STDMETHODCALLTYPE IsEqual(PVOID pItem,int cmpMode) = 0;
	virtual HRESULT STDMETHODCALLTYPE Clone(REFIID riid,PVOID* ppvOut) = 0;
	virtual HRESULT STDMETHODCALLTYPE RemoveRootsMatchingUrlScheme(LPWSTR pStr) = 0;
	virtual HRESULT STDMETHODCALLTYPE AddScopeTreeItem(PVOID pItem,PVOID* ppvOut,int* pOut) = 0;
	virtual HRESULT STDMETHODCALLTYPE RemoveScopeTreeItem(PVOID pItem, PVOID* ppvOut, int* pOut) = 0;
};
#endif