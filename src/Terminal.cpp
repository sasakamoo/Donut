#include "Terminal.h"

Terminal::Terminal() {
    HANDLE terminalHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (terminalHandle == INVALID_HANDLE_VALUE) {
        perror("Invalid handle value!");
        exit(EXIT_FAILURE);
    }
    
    DWORD mode = 0;
    
    if (!GetConsoleMode(terminalHandle, &mode)) {
        perror("Invalid terminal mode!");
        exit(EXIT_FAILURE);
    }

    originalMode = mode;
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if (!SetConsoleMode(terminalHandle, mode)) {
        perror("Error setting terminal mode!");
        exit(EXIT_FAILURE);
    }
}

Terminal::~Terminal() {
    HANDLE terminalHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(terminalHandle, originalMode);
}

// Based off https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648
void Terminal::clearTerminal(char fillChar) {
    HANDLE terminalHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD home = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(terminalHandle, &csbi);
    DWORD written, cells = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(terminalHandle, fillChar, cells, home, &written);
    SetConsoleCursorPosition(terminalHandle, home);
}

void Terminal::print(const char* string) {
    HANDLE terminalHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsole(terminalHandle, string, (DWORD) strlen(string), NULL, NULL);
}