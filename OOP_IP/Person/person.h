//  Copyright 2025 Sky_Trav1er
#pragma once

#ifndef PERSON_H
#define PERSON_H

#include "../Date/date.h"
#include "../FIO/fio.h"

class Person {
    FIO _fio;
    Date _birth_date;

 public:
    Person(const FIO& fio, const Date& birth_date);
    FIO get_fio() const;
};
#endif  // PERSON_H
