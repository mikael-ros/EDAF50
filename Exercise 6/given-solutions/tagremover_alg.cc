#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <utility>
#include <tuple>

using std::string;

struct TagPredicate {
    bool operator()(char c);
private:
    bool in_tag{false};
};

bool TagPredicate::operator()(char c)
{
    bool res = in_tag;
    if(c == '<') res = in_tag = true;
    else if (in_tag && (c == '>')) in_tag=false;

    return !res;
}

std::ostream& remove_tags(std::istream& in, std::ostream& out)
{
    std::noskipws(in);
    auto iit = std::istream_iterator<char>(in);
    auto oit = std::ostream_iterator<char>(out);
    std::copy_if(iit, std::istream_iterator<char>{}, oit, TagPredicate());
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

int main()
{
#ifndef NO_TEST
    test_remove_tags();
#else
    remove_tags(std::cin, std::cout);
#endif
}
