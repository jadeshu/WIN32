// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "windows.h"

struct CRuntimeClass
{
	LPCSTR m_lpszClassName;
	CRuntimeClass* m_pBaseClass;
	CRuntimeClass* m_pNextClass;       // linked list of registered classes
	static CRuntimeClass* pFristClass;

	//BOOL IsDerivedFrom(const CRuntimeClass* pBaseClass) const
	//{
	//	// simple SI case
	//	const CRuntimeClass* pClassThis = this;
	//	while (pClassThis != NULL)
	//	{
	//		if (pClassThis == pBaseClass)
	//			return TRUE;
	//		pClassThis = pClassThis->m_pBaseClass;
	//	}
	//	return FALSE;       // walked to the top, no match 
	//}
};


#define DECLARE_DYNAMIC(class_name) \
public: \
	static CRuntimeClass class##class_name; \
	virtual const CRuntimeClass* GetRuntimeClass() ; \
//protected: \
//static const CRuntimeClass* _GetBaseClass() ; \


#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)(&class_name::class##class_name))

struct AFX_CLASSINIT
{
	AFX_CLASSINIT(CRuntimeClass* pNewClass)
	{
		//pNewClass->m_pNextClass = CRuntimeClass::pFristClass;
		//CRuntimeClass::pFristClass = pNewClass;
			CRuntimeClass **pTmp = &(CRuntimeClass::pFristClass->m_pNextClass);
			while(*pTmp)
			{
				pTmp = &((*pTmp)->m_pNextClass);
			}
			*pTmp = pNewClass;
			//pNewClass->m_pNextClass = NULL;
	}
};

#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name) \
	CRuntimeClass class_name::class##class_name = {#class_name, RUNTIME_CLASS(base_class_name), NULL }; \
	static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name);\
	const  CRuntimeClass* class_name::GetRuntimeClass() { return RUNTIME_CLASS(class_name); } 
	//*const  CRuntimeClass* class_name::_GetBaseClass()  { return RUNTIME_CLASS(base_class_name); } \