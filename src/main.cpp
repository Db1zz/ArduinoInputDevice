#include "Keyboard.h"
#include <iostream>


int main()
{   
    {
        Keyboard keyboard{L"//./COM12"};
        keyboard.press(KEY_LEFT_SHIFT);
        keyboard.press('a');
        keyboard.release('a');
        keyboard.release(KEY_LEFT_SHIFT);
    }


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