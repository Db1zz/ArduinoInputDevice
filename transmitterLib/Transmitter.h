#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <Windows.h>
#include <stdint.h>

// Messages
#define MSG_SUCCESS  " - SUCCESS"
#define MSG_FAILED   " - FAILED"
#define MSG_LIBRARY_NAME "[Transmitter]: "

// Com port settings
#define COM_BAUD_RATE 9600

class Transmitter
{
protected:
    HANDLE m_hCom;
    LPCWSTR m_comName;

public:
    Transmitter(LPCWSTR comName);
    ~Transmitter();

    void setComName(LPCWSTR comName);
    LPCWSTR getComName() { return m_comName; }

    HANDLE getHandle() { return m_hCom; }
    void openHandle(LPCWSTR comName);
    BOOL closeHandle();

    BOOL sendDataToComPort(uint8_t data);
    void readDataFromComPort();

};

#endif // TRANSMITTER_H