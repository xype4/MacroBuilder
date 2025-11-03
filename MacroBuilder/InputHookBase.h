#pragma once
#include <functional>
#include <string>
#include <map>

enum KeyEvent {
    Up,     
    Down
};

class InputHookBase
{       
public:

    //Callback для нажатие на кнопку. Возвращаемое значение - блокировать ли дальнеёшую работу кнопки или нет
    static std::function<bool(std::string key, KeyEvent keyEvent)> HookCallback;

    int GetHookID()
    {
        return HookID;
    }
    void InitHook(int HookID, int HookData);
    void DeinitHook();

    friend bool operator==(const InputHookBase& FirstHook, const InputHookBase& SecondHook);

protected:

    int HookData;
    int HookID;


    virtual int CreateHook() = 0;

    virtual void DeleteHook() = 0;
};
