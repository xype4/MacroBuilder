#include "Activator.h"
#include "InputHandlerModule.h"

#include "ModuleManager.h"

std::function<void(std::string Name, bool isActivate)> Activator::OnChangeState = nullptr;

bool Activator::TryToActivate(std::vector<std::string>& AllInputs)
{
	InputHandlerModule* HandlerModule = ModuleManager::GetModule<InputHandlerModule>();

	int lastKeyIndex = -1;

	for(int i = 0; i < Activators.size(); i++)
	{
		int currentKeyIndex = HandlerModule->KeyIsPressed(Activators[i].Name);
		if(currentKeyIndex != -1)
		{
			if (FixedKeyOrder)
			{
				if (lastKeyIndex < currentKeyIndex)
				{
					lastKeyIndex = currentKeyIndex;
				}
				else
				{
					break;
				}
			}

			if(i == Activators.size()-1)
			{
				if(IsActive == false)
				{
					Activate();
					return false;
				}
			}
		}
		else
		{
			break;
		}
	}

	if (IsActive == true)
	{
		Deactivate();
	}
	return false;
}

void Activator::Activate()
{
	IsActive = true;
	OnChangeState(Name, true);
}

void Activator::Deactivate()
{
	IsActive = false;
	OnChangeState(Name, false);
}
