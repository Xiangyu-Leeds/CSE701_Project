/**
 * @file test.c
 * @brief Comprehensive testing suite for the bigint class.
 *
 * This file contains unit tests, integration tests, edge case tests, 
 * error handling tests, consistency tests, randomizing tests, and stress tests 
 */


#include <iostream>
#include <fstream>
#include <cassert>
#include "bigint.hpp"

/**
 * @brief Logs the result of a test case and tracks passed/failed tests.
 * 
 * @param testName Name of the test case.
 * @param result Boolean indicating if the test passed or failed.
 */
void logTest(const std::string &testName, bool result) {
    static int passed = 0, failed = 0;
    if (result) {
        ++passed;
        std::cout << "[PASSED] " << testName << std::endl;
    } else {
        ++failed;
        std::cerr << "[FAILED] " << testName << std::endl;
    }
    
    std::cout << "Total Passed: " << passed << ", Total Failed: " << failed << std::endl;

}

/**
 * @brief Unit tests for the `bigint` class.
 *
 * Tests the default constructor, integer constructor, string constructor, 
 * and handling of leading zeros in the input.
 */

void Unit_tests() {
    std::cout << "Unit Tests" << std::endl;
    try {
        bigint a;
        logTest("Default Constructor", a == bigint("0"));
    } catch (const std::exception &e) {
        logTest("Default Constructor", false);
        std::cout << "Error: " << e.what() << '\n';
    }

    try {
        bigint b(12345);
        bigint c(-67890);

        logTest("int64_t Constructor Positive one ", b == bigint("12345"));
        logTest("int64_t Constructor Negative one", c == bigint("-67890"));
    } catch (const std::exception &e) {
        logTest("int64_t Constructor", false);
        std::cout << "Error: " << e.what() << '\n';
    }
    try {
        bigint d("12345");
        bigint e("-67890");
        logTest("String Constructor", d == bigint("12345"));
        logTest("String Constructor", e == bigint("-67890"));
    } catch (const std::exception &e) {
        logTest("String Constructor", false);
        std::cout << "Error: " << e.what() << '\n';
    }
    try {
        bigint f("0000123");
        logTest("String Constructor (Zeros)", f == bigint("123"));
    } catch (const std::exception &e) {
        logTest("String Constructor (Leading Zeros)", false);
        std::cout << "Error: " << e.what() << '\n';
    }

 
}
/**
 * @brief Integration tests combining multiple features of the `bigint` class.
 *
 * Tests addition, subtraction, multiplication, comparisons, and increment/decrement operators.
 */

void Integration_tests() {
    std::cout << "Integration Tests" << std::endl;
    try {
        bigint a("12345");
        bigint b("67890");
        bigint c = a + b;
        logTest("Addition", c == bigint("80235"));
    } catch (const std::exception &e) {
        logTest("Addition", false);
        std::cout << "Error: " << e.what() << '\n';
    }

    try {
        bigint a("12345");
        bigint b("67890");
        bigint c = a - b;
        logTest("Subtraction", c == bigint("-55545"));
    } catch (const std::exception &e) {
        logTest("Subtraction", false);
        std::cout << "Error: " << e.what() << '\n';
    }

    try {
        bigint a("12345");
        bigint b("67890");
        bigint c = a * b;
        logTest("Multiplication", c == bigint("838102050"));
    } catch (const std::exception &e) {
        logTest("Multiplication", false);
        std::cout << "Error: " << e.what() << '\n';
    }
    try {
        bigint a("12345");
        bigint b("67890");
        bigint c("12345");
        logTest("Comparison", a < b);
        logTest("Comparison", a == c);
        logTest("Comparison", b > c);
        logTest("Comparison", a != b);
        logTest("Comparison", a <= c);
        logTest("Comparison", b >= c);
    } catch (const std::exception &e) {
        logTest("Comparison", false);
        std::cout << "Error: " << e.what() << '\n';
    }
    try {
        bigint a("12345");
        bigint b = a++;
        bigint c = a--;
        bigint d = ++a;
        bigint e = --a;
        logTest("Increment and Decrement", b == bigint("12345"));
        logTest("Increment and Decrement", c == bigint("12346"));
        logTest("Increment and Decrement", d == bigint("12346"));
        logTest("Increment and Decrement", e == bigint("12345"));
    } catch (const std::exception &e) {
        logTest("Increment and Decrement", false);
        std::cout << "Error: " << e.what() << '\n';
    }

    try {
        bigint a("12345");
        bigint b = -a;
        logTest("Negation", b == bigint("-12345"));
    } catch (const std::exception &e) {
        logTest("Negation", false);
        std::cout << "Error: " << e.what() << '\n';
    }

    try {
        bigint a("12345");
        bigint b("67890");
        bigint c = a + b;
        bigint d = c - a;
        logTest("Addition and Subtraction", d == b);
    } catch (const std::exception &e) {
        logTest("Addition and Subtraction", false);
        std::cout << "Error: " << e.what() << '\n';
    }
}

