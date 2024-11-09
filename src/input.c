#include "input.h"

#ifdef _WIN32
#include <windows.h>
#endif

bool key_pressed(int key)
{
#ifdef _WIN32
    // windows-specific input detection
    if (GetKeyState(key) & 0x8000)
    {
        return true;
    }
#endif
    return false;
}