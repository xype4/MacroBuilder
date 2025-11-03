#pragma once
#include "InputHookBase.h"

#include <string>
#include <windows.h>
#include <functional>
#include <vector>
#include "IModuleInterface.h"

class InputHookModule: public IModuleInterface
{
public:

    //Callback для нажатие на кнопку. Возвращаемое значение - блокировать ли дальнеёшую работу кнопки или нет
    std::function<bool(std::string key, KeyEvent keyEvent)> HookCallback;

    InputHookModule();
    ~InputHookModule();

    //Добавить хук
    template<typename T>
    void AddHook(int HookData) {
        static_assert(std::is_base_of<InputHookBase, T>::value, "Type T must derive from InputHookBase to be used with AddHandler.");
        InputHookBase* CreatedHook = new T();

        CreatedHook->InitHook(lastHookID, HookData);
        Hooks.push_back(CreatedHook);

        lastHookID++;
    }

    //Получить Хук по ИД
    const InputHookBase* GetHookByID(int ID);

    //Запустить отслеживание ввода
    void Start();

    void InitModule() override;
    void DeinitModule() override;

private:
    //Индексация хуков для создания уникальный ИД (Костыль? ДА! и похуй)
    int lastHookID = 0;

    //Массив всех хуков
    std::vector<InputHookBase*> Hooks;
};


