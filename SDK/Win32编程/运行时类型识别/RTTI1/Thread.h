#pragma once
#include "cmd.h"
class CThread :public CCmd
{
public:
	CThread(void);
	~CThread(void);

	DECLARE_DYNAMIC(CThread)
};

