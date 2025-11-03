#pragma once
#include <string>
#include "InputHookWindowsBase.h"


class InputHookWindowsLParam: public InputHookWindowsBase
{
protected:

	HHOOK CrerateWinHook() override;

	static LRESULT CALLBACK KeyHandler(int nCode, WPARAM wParam, LPARAM lParam);

};

