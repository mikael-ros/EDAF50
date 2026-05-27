#include "eyes.h"
#include <iostream>
using std::cout;

void print(eye_colour x)
{
    switch(x) {
        case brown: cout << "brown"; break;
        case blue: cout << "blue"; break;
        case green: cout << "green"; break;
        default: cout << "???"; break;
    }
    cout << " eyes\n";
}
