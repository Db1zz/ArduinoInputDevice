#include "Mouse.h"
#include <iostream>

Mouse::Mouse(LPCWSTR comName)
    : Transmitter{comName}
{

}

Mouse::~Mouse()
{

}

void Mouse::move(int x, int y)
{

}
