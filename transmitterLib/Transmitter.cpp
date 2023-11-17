#include "Transmitter.h"
#include <iostream>
#include <thread>

Transmitter::Transmitter(LPCWSTR comName, LPDCB comConfig)
    : m_pCommName{ comName }
{
    openHandle(m_pCommName);
    if(comConfig == nullptr)
        setDefaultComConfig();
    else
        SetCommState(m_pCommHandle, comConfig);
}

Transmitter::~Transmitter()
{
    CloseHandle(m_pCommHandle);
    delete m_pCommName, m_pCommHandle;
}

void Transmitter::setComName(LPCWSTR comName)
{
    m_pCommName = comName;
}

BOOL Transmitter::setDefaultComConfig()
{
    LPDCB config = new DCB;
    BOOL result;
    do
    {
        result = GetCommState(m_pCommHandle, config);
        if(!result) break;
        
        config->BaudRate = CBR_9600;
        config->StopBits = ONESTOPBIT;
        config->Parity   = NOPARITY;
        config->ByteSize = 8;
        
        result = SetCommState(m_pCommHandle, config);
        if(!result) break;

    } while(false);

    delete config;
    return result;
}

HANDLE Transmitter::openHandle(LPCWSTR commName)
{
    if(m_pCommHandle == nullptr)
    {
        m_pCommHandle = CreateFileW(m_pCommName,
                                    GENERIC_READ | GENERIC_WRITE,
                                    0, 
                                    nullptr, 
                                    OPEN_EXISTING,
                                    0, 
                                    nullptr);

        if(m_pCommHandle == INVALID_HANDLE_VALUE)
        {
            std::cout << MSG_LIBRARY_NAME << "Handle to COM port ERROR: INVALID_HANDLE_VALUE" << MSG_FAILED << std::endl;
            exit(-1);
        }
        return  m_pCommHandle;
    }
    return nullptr;   
}

BOOL Transmitter::closeHandle()
{
    BOOL result = CloseHandle(m_pCommHandle);
    m_pCommHandle = nullptr;
    return result;
}

BOOL Transmitter::sendDataToComPort(char data)
{   
    DWORD lpNumberOfBytesWritten;
    BOOL result = WriteFile(m_pCommHandle, 
                            &data, 
                            sizeof(data), 
                            &lpNumberOfBytesWritten, 
                            nullptr);
    if(result == false)
        std::cout << MSG_LIBRARY_NAME <<  "Cannot transmit data to the com port." << MSG_FAILED << std::endl;
    while(lpNumberOfBytesWritten < sizeof(data)){}
    return result;
}