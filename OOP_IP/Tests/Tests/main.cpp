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

    return 0;
}