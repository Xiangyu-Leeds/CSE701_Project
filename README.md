# CSE701_Project

BigInt Class Implementation and Testing

Features:
1. BigInt Class
Supports arbitrarily large positive and negative integers.
Handles invalid inputs and leading zeros automatically.
2. Constructors
Default constructor: Initializes the value to 0.
Integer constructor: Accepts a signed 64-bit integer.
String constructor: Accepts a string representation of a number.
3. Operators
Arithmetic: +, -, *, +=, -=, *=
Increment/Decrement: ++, --
Negation: -
Comparison: ==, !=, <, >, <=, >=
Output operator: << for displaying BigInt.



How to run tests:

1. Compile the test.cpp:
clang++ -std=c++23 -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow -Wpedantic -o test_program test.cpp
2. Run the Program:
./test_program
