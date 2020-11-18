#pragma once
#include "stdafx.h"

class CObj
{
public:
	CObj();
	~CObj();
//------------------------------------------------------
//protected: 
//	static const CRuntimeClass* _GetBaseClass() 
//	{
//		return NULL;
//	}
public:
	static CRuntimeClass classCObj;
	virtual const CRuntimeClass* GetRuntimeClass()
	{
		return &classCObj;
	}
//------------------------------------------------------
	//BOOL IsKindOf(const CRuntimeClass* pClass)
	//{
	//	const CRuntimeClass* pClassThis = GetRuntimeClass();
	//	return pClassThis->IsDerivedFrom(pClass);
	//}
};

