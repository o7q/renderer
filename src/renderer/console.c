#include "console.h"

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

void clear_screen()
{
#if defined(_WIN32) || defined(WIN32)
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    printf("\033[H\033[J");
#endif
}