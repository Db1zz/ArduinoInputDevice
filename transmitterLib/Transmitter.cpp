#include "Transmitter.h"
#include <iostream>

Transmitter::Transmitter(LPCWSTR comName)
    : m_comName{ comName }
{
    std::cout << "Transmitter created!" << std::endl;
    openHandle(m_comName);
}

Transmitter::~Transmitter()
{
    std::cout << "Transmitter destroyed!" << std::endl;
    CloseHandle(m_hCom);
}

void Transmitter::openHandle(LPCWSTR comName)
{
    m_hCom = CreateFileW(m_comName,
                        GENERIC_READ | GENERIC_WRITE,
                        0, nullptr, OPEN_EXISTING,
                        0, nullptr);

    if(m_hCom == INVALID_HANDLE_VALUE)
    {
        std::cout << MSG_LIBRARY_NAME << "Handle to COM port ERROR: INVALID_HANDLE_VALUE" << MSG_FAILED << std::endl;
        exit(-1);
    }
}

BOOL Transmitter::closeHandle()
{
    return CloseHandle(m_hCom);
}

BOOL Transmitter::sendDataToComPort(uint8_t data)
{   

    BOOL result = WriteFile(m_hCom, 
                            &data, 
                            sizeof(data), 
                            nullptr, 
                            nullptr);
    if(result == false)
        std::cout << MSG_LIBRARY_NAME <<  "Cannot transmit data to the com port." << MSG_FAILED << std::endl;

    return result;
}

void Transmitter::readDataFromComPort()
{
    // TODO
}

void Transmitter::setComName(LPCWSTR comName)
{
    m_comName = comName;
}