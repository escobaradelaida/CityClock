#include "CityClock.h"

// constructor
CityClock::CityClock() {
    hours = 0;
    minutes = 0;
    seconds = 0;
    format12Hours = true;
    // project wants Rocher, Michigan as our cityName
    cityName = new std::string("Rochester, Michigan");
}

CityClock::CityClock(int h, int m, int s, const char* city) {
    hours = h;
    minutes = m;
    seconds = s;
    format12Hours = true;  // want it to be in 12-hour format first
    cityName = new std::string(city);
}

// copy constructor. there is a constant reference to CityClock object 'other'
// 'other' will copy time components to be constructor
CityClock::CityClock(const CityClock& other) {
    hours = other.hours;
    minutes = other.minutes;
    seconds = other.seconds;
    format12Hours = other.format12Hours;
    // allocating memory for new string object and init with other.cityName value
    // this allows for CityClock object to have its own city name
    cityName = new std::string(*other.cityName);
}

// move constructor for the CityClock class
CityClock::CityClock(CityClock&& other) {
    // also copies values of the time components
    hours = other.hours;
    minutes = other.minutes;
    seconds = other.seconds;
    format12Hours = other.format12Hours;
    cityName = other.cityName;
    // other.cityName value points to nullptr
    other.cityName = nullptr;
}

// destructor
CityClock::~CityClock() {
    delete cityName;
}

// copy assignment for CityClock class
CityClock& CityClock::operator=(const CityClock& other) {
    // checking if *this is not the same as 'other' object
    if (this != &other) {
        // delete allocated memory pointed to by cityName
        delete cityName;
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;
        format12Hours = other.format12Hours;
        // string object pointed by 'other.cityName'
        cityName = new std::string(*other.cityName);
    }
    return *this; // return current object
}

// move operator same as the top one
CityClock& CityClock::operator=(CityClock&& other) {
    if (this != &other) {
        delete cityName;
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;
        format12Hours = other.format12Hours;
        cityName = other.cityName;
        other.cityName = nullptr;
    }
    return *this;
}

void CityClock::toggleFormat() {
    format12Hours = !format12Hours;
}

// function that will print out the time format
void CityClock::show() const {
    // *cityName points to New York
    std::cout << *cityName << " - ";
    // this will be in 12 hour format
    if (format12Hours) {
        if (hours < 12)
            std::cout << std::setw(2) << std::setfill('0') << hours << ":"
                      << std::setw(2) << std::setfill('0') << minutes << ":"
                      << std::setw(2) << std::setfill('0') << seconds << " AM";
        else if (hours == 12)
            std::cout << std::setw(2) << std::setfill('0') << hours << ":"
                      << std::setw(2) << std::setfill('0') << minutes << ":"
                      << std::setw(2) << std::setfill('0') << seconds << " PM";
        else
            std::cout << std::setw(2) << std::setfill('0') << (hours - 12) << ":"
                      << std::setw(2) << std::setfill('0') << minutes << ":"
                      << std::setw(2) << std::setfill('0') << seconds << " PM";
    } else {
        std::cout << std::setw(2) << std::setfill('0') << hours << ":"
                  << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << std::setfill('0') << seconds;
    }
}

// the increase of secs
void CityClock::tick() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    seconds = localTime->tm_sec;
    minutes = localTime->tm_min;
    hours = localTime->tm_hour;
}

// converts CityClock object to a string
CityClock::operator std::string() const {
    // object called 'ss' is created and used to convert CityClock object into string rep
    std::stringstream ss;
    // this pointer is inserted to ss, which is overloaded
    ss << *this;
    // return 'ss' as a string
    return ss.str();
}

// defines overloaded addition operator. takes int argument secondsToAdd, repping the seconds being added to current CityClock object
// will return new CityClock object
CityClock CityClock::operator+(int secondsToAdd) const {
    // copy of current CityClock object is created and assigned to 'result'
    CityClock result(*this);
    //secondsToAdd added to seconds
    result.seconds += secondsToAdd;
    // if seconds > 59 after adding, exxcess seconds are converted to minutes
    if (result.seconds >= 60) {
        result.minutes += result.seconds / 60;
        result.seconds %= 60;
    }
    // if minutes > 59 after adding, exxcess seconds are converted to minutes
    if (result.minutes >= 60) {
        result.hours += result.minutes / 60;
        result.minutes %= 60;
    }
    // if hours > 23, time remains within 24 hours
    if (result.hours >= 24) {
        result.hours %= 24;
    }
    return result; // returns result
}

//  overloaded output stream with reference to an output stream 'os' and constant reference to a CityClock object 'clock'
std::ostream& operator<<(std::ostream& os, const CityClock& clock) {
    // inserts city name of 'clock' object into 'os'
    os << *clock.cityName << " - ";
    // applies to 12 hour format if 'clock' is 'true'
    if (clock.format12Hours) {
        if (clock.hours < 12)
            os << std::setw(2) << std::setfill('0') << clock.hours << ":"
               << std::setw(2) << std::setfill('0') << clock.minutes << ":"
               << std::setw(2) << std::setfill('0') << clock.seconds << " AM";
        else if (clock.hours == 12)
            os << std::setw(2) << std::setfill('0') << clock.hours << ":"
               << std::setw(2) << std::setfill('0') << clock.minutes << ":"
               << std::setw(2) << std::setfill('0') << clock.seconds << " PM";
        else
            os << std::setw(2) << std::setfill('0') << (clock.hours - 12) << ":"
               << std::setw(2) << std::setfill('0') << clock.minutes << ":"
               << std::setw(2) << std::setfill('0') << clock.seconds << " PM";
    } else {
        os << std::setw(2) << std::setfill('0') << clock.hours << ":"
           << std::setw(2) << std::setfill('0') << clock.minutes << ":"
           << std::setw(2) << std::setfill('0') << clock.seconds;
    }
    return os;
}