#include <iostream>
#include <string>
#include <vector>

#include "InputHookModule.h"
#include "InputHookWindowsBase.h"
#include "InputHookWindowsLParam.h"
#include "InputHookWindowsWParam.h"
#include "InputHandlerModule.h"
#include "ModuleManager.h"
#include "XMLReader.h"



class ModuleManager;

int main() {
	//Создание модулей
	ModuleManager::AddModule<InputHandlerModule>();
	ModuleManager::AddModule<InputHookModule>();

	//Создание хуков
	InputHookModule* HookModule = ModuleManager::GetModule<InputHookModule>();
	HookModule->AddHook<InputHookWindowsLParam>(WH_KEYBOARD_LL);
	HookModule->AddHook<InputHookWindowsWParam>(WH_MOUSE_LL);

	
	//Связка модуля перехвата инпута и модуля обработки инпута
	InputHandlerModule* HandlerModule = ModuleManager::GetModule<InputHandlerModule>();

	ActivatorData Activator;
	XMLReader::ReadActivatorFromXML("XML/Activators/Activator1.xml", Activator);
	/*std::vector<KeyActivator> AS;
	AS.push_back(KeyActivator("A"));
	AS.push_back(KeyActivator("S"));*/
	//HandlerModule->AddActivator("A+S", AS, true);
	HandlerModule->AddActivator(Activator.Name, Activator.Keys, Activator.FixedKeyOrder);

	HookModule->HookCallback = [HandlerModule](std::string key, KeyEvent keyEvent) ->bool
		{
			return HandlerModule->HookActivate(key, keyEvent);
		};

	ModuleManager::InitAllModules();
	//Старт работы считывания нажатия клавиш
	HookModule->Start();
}

