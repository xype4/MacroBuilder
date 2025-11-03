#pragma once

#include "InputHookBase.h"
#include "IModuleInterface.h"
#include "Activator.h"

#include <vector>
#include <string>

class InputHandlerModule: public IModuleInterface
{
public:

	//Обработка Callback для нажатие на кнопку. Возвращаемое значение - блокировать ли дальнеёшую работу кнопки или нет
	bool HookActivate(std::string key, KeyEvent keyEvent);

	//Нажата ли клавиша и какой порядок, -1 клавиша не нажата
	int KeyIsPressed(std::string);

	void AddActivator(std::string InName, std::vector <KeyActivator>& InActivators, bool InFixedKeyOrder);

	void InitModule() override;
	void DeinitModule() override;

private:

	void OnActivatorChangeState(std::string Name, bool isActivate);
	void TryToActivateActivators();

	std::vector <std::string> PressedKeys;
	std::vector <Activator*> Activators;
};

