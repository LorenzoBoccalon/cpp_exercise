//
// Created by LB on 26/09/2021.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<ulong> digit_set;

ulong find_next_smallest(ulong number = 0);

ulong parse_input();

ulong n_digits(const std::string &number_str);

ulong stoi(char c);

digit_set possible_digits(ulong number);

ulong first_digit(const std::string &number_str);

std::string itos(ulong number);

int main() {
    auto in = parse_input();
    auto ins = itos(in);
    auto f = first_digit(ins);
    auto l = n_digits(ins);
    std::cout << "number: " << in << std::endl;
    std::cout << "first digit: " << f << std::endl;
    std::cout << "length: " << l << std::endl;
    auto ds = possible_digits(in);
    for (auto d: ds) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

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
    if (find_next_smallest(126456) == 300000) {
        std::cout << "Test 4: passed" << std::endl;
    } else {
        std::cout << "Test 4: failed" << std::endl;
    }
}

ulong find_next_smallest(ulong number) { // 1234
    ulong next = 0;
//    std::cout << "number: " << number << std::endl;
    // first digits = min possible digits diff from 0
    auto ds = possible_digits(number); // 0 5 6 7 8 9
    auto it = ds.begin();
    auto fd = first_digit(itos(number)); // 1
//    std::cout << "fd: " << fd << std::endl;
    auto new_fd = *it; // 0
    while (it != ds.end() && new_fd < fd) {
        new_fd = *++it;
    }
//    std::cout << "new_fd: " << new_fd << std::endl;

    return next;
}

std::string itos(ulong number) {
    return std::to_string(number);
}

ulong first_digit(const std::string &number_str) {
    auto f = number_str.at(0);
    return stoi(f);
}

ulong parse_input() {
    std::cout << "insert number: ";
    ulong number = 0;
    std::cin >> number;
    return number;
}

ulong n_digits(const std::string &number_str) {
    return number_str.length();
}

ulong stoi(char c) {
    return c - '0';  // convert char to int
}

digit_set possible_digits(ulong number) {
    digit_set digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    digit_set to_be_removed = {};
    std::string number_str = std::to_string(number);
    for (char c: number_str) {
        ulong d = stoi(c);  // convert char to int
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