#include "CityClock.h"

CityClock::CityClock() {
    hours = 0;
    minutes = 0;
    seconds = 0;
    format12Hours = true;
    cityName = new std::string("Rochester, Michigan");
}

CityClock::CityClock(int h, int m, int s, const char* city) {
    hours = h;
    minutes = m;
    seconds = s;
    format12Hours = true;
    cityName = new std::string(city);
}

CityClock::CityClock(const CityClock& other) {
    hours = other.hours;
    minutes = other.minutes;
    seconds = other.seconds;
    format12Hours = other.format12Hours;
    cityName = new std::string(*other.cityName);
}

CityClock::CityClock(CityClock&& other) {
    hours = other.hours;
    minutes = other.minutes;
    seconds = other.seconds;
    format12Hours = other.format12Hours;
    cityName = other.cityName;
    other.cityName = nullptr;
}

CityClock::~CityClock() {
    delete cityName;
}

CityClock& CityClock::operator=(const CityClock& other) {
    if (this != &other) {
        delete cityName;
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;
        format12Hours = other.format12Hours;
        cityName = new std::string(*other.cityName);
    }
    return *this;
}

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

void CityClock::show() const {
    std::cout << *cityName << " - ";
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

void CityClock::tick() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    seconds = localTime->tm_sec;
    minutes = localTime->tm_min;
    hours = localTime->tm_hour;
}

CityClock::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

CityClock CityClock::operator+(int secondsToAdd) const {
    CityClock result(*this);
    result.seconds += secondsToAdd;
    if (result.seconds >= 60) {
        result.minutes += result.seconds / 60;
        result.seconds %= 60;
    }
    if (result.minutes >= 60) {
        result.hours += result.minutes / 60;
        result.minutes %= 60;
    }
    if (result.hours >= 24) {
        result.hours %= 24;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const CityClock& clock) {
    os << *clock.cityName << " - ";
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