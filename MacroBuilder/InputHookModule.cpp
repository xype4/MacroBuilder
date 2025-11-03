#include "InputHookModule.h"
#include <windows.h>
#include <iostream>

InputHookModule* InputHookModuleInstance = nullptr;

InputHookModule::InputHookModule()
{
	if(!InputHookModuleInstance)
	{
		InputHookModuleInstance = this;
		InitModule();
		std::cerr << "InputHookModule: Init " << std::endl;
	}
}

InputHookModule::~InputHookModule()
{
	DeinitModule();
	InputHookModuleInstance = nullptr;

	std::cerr << "InputHookModule: Destroyed " << std::endl;
}

const InputHookBase* InputHookModule::GetHookByID(int ID)
{
	for(auto const CurrentHook: Hooks)
	{
		if (CurrentHook->GetHookID() == ID)
			return CurrentHook;
	}
	return nullptr;
}

void InputHookModule::Start()
{
	std::cerr << "Started... " << std::endl;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}

void InputHookModule::InitModule()
{
	InputHookBase::HookCallback = HookCallback;
}

void InputHookModule::DeinitModule()
{
	for (auto& CurrentHook : Hooks)
	{
		if (CurrentHook)
		{
			CurrentHook->DeinitHook();
			delete CurrentHook;
		}			
	}
	Hooks.clear();
}
