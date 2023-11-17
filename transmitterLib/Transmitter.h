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
// Variables
// -------------------------------------
private:
    HANDLE  m_pCommHandle;
    LPCWSTR m_pCommName;

// Methods
// -------------------------------------
private:
    BOOL setDefaultComConfig();

public:
    Transmitter(LPCWSTR commName, LPDCB comConfig = nullptr);
    ~Transmitter();

    void setComName(LPCWSTR comName);
    LPCWSTR getComName() const { return m_pCommName; }

    HANDLE getHandle() const { return m_pCommHandle; }
    HANDLE openHandle(LPCWSTR comName);
    BOOL closeHandle();

    BOOL sendDataToComPort(char data);
};

#endif // TRANSMITTER_H