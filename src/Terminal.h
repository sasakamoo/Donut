#ifndef TERMINAL_H_DEF
#define TERMINAL_H_DEF

#include <windows.h>

class Terminal {
private:
    DWORD size;
    DWORD originalMode;

public:
    Terminal();
    ~Terminal();

    void clearTerminal(char fillChar = ' ');

};


#endif