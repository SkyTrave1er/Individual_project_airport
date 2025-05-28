//  Copyright 2025 Sky_Trav1er
#pragma once

#ifndef PASSPORT_H
#define PASSPORT_H

#include "../Date/date.h"

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
#endif  // PASSPORT_H
