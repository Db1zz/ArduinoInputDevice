#include "InputDevice.h"
#include <iostream>

// Library Message format convention:
// [LibraryName]: Message - STATUS

InputDevice::InputDevice(LPCWSTR comName)
    : k_comName{ comName }
{
    m_inputDeviceHandle = CreateFileW(k_comName, 
                                    GENERIC_READ | GENERIC_WRITE,
                                    0, nullptr,
                                    OPEN_EXISTING,
                                    0, nullptr);
    if(m_inputDeviceHandle == INVALID_HANDLE_VALUE)
    {
        std::cout << k_libraryName << "Cannot open handle to the input device!" << k_msgFailed << std::endl;
        exit(-1);
    }
    else std::cout << k_libraryName << "input device found!" << k_msgSuccess << std::endl;
}

InputDevice::~InputDevice()
{
    CloseHandle(m_inputDeviceHandle);
}