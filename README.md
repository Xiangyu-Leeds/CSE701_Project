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
4. Error Handling
Invalid input strings throw std::invalid_argument.
Empty strings are rejected.
5. Edge Cases
Handles carry-over in addition and borrow in subtraction.
Works with very large numbers (thousands of digits).
Properly supports numbers with leading zeros.

Usage:
Constructor:
bigint a;                   // Default constructor: a == 0
bigint b(12345);            // Integer constructor: b == 12345
bigint c("-67890");         // String constructor: c == -67890
bigint d("0000123");        // Leading zeros handled: d == 123

Arithmetic Operators:
bigint a("12345");
bigint b("67890");
// Addition
bigint sum = a + b;         // sum == 80235
// Subtraction
bigint diff = a - b;        // diff == -55545
// Multiplication
bigint prod = a * b;        // prod == 838102050
// Increment and Decrement
a++;                        // a == 12346
b--;                        // b == 67889
// Negation
bigint neg = -a;            // neg == -12346

Comparison:
bigint a("12345");
bigint b("67890");
bool result = a < b        //true
bool result1 = a==b       //false
bool result3 = b>a        //true




How to run tests:

1. Compile the test.cpp:
clang++ -std=c++23 -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow -Wpedantic -o test_program test.cpp
2. Run the Program:
./test_program
