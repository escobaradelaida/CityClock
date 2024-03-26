#ifndef CITYCLOCK_H
#define CITYCLOCK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <sstream>

class CityClock {
private:
    std::string* cityName;
    int hours;
    int minutes;
    int seconds;
    bool format12Hours; // true for 12 hours and false for 24 hours

public:
    // Constructors
    CityClock(); // Default constructor
    CityClock(int h, int m, int s, const char* city); // Constructor with parameters
    CityClock(const CityClock& other); // Copy constructor
    CityClock(CityClock&& other); // Move constructor

    // Destructor
    ~CityClock();

    // Assignment operators
    CityClock& operator=(const CityClock& other); // Copy assignment
    CityClock& operator=(CityClock&& other); // Move assignment

    // Member functions
    void toggleFormat(); // Toggles the time format
    void show() const; // Displays the time
    void tick(); // Advances time by one second

    // Conversion function to string
    operator std::string() const;

    // Addition operator to add seconds to the time
    CityClock operator+(int secondsToAdd) const;

    // Friend function for output stream operator
    friend std::ostream& operator<<(std::ostream& os, const CityClock& clock);
};

#endif // CITYCLOCK_H
