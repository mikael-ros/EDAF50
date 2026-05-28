#include "rational.h"

#include <iostream>
using namespace std;

Rational::Rational(long numerator, long denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
    reduce();
};

void Rational::reduce() {
    long common = gcd(numerator, denominator);
    numerator /= common;
    denominator /= common;
}

Rational& Rational::operator+=(const Rational& r) {
    numerator = numerator * r.denominator + r.numerator * denominator;
    denominator = denominator * r.denominator;
    reduce();
    return *this;
};

Rational operator+(const Rational& left, const Rational& right) {
    Rational result = left;
    result += right;
    return result;
};

std::ostream& operator<<(ostream& os, const Rational& r) { // Borrowed straight from solutions
	os << r.numerator;
	if (r.denominator != 1) {
		os << '/' << r.denominator;
	}
	return os;
};

long gcd(long x, long y) {
    long R;

    while ((R = x % y) > 0)  {
        x = y;
        y = R;
    }
    return y;
};