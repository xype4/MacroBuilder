#include "InputHookBase.h"
#include <iostream>

std::function<bool(std::string key, KeyEvent keyEvent)> InputHookBase::HookCallback = nullptr;

void InputHookBase::InitHook(int HookID, int HookData)
{
	this->HookID = HookID;
	this->HookData = HookData;

	int Code = CreateHook();

	if (Code == 0)
	{
		std::cout << "Success init hook " << HookData << std::endl;
	}
	else
	{
		std::cerr << "Failed to init hook " << HookData << ". Error code: " << Code << std::endl;
		delete this;
	}
}
void InputHookBase::DeinitHook()
{
	DeleteHook();
}

bool operator==(const InputHookBase& FirstHook, const InputHookBase& SecondHook) {

	return (FirstHook.HookID == SecondHook.HookID);
}
