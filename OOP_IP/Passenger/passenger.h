//  Copyright 2025 Sky_Trav1er
#pragma once

#ifndef PASSENGER_H
#define PASSENGER_H

#include "../Passport/passport.h"
#include "../TVector/vector.h"
#include "../Person/person.h"
#include "../Flights/flights.h"

class Passenger : public Person {
    Passport _passport;
    TVector<Flights*> _flights;

 public:
    Passenger(const FIO& fio, const Date& birth_date, const Passport& passport);
    const Passport& get_passport() const;
};

#endif  // PASSENGER_H
