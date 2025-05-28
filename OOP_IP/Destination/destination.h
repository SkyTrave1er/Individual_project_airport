//  Copyright 2025 Sky_Trav1er
#pragma once

#ifndef DESTINATION_H
#define DESTINATION_H

#include <iostream>
#include <string>

class Destination {
    std::string _country;
    std::string _city;
    std::string _airport;

 public:
    Destination(const std::string& country,
        const std::string& city, const std::string& airport);
};
#endif  // DESTINATION_H
