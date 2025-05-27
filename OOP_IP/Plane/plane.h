//  Copyright 2025 Sky_Trav1er
#pragma once
#include <iostream>
#include <string>

#ifndef PLANE_H
#define PLANE_H

class Plane {
    std::string _number;
    std::string _model;
    int _flight_hours;
    int _total_places;

 public:
    Plane(const std::string& number,
        const std::string& model, int hours, int seats);
    std::string get_number() const;
};

#endif  // PLANE_H
