#pragma once

class IModuleInterface
{
public:
	virtual ~IModuleInterface() {}

	virtual void InitModule() = 0;
	virtual void DeinitModule() = 0;
};

