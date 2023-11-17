#ifndef INPUT_H
#define INPUT_H

#include "Transmitter.h"
#include "Mouse.h"
#include "Keyboard.h"
#include <Windows.h>

class Input : public Mouse, public Keyboard
{
// Methods
// ----------------------------------------
public:
    Input(LPCWSTR comName);
};

#endif // INPUT_H