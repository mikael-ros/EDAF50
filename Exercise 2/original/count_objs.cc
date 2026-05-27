#include <iostream>
using std::cout;
using std::endl;


class Foo {
private:
    static int created;
public:
    Foo() {++created;}
};

int Foo::created{0};

void example()
{
    {
        Foo a;
        a.print_count();

        Foo b;
        b.print_count();
    }

    {
        Foo c;
        Foo::print_count();
    }
    Foo::print_count();
}

int main()
{
    example();
}
