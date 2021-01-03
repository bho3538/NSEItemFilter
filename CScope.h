#pragma once

#include "IBindScopeDialog.h"

class ATL_NO_VTABLE CScope :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IBindScopeDialog
{
public:

	BEGIN_COM_MAP(CScope)
		COM_INTERFACE_ENTRY(IBindScopeDialog)
	END_COM_MAP()

	CScope();
	~CScope();

	HRESULT STDMETHODCALLTYPE AddScopeItem(PVOID pItem);
	HRESULT STDMETHODCALLTYPE RemoveScopeItem(PVOID pItem);
	HRESULT STDMETHODCALLTYPE IsItemIncluded(PVOID pItem, int index);
	HRESULT STDMETHODCALLTYPE GetKnownScopeID(REFIID riid);
	HRESULT STDMETHODCALLTYPE IsEmpty();
	HRESULT STDMETHODCALLTYPE Flatten();
	HRESULT STDMETHODCALLTYPE IsEqual(PVOID pItem, int cmpMode);
	HRESULT STDMETHODCALLTYPE Clone(REFIID riid, PVOID* ppvOut);
	HRESULT STDMETHODCALLTYPE RemoveRootsMatchingUrlScheme(LPWSTR pStr);
	HRESULT STDMETHODCALLTYPE AddScopeTreeItem(PVOID pItem, PVOID* ppvOut, int* pOut);
	HRESULT STDMETHODCALLTYPE RemoveScopeTreeItem(PVOID pItem, PVOID* ppvOut, int* pOut);
};

