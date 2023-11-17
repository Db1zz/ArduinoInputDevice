#include "input.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{  
    Input input{ L"//./COM5" };
    input.click(Input::Mouse::Left);


    std::cout << "Enter key to exit: ";
    while(true)
    {
        char k;
        std::cin >> k ;
        if(k > 0 )
            break;
    }
    return 0;
}