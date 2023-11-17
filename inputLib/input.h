#include "Transmitter.h"
#include "Mouse.h"
#include "Keyboard.h"
#include <Windows.h>

class Input : public Mouse, public Keyboard
{
public:
    Input(LPCWSTR comName);
};