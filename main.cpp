//
// Created by LB on 26/09/2021.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>

typedef std::vector<ulong> digit_set;

ulong find_next_smallest(ulong number = 0);

ulong parse_input();

ulong magnitude(ulong number);

digit_set possible_digits(ulong number);

ulong minimum_possible_first_digit(ulong number);

ulong minimum_possible_other_digit(ulong number);

ulong first_digit(ulong number);

int main() {
    auto in = parse_input();
// debug
//    std::cout << "number: " << in << std::endl;
//    std::cout << "first digit: " << first_digit(in) << std::endl;
//    std::cout << "magnitude: " << magnitude(in) << std::endl;
//    std::cout << "new first digit: " << minimum_possible_first_digit(in) << std::endl;
//    std::cout << "available digits: " << std::endl;
//    auto ds = possible_digits(in);
//    for (auto d: ds) {
//        std::cout << d << " ";
//    }
//    std::cout << std::endl;
    auto next = find_next_smallest(in);
    std::cout << "next possible number: " << next << std::endl;

    // test 1
    if (find_next_smallest(2) == 3) {
        std::cout << "Test 1: passed" << std::endl;
    } else {
        std::cout << "Test 1: failed" << std::endl;
    }
    // test 2
    if (find_next_smallest(10) == 22) {
        std::cout << "Test 2: passed" << std::endl;
    } else {
        std::cout << "Test 2: failed" << std::endl;
    }
    // test 3
    if (find_next_smallest(98) == 100) {
        std::cout << "Test 3: passed" << std::endl;
    } else {
        std::cout << "Test 3: failed" << std::endl;
    }
    // test 4
    if (find_next_smallest(123456) == 700000) {
        std::cout << "Test 4: passed" << std::endl;
    } else {
        std::cout << "Test 4: failed" << std::endl;
    }
}

ulong magnitude(ulong number) {
    return (ulong) std::log10(number);
}

ulong first_digit(ulong number) {
    return (number / (ulong) pow(10, magnitude(number))); // integer division
}

ulong minimum_possible_other_digit(ulong number) {
    auto possibilities = possible_digits(number);
    auto it = possibilities.begin();
    return *it;
}

ulong minimum_possible_first_digit(ulong number) {
    auto fd = first_digit(number);
    ulong new_fd = 0;
    auto possibilities = possible_digits(number);
    auto it = possibilities.begin();
    if (*it == 0) it++;
    auto case_nine = *it;
    if (fd == 9) return case_nine;
    for (; it != possibilities.end(); it++) {
        if (fd < *it) {
            new_fd = *it;
            break;
        }
    }
    return new_fd;
}

ulong find_next_smallest(ulong number) { // 1234
    ulong next = minimum_possible_first_digit(number);
//    std::cout << "number: " << number << std::endl;
    auto exp = magnitude(number);
    if (first_digit(number) == 9) exp++;
    next *= pow(10, exp);
//    std::cout << "next before: " << next << std::endl;
//    std::cout << "exponent: " << exp << std::endl;
    // from second digit to end
    for (auto i = exp - 1; i != -1; i--) {
        // get new possible digit
        ulong d = minimum_possible_other_digit(number);
//        std::cout << "min: " << d << std::endl;
        // get the number to add
        d *= (ulong) pow(10, i);
        // sum
        next += d;
//        std::cout << "added: " << d << std::endl;
    }
//    std::cout << "next after: " << next << std::endl;
    return next;
}


ulong parse_input() {
    std::cout << "insert number: ";
    ulong number = 0;
    std::cin >> number;
    return number;
}

digit_set possible_digits(ulong number) {
    digit_set digits(10);
    std::iota(digits.begin(), digits.end(), 0);
    digit_set to_be_removed = {};
    std::string number_str = std::to_string(number);
    for (char c: number_str) {
        ulong d = c - '0';  // convert char to int
        to_be_removed.push_back(d);
    }

    std::sort(to_be_removed.begin(), to_be_removed.end());

    digit_set possible_digits(10);  // 0  0  0  0  0  0  0  0  0  0
    digit_set::iterator it;

    it = std::set_difference(digits.begin(), digits.end(), to_be_removed.begin(), to_be_removed.end(),
                             possible_digits.begin());
    possible_digits.resize(it - possible_digits.begin());

    if (possible_digits.empty()) {
        std::cout << "No digits available!" << std::endl;
        throw std::exception();
    }

    return possible_digits;
}