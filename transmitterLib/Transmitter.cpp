#include "Transmitter.h"
#include <iostream>
#include <thread>

Transmitter::Transmitter(LPCWSTR comName, LPDCB comConfig)
    : m_comName{ comName }
{
    openHandle(m_comName);
    if(comConfig == nullptr)
        setDefaultComConfig();
    else
        SetCommState(m_hCom, comConfig);
}

Transmitter::~Transmitter()
{
    CloseHandle(m_hCom);    
}

void Transmitter::setComName(LPCWSTR comName)
{
    m_comName = comName;
}

BOOL Transmitter::setDefaultComConfig()
{
    LPDCB config = new DCB;
    BOOL result;
    do
    {
        result = GetCommState(m_hCom, config);
        if(!result) break;
        
        config->BaudRate = CBR_9600;
        config->StopBits = ONESTOPBIT;
        config->Parity   = NOPARITY;
        config->ByteSize = 8;
        
        result = SetCommState(m_hCom, config);
        if(!result) break;

    } while(false);

    delete config;
    return result;
}

HANDLE Transmitter::openHandle(LPCWSTR comName)
{
    m_hCom = CreateFileW(m_comName,
                        GENERIC_READ | GENERIC_WRITE,
                        0, 
                        nullptr, 
                        OPEN_EXISTING,
                        0, 
                        nullptr);

    if(m_hCom == INVALID_HANDLE_VALUE)
    {
        std::cout << MSG_LIBRARY_NAME << "Handle to COM port ERROR: INVALID_HANDLE_VALUE" << MSG_FAILED << std::endl;
        exit(-1);
    }
    return  m_hCom;
}

BOOL Transmitter::closeHandle()
{
    return CloseHandle(m_hCom);
}

BOOL Transmitter::sendDataToComPort(char data)
{   
    DWORD lpNumberOfBytesWritten;
    BOOL result = WriteFile(m_hCom, 
                            &data, 
                            sizeof(data), 
                            &lpNumberOfBytesWritten, 
                            nullptr);
    if(result == false)
        std::cout << MSG_LIBRARY_NAME <<  "Cannot transmit data to the com port." << MSG_FAILED << std::endl;
    while(lpNumberOfBytesWritten < sizeof(data)){}
    return result;
}
