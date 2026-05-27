#include "traffic_light.h"
#include <iostream>
using std::cout;

void print(traffic_light x)
{
    switch(x) {
        case red: cout << "red"; break;
        case yellow: cout << "yellow"; break;
        case green: cout << "green"; break;
        default: cout << "???"; break;
    }
    cout << " light\n";
}
