#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    unsigned int x = 6;
    int y = 10;

    float a = x - y; 

    int b = x - y;
    long c = x - y;

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
    cout << "c = " << c << '\n';

    /* When two variables of different size or signedness are used in an
     * expression, one of them is converted.
     * In this case, as all values of unsigned int does not fit in a signed int,
     * in the expression x-y, x is converted to unsigned int. Therefore, the
     * result of x - y is  x-y modulo UINT_MAX, which is 4294967292 (for 32-bit ints)
     *
     * Depending on the type of the variable that is initialized with this value,
     * we get different results:
     *
     * a float can represent that number, so a = 4.29497e+09
     *
     * an int, on the other hand, cannot, so here the unsigned value 
     * of 4294967292 is typically (it is implementation defined)
     * interpreted as -4 when used as a signed int.
     *
     * a long, again can contain the value 4294967292.
     *
     * Note that the compiler may not give warnings for the unsafe conversions.
     * With g++, you must compile with -Wconversion and -Wsign-conversion 
     * to get warnings. -Wall or -Wextra does not enable those warnings.
     */
}
