//  Copyright 2025 Sky_Trav1er
#include "../Person/person.h"
#include <string>
#pragma once

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

enum class Position { PILOT, STEWARD, TECHNICAN};

class Employee : public Person {
    Position _position;
    int _experience;

 public:
    Employee(const std::string& name,
        const Date& birth_date, Position pos, int exp);
};
#endif  // EMPLOYEE_H