/**
 * @brief Tests edge cases.
 */
void Edge_cases() {
    std::cout << "Edge Cases" << std::endl;
    try {
        bigint a("9999");
        bigint b("1");
        bigint c = a + b;
        logTest("Addition", c == bigint("10000"));
    } catch (const std::exception &e) {
        logTest("Addition", false);
        std::cout << "Error: " << e.what() << '\n';
    }
}

/**
 * @brief Tests error handling for invalid inputs.
 */
void Error_handling() {
    std::cout << "Error Handling" << std::endl;
    try {
        bigint invalid("abc123");
        logTest("String Constructor (Invalid Characters)", false);
    } catch (const std::invalid_argument &e) {
        logTest("String Constructor (Invalid Characters)", true);
    } 
    try {
        bigint empty("");
        logTest("String Constructor (Empty String)", false);
    } catch (const std::invalid_argument &e) {
        logTest("String Constructor (Empty String)", true);
    }

}

/**
 * @brief Tests consistency between different operations.
 */
void Consistency_tests(){
    std::cout << "Consistency Tests" << std::endl;
    // Addition
    try {
        bigint a("12345");
        bigint b("67890");
        bigint c("8888");
        bigint d = a + b - c;
        bigint e = a - c + b;
        logTest("Consistency Tests", d==e);
    } catch (const std::exception &e) {
        logTest("Consistency Tests", false);
        std::cout << "Error: " << e.what() << '\n';
}
}
/**
 * @brief Generates a random `bigint` with a specified number of digits.
 * @param digits The number of digits for the random bigint.
 * @return A random bigint.
 */
bigint generateRandomBigint(int digits) {
    std::string number;

    if (std::rand() % 2 == 0) {
        number += "-";
    }

    number += std::to_string(std::rand() % 9 + 1);

    for (int i = 1; i < digits; ++i) {
        number += std::to_string(std::rand() % 10);
    }

    return bigint(number);
}

/**
 * @brief Tests random operations on `bigint` for consistency and correctness.
 */

void Randomizing_tests() {
    std::cout << "Randomizing Tests" << std::endl;
    try{
        bigint A = generateRandomBigint(50);
        bigint B = generateRandomBigint(10);
        bigint C = generateRandomBigint(10);
        bigint D = A + B - C;
        bigint E = A - C + B;
        logTest("Randomizing Tests", D == E);
    } catch (const std::exception &e) {
        logTest("Randomizing Tests", false);
        std::cout << "Error: " << e.what() << '\n';
    }

}
/**
 * @brief Stress tests with very large `bigint` values.
 */
void Stress_tests() {
    std::cout << "Stress Tests" << std::endl;
    try {
        bigint a = generateRandomBigint(1000);
        bigint b = generateRandomBigint(1000);
        bigint c = a + b;
        logTest("Stress Tests", c == b + a);
        
    } catch (const std::exception &e) {
        logTest("Stress Tests", false);
        std::cout << "Error: " << e.what() << '\n';
    }
}

/**
 * @brief Main function to run all test cases.
 * @return Returns 0 on successful execution.
 */
int main() {
    Unit_tests();
    Integration_tests();
    Edge_cases();
    Error_handling();
    Consistency_tests();
    Randomizing_tests();
    Stress_tests();
    return 0;
}
