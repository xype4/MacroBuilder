#pragma once
#include "InputHookBase.h"

#include <windows.h>
#include <functional>
#include <string>
#include <vector>

struct KeyActivator {
    std::string Name;

    KeyActivator(std::string InName):
        Name(InName){ }
};

class Activator
{
public:
    Activator(std::string InName,std::vector <KeyActivator>& InActivators, bool InFixedKeyOrder):
        Name(InName),
        Activators(InActivators),
        FixedKeyOrder(InFixedKeyOrder)
    { }

    bool TryToActivate(std::vector <std::string>& AllInputs);

    static std::function<void(std::string Name, bool isActivate)> OnChangeState;

private:

    void Activate();
    void Deactivate();


    //Активирован ли активатор
    bool IsActive = false;

    //Порядок ключей Activators важен и активатор активируется только при нажатии кнопок в аналогичном порядке
    bool FixedKeyOrder;

    //Название активатора
    std::string Name;

    //Условия ключи активации
    std::vector <KeyActivator> Activators;
};

