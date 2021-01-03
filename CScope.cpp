#include "stdafx.h"
#include "CScope.h"


CScope::CScope()
{
}


CScope::~CScope()
{
}

HRESULT STDMETHODCALLTYPE CScope::AddScopeItem(PVOID pItem) {
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CScope::RemoveScopeItem(PVOID pItem) {
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CScope::IsItemIncluded(PVOID pItem, int index) {
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CScope::GetKnownScopeID(REFIID riid) {
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CScope::IsEmpty() {
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CScope::Flatten() {
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CScope::IsEqual(PVOID pItem, int cmpMode) {
	return S_FALSE;
}
HRESULT STDMETHODCALLTYPE CScope::Clone(REFIID riid, PVOID* ppvOut) {
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CScope::RemoveRootsMatchingUrlScheme(LPWSTR pStr) {
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CScope::AddScopeTreeItem(PVOID pItem, PVOID* ppvOut, int* pOut) {
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE CScope::RemoveScopeTreeItem(PVOID pItem, PVOID* ppvOut, int* pOut) {
	return E_NOTIMPL;
}