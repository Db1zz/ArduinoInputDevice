#ifndef Mouse_H
#define Mouse_H

#include "Transmitter.h"
#include <Windows.h>

class Mouse : virtual public Transmitter
{
private:

public:
 Mouse(LPCWSTR comName);
 ~Mouse();


};


#endif // Mouse_H