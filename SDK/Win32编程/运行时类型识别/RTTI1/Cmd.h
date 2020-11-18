#pragma once
#include "obj.h"

class CCmd :public CObj
{
public:
	CCmd(void);
	~CCmd(void);

	DECLARE_DYNAMIC(CCmd)
//protected: 
//	static const CRuntimeClass* _GetBaseClass()
//	{
//		return ((CRuntimeClass*)(&CObj::classCObj));
//	}
//public:
//	static const CRuntimeClass classCCmd;
//	virtual const CRuntimeClass* GetRuntimeClass() const
//	{
//		return &classCCmd;
//	}
};

