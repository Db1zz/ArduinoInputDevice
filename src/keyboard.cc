#include "keyboard.h"
#include <iostream>
#include <assert.h>

Keyboard::Keyboard(LPCWSTR comName)
    : Transmitter{ comName }
{
}

Keyboard::~Keyboard()
{
}

bool Keyboard::press(uint8_t key) {

    if(m_pressedKeys.find(key) == m_pressedKeys.end()) {
        sendDataToComPort(KEYBOARD_PRESS);
        sendDataToComPort(key);
        m_pressedKeys.insert(key);
        return true;
    }
    else {
        std::cout << LIBRARY_NAME << "Key " << "'" << key << "'" << " is already pressed." << MSG_FAILED << std::endl;
        return false;
    }
}

bool Keyboard::release(uint8_t key) {
    if(m_pressedKeys.find(key) != m_pressedKeys.end()) {
        sendDataToComPort(KEYBOARD_RELEASE);
        sendDataToComPort(key);
        m_pressedKeys.erase(key);
        return true;
    }
    else {
        std::cout << LIBRARY_NAME << "Key " << "'" << key << "'" << " is already released." << MSG_FAILED << std::endl;
        return false;
    }
}

bool Keyboard::releaseAll() {
    for(auto key : m_pressedKeys) {
        sendDataToComPort(KEYBOARD_RELEASE_ALL);
        sendDataToComPort(key);
    }
    m_pressedKeys.clear();
    return true;
}
