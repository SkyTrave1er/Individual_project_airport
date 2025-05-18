#pragma once
#include "../Date/date.h"
#include "../FIO/fio.h"

#ifndef PERSON_H
#define PERSON_H

class Person {
	FIO _fio;
	Date _birth_date;
public:
	Person(const FIO& fio, const Date& birth_date);
	FIO get_fio() const;
};
#endif // PERSON_H
