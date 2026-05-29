#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <utility>
#include <tuple>

std::ostream& remove_tags(std::istream&, std::ostream& out)
{
    // use stream iterators and std::copy_if with a stateful
    // functor that returns false when inside a tag and true otherwise.
    return out;
}

std::pair<std::istringstream, std::string> setup()
{
    std::string raw{"<html><head>Head</head><body><h1>Hej!</h1><p>Testing, testing. A B C</p></body></html>"};
    std::string expected{"HeadHej!Testing, testing. A B C"};
    return {std::istringstream(raw),expected} ;
}

void test_remove_tags()
{
    std::cout << "test_remove_tags:\n";

    std::istringstream input;
    std::string expected;
    std::tie(input,expected) = setup();

    std::ostringstream output;
    remove_tags(input,output);
    std::string actual = output.str();

    if(actual != expected) {
        std::cout << "ERROR: expected: "<< expected << "\n" <<
                     "       got     : "<< actual << std::endl;
    } else {
        std::cout << "OK.\n";
    }
}

// the main program runs tests if not NO_TEST is defined
// compile with -DNO_TEST to get a program that reads from
// stdin and writes to stdout
int main()
{
#ifndef NO_TEST
    test_remove_tags();
#else
    remove_tags(std::cin, std::cout);
#endif
}
