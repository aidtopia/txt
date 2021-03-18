#include "enablevirtualterminal.h"

#define NOMINMAX
#include <Windows.h>

EnableVirtualTerminal::EnableVirtualTerminal() {
#ifdef _WIN32
    // Use UTF-8 for output.
    m_original_code_page = ::GetConsoleOutputCP();
    if (m_original_code_page != CP_UTF8) {
        ::SetConsoleOutputCP(CP_UTF8);
    }

    // Interpret VT and ANSI escape sequences for color and styling.
    HANDLE hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    m_original_mode = 0;
    ::GetConsoleMode(hOut, &m_original_mode);
    if ((m_original_mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) == 0) {
        const auto new_mode =
            m_original_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        ::SetConsoleMode(hOut, new_mode);
    }
#endif
}

EnableVirtualTerminal::~EnableVirtualTerminal() {
#ifdef _WIN32
    HANDLE hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD current_mode = 0;
    ::GetConsoleMode(hOut, &current_mode);
    if (current_mode != m_original_mode) {
        ::SetConsoleMode(hOut, m_original_mode);
    }
    if (::GetConsoleOutputCP() != m_original_code_page) {
        ::SetConsoleOutputCP(m_original_code_page);
    }
#endif
}
