#include "InputHookWindowsWParam.h"
#include <string>
#include <iostream>


HHOOK InputHookWindowsWParam::CrerateWinHook()
{
	return SetWindowsHookEx(
		HookData,
		KeyHandler,
		NULL,
		0
	);
}

LRESULT InputHookWindowsWParam::KeyHandler(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
        MSLLHOOKSTRUCT* pMouseInfo = (MSLLHOOKSTRUCT*)lParam;
        std::string buttonName;
        KeyEvent eventType = KeyEvent::Down;

        switch (wParam)
        {
        case WM_LBUTTONDOWN: buttonName = "LMB"; eventType = KeyEvent::Down; break;
        case WM_LBUTTONUP:   buttonName = "LMB"; eventType = KeyEvent::Up; break;
        case WM_RBUTTONDOWN: buttonName = "RMB"; eventType = KeyEvent::Down; break;
        case WM_RBUTTONUP:   buttonName = "RMB"; eventType = KeyEvent::Up; break;
        case WM_MBUTTONDOWN: buttonName = "MMB"; eventType = KeyEvent::Down; break;
        case WM_MBUTTONUP:   buttonName = "MMB"; eventType = KeyEvent::Up; break;
        case WM_XBUTTONDOWN:
            buttonName = (HIWORD(pMouseInfo->mouseData) == XBUTTON1) ? "XMB1" : "XMB2";
            eventType = KeyEvent::Down;
            break;
        case WM_XBUTTONUP:
            buttonName = (HIWORD(pMouseInfo->mouseData) == XBUTTON1) ? "XMB1" : "XMB2";
            eventType = KeyEvent::Up;
            break;
        }

        if (InputHookBase::HookCallback && !buttonName.empty())
        {
            if (InputHookBase::HookCallback(buttonName, eventType))
                return LRESULT();
        }
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
