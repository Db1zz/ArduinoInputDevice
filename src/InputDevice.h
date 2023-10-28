#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <vector>
#include <Windows.h>
#include <string>

// Modifiers
#define KEY_LEFT_CTRL     0x80
#define KEY_LEFT_SHIFT    0x81
#define KEY_LEFT_ALT      0x82
#define KEY_LEFT_GUI      0x83
#define KEY_RIGHT_CTRL    0x84
#define KEY_RIGHT_SHIFT   0x85
#define KEY_RIGHT_ALT     0x86
#define KEY_RIGHT_GUI     0x87

class InputDevice
{
private: // Private Variablse
    const LPCWSTR k_comName;
    const std::string_view k_libraryName{"[InputDevice]: "};
    const std::string_view k_msgFailed{" - FAILED"};
    const std::string_view k_msgSuccess{" - SUCCESS"};

public: // Public Variables
    HANDLE m_inputDeviceHandle;

public: // Public Methods
    InputDevice(LPCWSTR comName);
    ~InputDevice();



};


#endif // INPUTDEVICE_H