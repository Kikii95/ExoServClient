#pragma once
#include <iostream>
#include <functional>
#include <windows.h>

class Thread {
public:
    Thread(int id);
    ~Thread();

    void Start(std::function<void()> func);
    bool IsRunning() const;

private:
    static DWORD WINAPI Static_ThreadProc(LPVOID lpParameter);
    HANDLE m_Thread;
    std::function<void()> m_Function;
    bool m_Running;
    int m_Id;
};
