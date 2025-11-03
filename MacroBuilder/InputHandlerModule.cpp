#include "InputHandlerModule.h"
#include <iostream>

bool InputHandlerModule::HookActivate(std::string key, KeyEvent keyEvent)
{
	if(keyEvent == KeyEvent::Down)
	{
		if(KeyIsPressed(key) == -1)
		{
			PressedKeys.push_back(key);		
			TryToActivateActivators();
		} 
	}
	else
	{
		if (KeyIsPressed(key) != -1)
		{
			PressedKeys.erase(std::remove(PressedKeys.begin(), PressedKeys.end(), key), PressedKeys.end());
			TryToActivateActivators();
		}
	}

	return false;
}

int InputHandlerModule::KeyIsPressed(std::string Key)
{
	for (int i = 0; i < PressedKeys.size();i++)
	{
		if (PressedKeys[i] == Key)
			return i;
	}

	return -1;
}

void InputHandlerModule::AddActivator(std::string InName, std::vector <KeyActivator>& InActivators, bool InFixedKeyOrder)
{
	Activator* NewActivator = new Activator(InName, InActivators, InFixedKeyOrder);
	Activators.push_back(NewActivator);
}

void InputHandlerModule::OnActivatorChangeState(std::string Name, bool isActivate)
{
	std::cout << Name << (isActivate ?" Activate": " Deactivate") << std::endl;
}

void InputHandlerModule::TryToActivateActivators()
{
	for (auto& CurrentActivator: Activators)
	{
		if (CurrentActivator)
		{
			CurrentActivator->TryToActivate(PressedKeys);
		}			
	}
}

void InputHandlerModule::InitModule()
{
	Activator::OnChangeState = [this](std::string Name, bool isActivate) ->void
		{
			return OnActivatorChangeState(Name, isActivate);
		};
}

void InputHandlerModule::DeinitModule()
{
	PressedKeys.clear();
	Activators.clear();
}
