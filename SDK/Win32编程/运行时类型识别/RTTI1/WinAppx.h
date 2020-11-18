#pragma once
#include "thread.h"
class CWinAppx :public CThread
{
public:
	CWinAppx(void);
	~CWinAppx(void);

	DECLARE_DYNAMIC(CWinAppx)
};

