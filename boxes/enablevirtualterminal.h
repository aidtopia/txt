#ifndef ENABLEVIRTUALTERMINAL_H
#define ENABLEVIRTUALTERMINAL_H

// Windows 10 has improved the Console to work like a Posix-style virtual
// terminal.  Specifically, it can now use UTF-8 for text and ANSI/VT/ECMA
// escape sequences for cursor control, color, etc.  But that functionality
// isn't necessarily enabled by default.  Create an instance of this class
// at the beginning of `main`, and it'll set the console's code page to
// UTF-8 and to enable virtual terminal processing.  Upon destruction, it
// restores the code page and mode.
class EnableVirtualTerminal {
    public:
        explicit EnableVirtualTerminal();
        ~EnableVirtualTerminal();

#ifdef _WIN32
    private:
        unsigned long m_original_mode;
        unsigned int m_original_code_page;
#endif
};

#endif
