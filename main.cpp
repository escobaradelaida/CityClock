#include "CityClock.h"
#include <iostream>

int main() {
    // Create a CityClock object using the default constructor
    CityClock clock1;
    std::cout << "Default Constructor - ";
    clock1.show();
    std::cout << std::endl;

    // Create a CityClock object with a specific time and city name. I chose New York.
    CityClock clock2(13, 35, 2, "New York");
    std::cout << "Custom Constructor - ";
    clock2.show();
    std::cout << std::endl;

    // Toggle the format of clock2
    clock2.toggleFormat();
    std::cout << "After toggling format - ";
    clock2.show();
    std::cout << std::endl;

    // Advance clock2 by one second and display
    clock2.tick();
    std::cout << "After ticking - ";
    clock2.show();
    std::cout << std::endl;

    // copy constructor
    CityClock clock3(clock2);
    std::cout << "Copy Constructor - ";
    clock3.show();
    std::cout << std::endl;

    // move constructor
    CityClock clock4(std::move(clock3));
    std::cout << "Move Constructor - ";
    clock4.show();
    std::cout << std::endl;

    // copy assignment operator
    CityClock clock5;
    clock5 = clock2;
    std::cout << "Copy Assignment Operator - ";
    clock5.show();
    std::cout << std::endl;

    // move assignment operator
    CityClock clock6;
    clock6 = std::move(clock4);
    std::cout << "Move Assignment Operator - ";
    clock6.show();
    std::cout << std::endl;

    // type conversion function
    std::string strClock = static_cast<std::string>(clock6);
    std::cout << "Type Conversion Function - " << strClock << std::endl;

    // addition operator
    CityClock clock7 = clock6 + 3600; // adding one hour (3600 seconds)
    std::cout << "Addition Operator - ";
    clock7.show();
    std::cout << std::endl;

    // ostream insertion operator
    std::cout << "Ostream Insertion Operator - " << clock7 << std::endl;

    return 0;
}
