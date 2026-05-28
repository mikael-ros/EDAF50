#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>


//  Numerator
// -----------
// Denominator

class Rational {
    friend std::ostream& operator<<(std::ostream&, const Rational&);
public:
    Rational(long numerator = 0, long denominator = 1);

    Rational& operator+=(const Rational &r);

private:
    void reduce();
    long numerator; // Top part
    long denominator; // Bottom part
};

Rational operator+(const Rational& left, const Rational& right);

std::ostream& operator<<(std::ostream& os, const Rational& r);

long gcd(long x, long y); // Defined outside because it's more of a utility function


#endif