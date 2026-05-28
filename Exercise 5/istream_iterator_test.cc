#include <iostream>
#include <sstream>
#include <iterator>
#include <iomanip>

void example()
{
    using std::cout;
    using std::endl;
    using std::istream_iterator;

    std::stringstream ss{"1 17 kalle 2 nisse 3 pelle\n"};
    istream_iterator<int> iit(ss);
    istream_iterator<int> iit_end{};

    while(iit != iit_end) { cout << *iit++ << endl; }

    cout << std::boolalpha << "ss.eof(): " << ss.eof() << endl;
}

int main()
{
    example();
}
