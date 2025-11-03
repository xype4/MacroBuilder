#include "InputHookWindowsLParam.h"
#include <string>
#include <iostream>


HHOOK InputHookWindowsLParam::CrerateWinHook()
{
	return SetWindowsHookEx(
		HookData,
		KeyHandler,
		NULL,
		0 
	);
}

LRESULT InputHookWindowsLParam::KeyHandler(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* pKeyInfo = (KBDLLHOOKSTRUCT*)lParam;

		LONG lParamName =
			(pKeyInfo->scanCode << 16) |
			(pKeyInfo->flags << 24);

		char keyName[128] = { 0 };

		int res = GetKeyNameTextA(lParamName, keyName, sizeof(keyName));

		if (InputHookBase::HookCallback)
		{
			if (InputHookBase::HookCallback(std::string(keyName), pKeyInfo->flags & LLKHF_UP ? KeyEvent::Up : KeyEvent::Down))
				return LRESULT();
		}

	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
