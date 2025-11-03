#pragma once
#include <vector>
#include "IModuleInterface.h"

class ModuleManager
{
public:
	template<typename T>
	static T* GetModule()
	{
		for (IModuleInterface* module : AllModules) {
			if (T* casted = dynamic_cast <T*>(module)) {
				return casted;
			}
		}
		return nullptr;
	}

	template<typename T>
	static void AddModule()
	{
		IModuleInterface* NewModule = new T();
		AllModules.push_back(NewModule);
	}

	static void InitAllModules()
	{
		for(auto& CurrentModule: AllModules)
		{
			InitModule(CurrentModule);
		}
	}

	static void InitModule(IModuleInterface* Module)
	{
		Module->InitModule();
	}

private:
	static std::vector <IModuleInterface*> AllModules;

};

