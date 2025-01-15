#include "Thread.h"

Thread::Thread(int id) : m_Thread(nullptr), m_Function(nullptr), m_Running(false), m_Id(id) {
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Thread " << m_Id << " created." << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}

Thread::~Thread() {
    if (m_Thread) {
        CloseHandle(m_Thread);
    }
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Thread " << m_Id << " destructed." << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}

void Thread::Start(std::function<void()> func) {
    m_Function = func;
    m_Running = true;
    m_Thread = CreateThread(nullptr, 0, Static_ThreadProc, this, 0, nullptr);
    if (m_Thread == nullptr) {
        std::cout << "------------------------------------------" << std::endl;
        std::cerr << "Thread " << m_Id << " creation failed." << std::endl;
        std::cout << "------------------------------------------" << std::endl;
        m_Running = false;
    }
}

bool Thread::IsRunning() const {
    return m_Running;
}

DWORD WINAPI Thread::Static_ThreadProc(LPVOID lpParameter) {
    Thread* thread = static_cast<Thread*>(lpParameter);
    if (thread->m_Function) {
        thread->m_Function();
    }
    thread->m_Running = false;
    return 0;
}
