//  Copyright 2025 Sky_Trav1er
#pragma once

#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

class Time {
    int _hour;
    int _minut;

 public:
    Time(int hour, int minut);

    void add_hours(int h);
    void add_minuts(int m);
    std::string to_string() const;

    bool operator==(const Time& other) const;
    bool operator<(const Time& other) const;
};
#endif  // TIME_H
