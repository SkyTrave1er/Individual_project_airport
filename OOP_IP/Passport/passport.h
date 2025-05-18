#pragma once
#include "../Date/date.h"

#ifndef PASSPORT_H
#define PASSPORT_H

class Passport {
	int _series;
	int _number;
	Date _issue_date;
	Date _validaty_date;
public:
	Passport(int series, int number);

	int get_series() const;
	int get_number() const;

	bool is_valid(const Date current_date) const;
};
#endif // PASSPORT_H

