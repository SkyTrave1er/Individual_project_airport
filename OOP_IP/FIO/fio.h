#pragma once
#include <iostream>

#ifndef FIO_H
#define FIO_H

class FIO {
    std::string _first_name;
    std::string _second_name;
    std::string _last_name;
public:
    FIO(const std::string& second, const std::string& first, const std::string& last);

    std::string get_first_name() const;
    std::string get_second_name() const;
    std::string get_last_name() const;
};

#endif //  FIO_H