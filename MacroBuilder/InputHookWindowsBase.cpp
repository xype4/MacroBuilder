#include "InputHookWindowsBase.h"
#include <iostream>


int InputHookWindowsBase::CreateHook()
{
	Hook = CrerateWinHook();

	if (Hook)
	{
		return 0;
	}

	return 1;
}

void InputHookWindowsBase::DeleteHook()
{
	if (Hook)
	{
		UnhookWindowsHookEx(Hook);
		std::cout << "Hook deleted " << HookID << std::endl;
	}
}

