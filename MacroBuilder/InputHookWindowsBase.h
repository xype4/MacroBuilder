#pragma once
#include <windows.h>
#include "InputHookModule.h"

class InputHookWindowsBase: public InputHookBase
{
protected:

	HHOOK Hook;

	int CreateHook() override;
	virtual HHOOK CrerateWinHook() = 0;
	void DeleteHook() override;
};

