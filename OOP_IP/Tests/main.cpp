#include <iostream>
#include <Windows.h>
#include "../TVector/vector.h"



void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

namespace TestSystem {
    int count_success = 0, count_failed = 0;

    void start_test(bool(*test)(), const char* name_of_test) {
        set_color(2, 0);
        std::cout << "[ RUN      ]";
        set_color(7, 0);
        std::cout << name_of_test << std::endl;

        bool status = test();

        if (status == true) {
            set_color(2, 0);
            std::cout << "[       OK ]" << std::endl;
            count_success++;
        }
        else {
            set_color(4, 0);
            std::cout << "[  FAILED  ]" << std::endl;
            count_failed++;
        }
        set_color(7, 0);
    }

    template <class T>
    bool check(const T& expected, const T& actual) {
        if (expected == actual) {
            return true;
        }
        else {
            std::cerr << "Expected result is " << expected << ", but actual is " << actual << "." << std::endl;
            return false;
        }
    }

    void print_init_info() {
        set_color(2, 0);
        std::cout << "[==========] " << std::endl;
        set_color(7, 0);
    }

    void print_final_info() {
        set_color(2, 0);
        std::cout << "[==========] ";
        set_color(7, 0);
        std::cout << count_success + count_failed << " test" << (count_success + count_failed > 1 ? "s" : "") << " ran." << std::endl;
        set_color(2, 0);
        std::cout << "[  PASSED  ] ";
        set_color(7, 0);
        std::cout << count_success << " test" << (count_success > 1 ? "s" : "") << std::endl;
        if (count_failed > 0) {
            set_color(4, 0);
            std::cout << "[  FAILED  ] ";
            set_color(7, 0);
            std::cout << count_failed << " test" << (count_failed > 1 ? "s." : ".") << std::endl;
        }
    }
};

