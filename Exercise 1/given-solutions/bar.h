#ifndef BAR_H
#define BAR_H
#include <string>
#include <iostream>
using std::cout;
using std::endl;

class Bar{
public:
    Bar(const std::string& s) :str{s} {}
    void print() const {cout << "Bar(" << str << ")\n";}
private:
    std::string str;
};

#endif
