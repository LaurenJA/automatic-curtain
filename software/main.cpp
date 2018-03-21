#include <iostream>
#include "motor/MotorControl.h"

int main() 
{
    std::cout << "Starting..." << std::endl;
    
    MotorControl m(1,2,3);
    std::cout << "Created Motor object" << std::endl;
    return 0;
}