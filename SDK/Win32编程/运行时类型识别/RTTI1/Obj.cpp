#include "Obj.h"

CRuntimeClass* CRuntimeClass::pFristClass = &CObj::classCObj;

CRuntimeClass CObj::classCObj = {"CObj",NULL,NULL};

CObj::CObj(void)
{
}


CObj::~CObj(void)
{
}
