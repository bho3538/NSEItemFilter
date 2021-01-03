//Pseudo code

//------IShellFolder----------
HRESULT STDMETHODCALLTYPE CNSEFolder::ParseDisplayName(HWND hwndOwner, LPBC pbc, LPOLESTR pwszDisplayName, LPDWORD pchEaten, LPITEMIDLIST* ppidl, LPDWORD pdwAttributes)
{
	LPWSTR displayName = NULL;
	HRESULT hr = E_FAIL;
	
	//in DBFolder, pwszDisplayName value can be empty string.
	//in this case, use pbc(IBindCtx) to get pwszDisplayName value
	//see details in here 
	//(https://docs.microsoft.com/en-us/windows/win32/shell/str-constants ,STR_PARSE_WITH_PROPERTIES ) --byungho
	if (!pwszDisplayName || wcslen(pwszDisplayName) <= 0) {
		if (!pbc) {
			hr = E_INVALIDARG;
			goto escapeArea;
		}
		
		//First, try get pidl from pbc.
		*ppidl = _GetPIDLFromPBC(pbc);
		if (*ppidl) {
			hr = S_OK;
			goto escapeArea;
		}
		//Get displayName from pbc. (if failed to get pidl)
		displayName = _GetDisplayNameFromPBC(pbc);
		pwszDisplayName = displayName;
	}
	
	/*...Handle ParseDisplayName ...*/
escapeArea:

	if(displayName){
		CoTaskMemFree(displayName);
	}
	
	return hr;
}


