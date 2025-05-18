#pragma once
#include "../Passport/passport.h"
#include "../TVector/vector.h"
#include "../Person/person.h"
#include "../Flights/flights.h"

#ifndef PASSENGER_H
#define PASSENGER_H

class Passenger : public Person {
	Passport _passport;
	TVector<Flights*> _flights;
public:
	Passenger(const FIO& fio, const Date& birth_date, const Passport& passport);
	const Passport& get_passport() const;
};

#endif // PASSENGER_H

