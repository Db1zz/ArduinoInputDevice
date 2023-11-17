#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <Windows.h>
#include <stdint.h>
#include <string>

// Messages
#define MSG_SUCCESS      " - SUCCESS"
#define MSG_FAILED       " - FAILED"
#define MSG_LIBRARY_NAME "[Transmitter]: "

class Transmitter
{
protected: // Protected Variables
    HANDLE  m_hCom;
    LPCWSTR m_comName;
    BOOL    m_recivingData = false;

private: // Private Methods
    BOOL setDefaultComConfig();
public: // Public Methods
    Transmitter(LPCWSTR comName, LPDCB comConfig = nullptr);
    ~Transmitter();

    void setComName(LPCWSTR comName);
    LPCWSTR getComName() { return m_comName; }

    HANDLE getHandle() { return m_hCom; }
    HANDLE openHandle(LPCWSTR comName);
    BOOL closeHandle();

    BOOL sendDataToComPort(char data);
};

#endif // TRANSMITTER_H