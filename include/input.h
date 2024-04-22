#ifndef INPUT_H
#define INPUT_H

#include "transmitter.h"
#include "mouse.h"
#include "keyboard.h"
#include <Windows.h>

class Input : public Mouse, public Keyboard {
// Methods
// ----------------------------------------
public:
    Input::Input(LPCWSTR comName)
        : Mouse{ comName }, Keyboard{ comName }, Transmitter{ comName } {}
};

#endif // INPUT_H