#include "input.h"

Input::Input(LPCWSTR comName)
        : Mouse{ comName }, Keyboard{ comName }, Transmitter{ comName }
{

}