bool test_1_default_constructor_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec;
    if (vec.size() != 0 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_2_default_constructor_string()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec;
    if (vec.size() != 0 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_3_default_constructor_char()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec;
    if (vec.size() != 0 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_4_default_constructor_struct()
{
    bool expected_result = true;
    bool actual_result = true;
    struct Point { int x, y; };
    TVector<Point> vec;
    if (vec.size() != 0 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_5_sized_constructor_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec(5);
    if (vec.size() != 5 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_6_sized_constructor_null()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec(0);
    if (vec.size() != 0 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_7_sized_constructor_string()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec(0);
    if (vec.size() != 0 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_8_sized_constructor_char()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec(0);
    if (vec.size() != 0 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_9_sized_constructor_struct()
{
    bool expected_result = true;
    bool actual_result = true;
    struct Point { int x, y; };
    TVector<Point> vec(5);
    if (vec.size() != 5 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_10_array_constructor()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({ 1,2,3,4,5,6,7,8,9,10 }, 10);
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] != i + 1) actual_result = false;
    }
    if (vec.size() != 10 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_11_array_constructor_null()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({});
    if (vec.size() != 0 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_12_array_constructor_v2()
{
    bool expected_result = true;
    bool actual_result = true;
    int mass[10] = {1,2,3,4,5,6,7,8,9,10};
    size_t n = 10;
    TVector<int> vec(mass, n);
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] != i + 1) actual_result = false;
    }
    if (vec.size() != 10 || vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}


bool test_13_copy_constructor_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> original(10);
    TVector<int> copy(original);

    if (original.size() != copy.size() || original.capacity() != copy.capacity()) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}


bool test_14_copy_constructor_array()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> original({ 1, 2, 3, 4, 5 }, 5);
    TVector<int> copy(original);

    for (int i = 0; i < 5; ++i) {
        if (original[i] != copy[i]) actual_result = false;
    }
    if (original.size() != copy.size() || original.capacity() != copy.capacity()) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

//bool test_16_throw_when_copy_null_constructor_array()
//{
//    TVector<int> original({ }, 0);
//    bool actual_result = true;
//    bool expected_result = false;
//    try {
//        TVector<int> copy(original);
//    }
//    catch (const std::exception& ex) {
//        actual_result = false;
//    }
//    return TestSystem::check(expected_result, actual_result);
//}

bool test_15_copy_null_constructor_array_v2()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> original({});
    TVector<int> copy(original);
    if (original.size() != copy.size() || original.capacity() != copy.capacity()) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_16_reserve()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec;
    vec.reserve(75);
    if (vec.capacity() != 75) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_17_reserve_new_less_old()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec;
    vec.reserve(10);
    if (vec.capacity() != 15) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_18_reserve_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec(16);
    vec.reserve(50);
    if (vec.capacity() != 60) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_19_reserve_new_less_old_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec(16);
    vec.reserve(20);
    if (vec.capacity() != 30) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_20_reserve_mass()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({1, 2, 3}, 3);
    vec.reserve(50);
    if (vec.capacity() != 60 || vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_21_reserve_mass_v2()
{
    bool expected_result = true;
    bool actual_result = true;
    int mass[3] = { 1, 2, 3 };
    TVector<int> vec(mass, 3);
    vec.reserve(50);
    if (vec.capacity() != 60 || vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

//bool test_22_reserve_string()
//{
//    bool expected_result = true;
//    bool actual_result = true;
//    TVector<std::string> vec;
//    vec.reserve(50);
//    if (vec.capacity() != 60) actual_result = false;
//    return TestSystem::check(expected_result, actual_result);
//}

bool test_23_resize_int_upper()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec(5);
    vec.resize(50, 1);
    if (vec.capacity() != 60 || vec.size() != 50) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_24_resize_int_lower()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec(50);
    vec.resize(5);
    if (vec.capacity() != 60 || vec.size() != 5) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_25_resize_mass_upper()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({1, 2, 3}, 3);
    vec.resize(16, 9);
    for (int i = 3; i < 16; ++i) {
        if (vec[i] != 9) {
            actual_result = false;
        }
    }
    if (vec.capacity() != 30 || vec.size() != 16) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_26_resize_mass_lower()
{
    bool expected_result = true;
    bool actual_result = true;
    int mass[50];
    TVector<int> vec(mass, 50);
    vec.resize(14);
    if (vec.capacity() != 60 || vec.size() != 14) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_27_shrink_to_fit_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec(14);
    vec.reserve(100);
    vec.shrink_to_fit();
    if (vec.capacity() != 15 || vec.size() != 14) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_28_shrink_to_fit_mass()
{
    bool expected_result = true;
    bool actual_result = true;
    int mass[16];
    TVector<int> vec(mass, 16);
    vec.reserve(100);
    vec.shrink_to_fit();
    if (vec.capacity() != 30 || vec.size() != 16) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_29_emplace()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({1, 5, 9, 4, 6, 8}, 6);
    vec.emplace(4, 2);
    if (vec[4] != 2) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_30_throw_when_emplace_invalid_pos()
{
    bool expected_result = false;
    bool actual_result = true;
    TVector<int> vec({ 1, 5, 9, 4, 6, 8 }, 6);
    try {
        vec.emplace(10, 2);
    }
    catch (std::exception& ex) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}

bool test_31_assign()
{
    bool expected_result = true;
    bool actual_result = true;
    int mass[5] = { 4, 9, 1, 7, 5 };
    TVector<int> vec;
    vec.assign(mass, 3);
    if (vec[0] != 4 || vec[1] != 9 || vec[2] != 1) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_32_clear_mass()
{
    bool expected_result = true;
    bool actual_result = true;
    int mass[5] = { 4, 9, 1, 7, 5 };
    TVector<int> vec(mass, 5);
    vec.clear();
    if (vec.size() != 0) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_33_push_back_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec(5);
    vec.push_back(111);
    vec.push_back(99);
    vec.push_back(1);
    if (vec[5] != 111 || vec[6] != 99 || vec[7] != 1) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_34_push_back_char()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec;
    vec.push_back('5');
    vec.push_back('h');
    vec.push_back('#');
    if (vec[0] != '5' || vec[1] != 'h' || vec[2] != '#') actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_35_push_back_string()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec;
    vec.push_back("Hello");
    vec.push_back("there");
    vec.push_back("guys");
    if (vec[0] != "Hello" || vec[1] != "there" || vec[2] != "guys") actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_36_push_back_mass()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec;
    for (int i = 0; i < 10; i++) {
        vec.push_back(i);
    }
    if (vec.size() != 10 || vec[7] != 7) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_37_push_front_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec(5);
    vec.push_front(111);
    vec.push_front(99);
    vec.push_front(1);
    if (vec[0] != 1 || vec[1] != 99 || vec[2] != 111) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_38_push_front_char()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec;
    vec.push_front('5');
    vec.push_front('h');
    vec.push_front('#');
    if (vec[0] != '#' || vec[1] != 'h' || vec[2] != '5') actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_39_push_back_string()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec;
    vec.push_front("yo");
    vec.push_front("hi");
    vec.push_front("wassup");
    if (vec[0] != "wassup" || vec[1] != "hi" || vec[2] != "yo") actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_40_push_back_mass()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec;
    for (int i = 0; i < 10; i++) {
        vec.push_front(i);
    }
    if (vec.size() != 10 || vec[9] != 0 || vec[4] != 5) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_41_insert_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({1, 5, 9, 3}, 4);
    vec.insert(2, 499);
    if (vec[2] != 499 || vec[3] != 9 || vec.size() != 5) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_42_insert_int_it()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({ 1, 5, 9, 3 }, 4);
    vec.insert(vec.begin(), 499);
    if (vec[0] != 499 || vec[3] != 9 || vec.size() != 5) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_43_insert_char()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec({ '1', '5', '9', '3' }, 4);
    vec.insert(2, '4');
    if (vec[2] != '4' || vec[3] != '9' || vec.size() != 5) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_44_insert_char_it()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec({ '1', '5', '9', '3' }, 4);
    vec.insert(vec.begin(), '4');
    if (vec[0] != '4' || vec[3] != '9' || vec.size() != 5) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_45_insert_string()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec({ "yo", "gg", "hi", "qwerty"}, 4);
    vec.insert(2, "boo");
    if (vec[2] != "boo" || vec[3] != "hi" || vec.size() != 5) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_46_insert_string_it()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec({ "yo", "gg", "hi", "qwerty" }, 4);
    vec.insert(vec.begin(), "boo");
    if (vec[0] != "boo" || vec[3] != "hi" || vec.size() != 5) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_47_insert_int_it_count()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({ 1, 5, 9, 3 }, 4);
    vec.insert(vec.begin(), 3, 499);
    if (vec[0] != 499 || vec[1] != 499 || vec[2] != 499 || vec.size() != 7) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_48_insert_char_it_count()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec({ '1', '5', '9', '3' }, 4);
    vec.insert(vec.begin(), 3, '4');
    if (vec[0] != '4' || vec[1] != '4' || vec[2] != '4' || vec.size() != 7) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

//bool test_49_insert_string_it_count()
//{
//    bool expected_result = true;
//    bool actual_result = true;
//    TVector<std::string> vec({ "yo", "gg", "hi", "qwerty" }, 4);
//    vec.insert(vec.begin(), 3, "boo");
//    if (vec[0] != "boo" || vec[1] != "boo" || vec[2] != "boo" || vec[5] != "hi" || vec.size() != 7) actual_result = false;
//    return TestSystem::check(expected_result, actual_result);
//}

bool test_50_erase_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({ 1, 5, 9, 3 }, 4);
    vec.erase(2);
    if (vec[2] != 3 || vec[1] != 5 || vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_51_erase_int_it()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({ 1, 5, 9, 3 }, 4);
    vec.erase(vec.begin());
    if (vec[0] != 5 || vec[1] != 9 || vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_52_erase_char()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec({ '1', '5', '9', '3' }, 4);
    vec.erase(2);
    if (vec[2] != '3' || vec[1] != '5' || vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_53_erase_char_it()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec({ '1', '5', '9', '3' }, 4);
    vec.erase(vec.begin());
    if (vec[0] != '5' || vec[1] != '9' || vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_54_erase_string()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec({ "yo", "gg", "hi", "qwerty" }, 4);
    vec.erase(2);
    if (vec[2] != "qwerty" || vec[1] != "gg" || vec.size() != 4) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_55_erase_string_it()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec({ "yo", "gg", "hi", "qwerty" }, 4);
    vec.erase(vec.begin());
    if (vec[0] != "gg" || vec[2] != "qwerty" || vec.size() != 4) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_56_erase_int_it_count()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({ 1, 5, 9, 3 }, 4);
    vec.erase(vec.begin(), 3);
    if (vec[0] != 3 || vec.size() != 1) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_57_erase_char_it_count()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec({ '1', '5', '9', '3' }, 4);
    vec.erase(vec.begin(), 3);
    if (vec[0] != '3' ||  vec.size() != 1) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_58_erase_int_it_range()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({ 1, 5, 9, 3 }, 4);
    vec.erase(vec.begin(), vec.end());
    if (vec.size() != 0) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_59_erase_char_it_range()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec({ '1', '5', '9', '3' }, 4);
    vec.erase(vec.begin(), vec.end());
    if (vec.size() != 0) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_60_pop_back_int()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> vec({ 1, 5, 9, 3 }, 4);
    vec.pop_back();
    if (vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_61_pop_back_char()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec({ '1', '5', '9', '3' }, 4);
    vec.pop_back();
    if (vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_62_pop_back_string()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec({ "1", "5", "9", "3" }, 4);
    vec.pop_back();
    if (vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_63_pop_front_char()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<char> vec({ '1', '5', '9', '3' }, 4);
    vec.pop_front();
    if (vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_64_pop_front_int()
{
    bool expected_result = true;
    bool actual_result = true;
    int mass[4] = { 1, 5, 9, 3 };
    TVector<int> vec(mass, 4);
    vec.pop_front();
    if (vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

bool test_65_pop_back_string()
{
    bool expected_result = true;
    bool actual_result = true;
    TVector<std::string> vec({ "1", "5", "9", "3" }, 4);
    vec.pop_front();
    if (vec.size() != 3) actual_result = false;
    return TestSystem::check(expected_result, actual_result);
}

int main()
{
    TestSystem::start_test(test_1_default_constructor_int, "test_1_default_constructor_int");
    TestSystem::start_test(test_2_default_constructor_string, "test_2_default_constructor_string");
    TestSystem::start_test(test_3_default_constructor_char, "test_3_default_constructor_char");
    TestSystem::start_test(test_4_default_constructor_struct, "test_4_default_constructor_struct");
    TestSystem::start_test(test_5_sized_constructor_int, "test_5_sized_constructor_int");
    TestSystem::start_test(test_6_sized_constructor_null, "test_6_sized_constructor_null");
    TestSystem::start_test(test_7_sized_constructor_string, "test_7_sized_constructor_string");
    TestSystem::start_test(test_8_sized_constructor_char, "test_8_sized_constructor_char");
    TestSystem::start_test(test_9_sized_constructor_struct, "test_9_sized_constructor_struct");
    TestSystem::start_test(test_10_array_constructor, "test_10_array_constructor");
    TestSystem::start_test(test_11_array_constructor_null, "test_11_array_constructor_null");
    TestSystem::start_test(test_12_array_constructor_v2, "test_12_array_constructor_v2");
    TestSystem::start_test(test_13_copy_constructor_int, "test_13_copy_constructor_int");
    TestSystem::start_test(test_14_copy_constructor_array, "test_14_copy_constructor_array");
    TestSystem::start_test(test_15_copy_null_constructor_array_v2, "test_15_copy_null_constructor_array_v2");



    TestSystem::start_test(test_16_reserve, "test_16_reserve");
    TestSystem::start_test(test_17_reserve_new_less_old, "test_17_reserve_new_less_old");
    TestSystem::start_test(test_18_reserve_int, "test_18_reserve_int");
    TestSystem::start_test(test_19_reserve_new_less_old_int, "test_19_reserve_new_less_old_int");
    TestSystem::start_test(test_20_reserve_mass, "test_20_reserve_mass");
    TestSystem::start_test(test_21_reserve_mass_v2, "test_21_reserve_mass_v2");
    //TestSystem::start_test(test_22_reserve_string, "test_22_reserve_string");
    TestSystem::start_test(test_23_resize_int_upper, "test_23_resize_int_upper");
    TestSystem::start_test(test_24_resize_int_lower, "test_24_resize_int_lower");
    TestSystem::start_test(test_25_resize_mass_upper, "test_25_resize_mass_upper");
    TestSystem::start_test(test_26_resize_mass_lower, "test_26_resize_mass_lower");
    TestSystem::start_test(test_27_shrink_to_fit_int, "test_27_shrink_to_fit_int");
    TestSystem::start_test(test_28_shrink_to_fit_mass, "test_28_shrink_to_fit_mass");
    TestSystem::start_test(test_29_emplace, "test_29_emplace");
    TestSystem::start_test(test_30_throw_when_emplace_invalid_pos, "test_30_throw_when_emplace_invalid_pos");
    TestSystem::start_test(test_31_assign, "test_31_assign");
    TestSystem::start_test(test_32_clear_mass, "test_32_clear_mass");


    TestSystem::start_test(test_33_push_back_int, "test_33_push_back_int");
    TestSystem::start_test(test_34_push_back_char, "test_34_push_back_char");
    TestSystem::start_test(test_35_push_back_string, "test_35_push_back_string");
    TestSystem::start_test(test_36_push_back_mass, "test_36_push_back_mass");
    TestSystem::start_test(test_37_push_front_int, " test_37_push_front_int");
    TestSystem::start_test(test_38_push_front_char, "test_38_push_front_char");
    TestSystem::start_test(test_39_push_back_string, "test_39_push_back_string");
    TestSystem::start_test(test_40_push_back_mass, "test_40_push_back_mass");
    TestSystem::start_test(test_41_insert_int, "test_41_insert_int");
    TestSystem::start_test(test_42_insert_int_it, "test_42_insert_int_it");
    TestSystem::start_test(test_43_insert_char, "test_43_insert_char");
    TestSystem::start_test(test_44_insert_char_it, "test_44_insert_char_it");
    TestSystem::start_test(test_45_insert_string, "test_43_insert_char");
    TestSystem::start_test(test_46_insert_string_it, "test_44_insert_string_it");
    TestSystem::start_test(test_47_insert_int_it_count, "test_47_insert_int_it_count");
    TestSystem::start_test(test_48_insert_char_it_count, "test_48_insert_char_it_count");
    //TestSystem::start_test(test_49_insert_string_it_count, "test_49_insert_string_it_count");
    TestSystem::start_test(test_50_erase_int, "test_50_erase_int");
    TestSystem::start_test(test_51_erase_int_it, "test_51_erase_int_it");
    TestSystem::start_test(test_52_erase_char, "test_52_erase_char");
    TestSystem::start_test(test_53_erase_char_it, "test_53_erase_char_it");
    //TestSystem::start_test(test_54_erase_string, "test_54_erase_string");
    //TestSystem::start_test(test_55_erase_string_it, "test_55_erase_string_it");
    TestSystem::start_test(test_56_erase_int_it_count, "test_56_erase_int_it_count");
    TestSystem::start_test(test_57_erase_char_it_count, "test_57_erase_char_it_count");
    TestSystem::start_test(test_58_erase_int_it_range, "test_58_erase_int_it_range");
    TestSystem::start_test(test_59_erase_char_it_range, "test_59_erase_char_it_range");
    TestSystem::start_test(test_60_pop_back_int, "test_60_pop_back_int");
    TestSystem::start_test(test_61_pop_back_char, "test_61_pop_back_char");
    TestSystem::start_test(test_62_pop_back_string, "test_62_pop_back_string");
    TestSystem::start_test(test_63_pop_front_char, "test_63_pop_front_char");
    TestSystem::start_test(test_64_pop_front_int, "test_64_pop_front_int");
    //TestSystem::start_test(test_65_pop_back_string, "test_65_pop_back_string");



    return 0;
}