#include "narrow_cast.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
using std::cout;
using std::endl;


int main()
{
    int x{42};
    int y{257};
    char a;
    
    try {
        a = narrow_cast<char>(x);
    } catch(std::runtime_error&){
        assert(!"Failure: unexpected exception thrown");
    }
    assert(a == 42);
    cout << "narrow_cast of small int succeeded\n";

    try {
        (void) narrow_cast<char>(y);
        assert(!"Failure: exception was not thrown");
    } catch(std::runtime_error&){
        cout << "narrow_cast of big int succeeded\n";
    }
}
