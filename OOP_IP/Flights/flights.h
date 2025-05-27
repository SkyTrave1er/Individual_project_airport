#pragma once
#include "../Time/time.h"
#include "../Destination/destination.h"
#include "../TVector/vector.h"
#include "../Plane/plane.h"
#include "../Passenger/passenger.h"
//  Copyright 2025 Sky_Trav1er
#include "../Employee/employee.h"

#include <string>

#ifndef FLIGHTS_H
#define FLIGHTS_H

enum class Flight_status { SCHEDULED, DELAYED, CANCELLED};

class Flights {
    Time _depart_time;
    Time _arrival_time;
    Destination _destination;
    Plane* _plane;
    std::string _flight_number;
    std::string _airline;
    TVector<Passenger*> _passeners;
    TVector<Employee*> _crew;

 public:
    Flights(const std::string& flight_number, const std::string& airline,
    const Destination& destination, Plane* plane,
        const Time& depart_time, const Time& arrival_time);

    void add_passenger(Passenger* passenger);
    void add_crew_member(Employee* emplyee);
    void set_status(Flight_status new_status);
};

#endif  // FLIGHTS_H