//------IShellFolder3---------
HRESULT STDMETHODCALLTYPE CNSEFolder::CreateFilteredIDList(PVOID pFilterCon, INT unknownFilterListType, IPropertyStore* store, PITEMID_CHILD * pidl) {
	//unknown
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CNSEFolder::GetFilteredIDListType(PCITEMID_CHILD pidl, INT unknownFilterListType) {
	//unknown
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CNSEFolder::ModifyFilteredIDList(PCITEMID_CHILD pidl, PVOID pFilterCon, PITEMID_CHILD* pPidl) {
	//unknown
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CNSEFolder::ReparentFilteredIDList(PCIDLIST_RELATIVE aa, PIDLIST_RELATIVE* pPidl) {
	//unknown
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CNSEFolder::CreateStackedIDList(PROPERTYKEY* pkey, PIDLIST_ABSOLUTE* pPidl) {
	//unknown
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CNSEFolder::GetStackedKey(PROPERTYKEY* key) {
	//Item Filter From Column???
	*key = PKEY_Null; //Set Empty (if not, you can't click column in details view mode)
	return S_FALSE; //must S_FALSE
}

HRESULT STDMETHODCALLTYPE CNSEFolder::GetStackData(REFIID iid, void** ppv) {
	//unknown
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CNSEFolder::EnumObjectsEx(HWND hwnd, IBindCtx* ctx, DWORD dwFlags, PVOID pFilter, LPENUMIDLIST* ppEnumIdList) {
	//unknown
	HRESULT hr = EnumObjects(hwnd, dwFlags, ppEnumIdList);
	return hr;
}

HRESULT STDMETHODCALLTYPE CNSEFolder::GetConditions(PROPERTYKEY* pkey, PVOID iqueryUnit, REFIID riid, PVOID* ppvOut) {
	//Create simple query
	LPCWSTR sampleFilter = L"New*.*";

	HRESULT hr = _CreateSimpleQuery(sampleFilter, (ICondition**)ppvOut);
	return hr;
}

HRESULT STDMETHODCALLTYPE CNSEFolder::GetAutoListFlags(ULONG* flags) {
	//unknown
	return E_NOTIMPL;
}
//IObjectProvider
HRESULT STDMETHODCALLTYPE CNSEFolder::QueryObject(REFGUID guidObject, REFIID riid, void **ppvOut) {
	HRESULT hr = E_NOTIMPL;
	//See CScope.h
	if (riid == IID_IBindScopeDialog) {
		CComObject<CScope>* pscope = NULL;
		hr = CComObject<CScope>::CreateInstance(&pscope);
		if (hr == S_OK) {
			*ppvOut = pscope;
		}
	}

	return hr;
}

//------Helper function-------

HRESULT CNSEFolder::_CreateSimpleQuery(LPCWSTR queryString, ICondition** pCon) {
	IQueryParserManager *pqpm;
	HRESULT hr = CoCreateInstance(CLSID_QueryParserManager, NULL, CLSCTX_INPROC_SERVER, IID_IQueryParserManager, (PVOID*)&pqpm);
	if (SUCCEEDED(hr))
	{
		IQueryParser *pqp;
		hr = pqpm->CreateLoadedParser(L"", LOCALE_USER_DEFAULT, IID_IQueryParser, (PVOID*)&pqp);
		if (SUCCEEDED(hr)) {
			IQuerySolution *pqs;
			hr = pqp->Parse(queryString, NULL, &pqs);
			if (SUCCEEDED(hr))
			{
				ICondition *pc = NULL;
				hr = pqs->GetQuery( &pc, NULL);
				*pCon = pc;
				pqs->Release();
			}
			pqp->Release();
		}

		pqpm->Release();
	}
	return hr;
}
//Need free return data (use CoTaskMemFree)
LPWSTR CNSEFolder::_GetDisplayNameFromPBC(IBindCtx* pbc) {
	LPWSTR displayName = NULL;
	IUnknown* pQueryResult = NULL;
	IPropertyStore* pProp = NULL;
	PROPVARIANT var;

	if (!pbc) {
		goto escapeArea;
	}
	//undocumented value
	//According to MSDN, DBFolder use STR_PARSE_WITH_PROPERTIES value to get displayname in ParseDisplayname
	//but in Windows 10 (not sure in windows 7 or 8) , GetObjectParam with STR_PARSE_WITH_PROPERTIES return E_FAIL
	//And searchfolder call GetObjectParam with undocumented key "ParseWithQueryResult" 
	//(return value is undocumented interface IQueryResult) --byungho
#define STR_PARSE_WITH_QUERYRESULT L"ParseWithQueryResult"
	pbc->GetObjectParam(STR_PARSE_WITH_QUERYRESULT, &pQueryResult);
	if (pQueryResult) {
		pQueryResult->QueryInterface(IID_IPropertyStore, (PVOID*)&pProp);
	}
	else {
		//fall back
		pbc->GetObjectParam(STR_PARSE_WITH_PROPERTIES,(IUnknown**)&pProp);
	}

	if (pProp) {
		pProp->GetValue(PKEY_ItemNameDisplay, &var);
		if (var.vt == VT_LPWSTR) {
			displayName = var.pwszVal;
			var.pwszVal = NULL; //free later (use CoTaskMemFree)
		}
	}

escapeArea:

	if (pProp) {
		pProp->Release();
	}

	if (pQueryResult) {
		pQueryResult->Release();
	}

	return displayName;
}

LPITEMIDLIST CNSEFolder::_GetPIDLFromPBC(IBindCtx* pbc) {
	LPITEMIDLIST pidl = NULL;
	LPITEMIDLIST temp = NULL;
	IUnknown* pQueryResult = NULL;
	IPropertyStore* pProp = NULL;
	PROPVARIANT var;

	if (!pbc) {
		goto escapeArea;
	}
	//undocumented value
	//According to MSDN, DBFolder use STR_PARSE_WITH_PROPERTIES value to get displayname in ParseDisplayname
	//https://docs.microsoft.com/en-us/windows/win32/shell/str-constants
	//but in Windows 10 (not sure in windows 7 or 8) , GetObjectParam with STR_PARSE_WITH_PROPERTIES return E_FAIL
	//And searchfolder call GetObjectParam with undocumented key "ParseWithQueryResult" 
	//(return value is undocumented interface IQueryResult) --byungho
#define STR_PARSE_WITH_QUERYRESULT L"ParseWithQueryResult"
	pbc->GetObjectParam(STR_PARSE_WITH_QUERYRESULT, &pQueryResult);
	if (pQueryResult) {
		pQueryResult->QueryInterface(IID_IPropertyStore, (PVOID*)&pProp);
	}
	else {
		//fall back
		pbc->GetObjectParam(STR_PARSE_WITH_PROPERTIES, (IUnknown**)&pProp);
	}

	if (pProp) {
		//undocumented value (PKEY_DelegateIDList , {28636aa6-953d-11d2-b5d6-00c04fd918d0,32} ) 
		//return value : (unknown pidl(s)/parent folder pidl/item pidl) --byungho
		pProp->GetValue(PKEY_DelegateIDList, &var);
		if (var.vt == 4113) {
			//Get Last Pidl and copy it. (last pidl is item pidl)
			temp = (LPITEMIDLIST)var.calpstr.pElems;
			temp = ILFindLastID(temp);
			pidl = ILClone(temp);
			ILFree((LPITEMIDLIST)var.calpstr.pElems);
		}
	}

escapeArea:
	if (pProp) {
		pProp->Release();
	}

	if (pQueryResult) {
		pQueryResult->Release();
	}

	return pidl;
}