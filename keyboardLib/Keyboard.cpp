#include "Keyboard.h"
#include <iostream>
#include <assert.h>

Keyboard::Keyboard(LPCWSTR comName)
    : Transmitter{ comName }
{
    std::cout << "Keyboard created!" << std::endl;
}

Keyboard::~Keyboard()
{
    std::cout << "Keyboard destroyed!" << std::endl;
}

bool Keyboard::press(uint8_t key)
{
    if(m_hCom != INVALID_HANDLE_VALUE)
    {
        if(m_map.find(key) == m_map.end())
        {
            sendDataToComPort(',');
            sendDataToComPort(key);
            m_map.insert(key);
            return true;
        }
        else{
            std::cout << LIBRARY_NAME << "Key " << "'" << key << "'" << " is already pressed." << MSG_FAILED << std::endl;
            return false;
        }
    }
    else{
        std::cout << LIBRARY_NAME << "Handle to COM port ERROR: INVALID_HANDLE_VALUE" << MSG_FAILED << std::endl;
        return false;
    }
}
bool Keyboard::release(uint8_t key)
{
    if(m_hCom != INVALID_HANDLE_VALUE)
    {
        if(m_map.find(key) != m_map.end())
        {
            sendDataToComPort('.');
            sendDataToComPort(key);
            m_map.erase(key);
            return true;
        }
        else{
           std::cout << LIBRARY_NAME << "Key " << "'" << key << "'" << " is already released." << MSG_FAILED << std::endl;
           return false;
        }
    }
    else{
        std::cout << LIBRARY_NAME << "Handle to COM port ERROR: INVALID_HANDLE_VALUE" << MSG_FAILED << std::endl;
        return false;
    }
}

bool Keyboard::releaseAll()
{
    if(m_hCom != INVALID_HANDLE_VALUE)
    {
        for(auto key : m_map)
        {
            sendDataToComPort('.');
            sendDataToComPort(key);
        }
        m_map.clear();
    }
    else{
        std::cout << LIBRARY_NAME << "Handle to COM port ERROR: INVALID_HANDLE_VALUE" << MSG_FAILED << std::endl;
        return false;
    }
    return true;
}