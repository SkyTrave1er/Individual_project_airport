//  Copyright 2025 Sky_Trav1er
#pragma once

#ifndef AIRPORT_H
#define AIRPORT_H

#include "../Flights/flights.h"
#include <string>

class Airport {
    TVector<Flights> _flights;
    TVector<Plane> _planes;
    TVector<Employee> _employees;
    TVector<Passenger> _passengers;
 public:
    void load_data();
    void save_data();
    void delete_old_data();
    Flights* find_flight(const std::string& number);
};

#endif  // AIRPORT_H
