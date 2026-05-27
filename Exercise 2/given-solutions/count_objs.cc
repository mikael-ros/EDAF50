#include <iostream>
using std::cout;
using std::endl;


class Foo {
private:
    static int created;
    static int alive;
public:
    Foo() {++created; ++alive;}
    ~Foo() {--alive;}

    static void print_counts();
};

int Foo::created{0};
int Foo::alive{0};

void Foo::print_counts()
{
    cout << "Alive Foo objects: " <<  alive << " / ";
    cout << created << " created" << endl;
}
void example()
{
    {
        Foo a;
        a.print_counts();

        Foo b;
        b.print_counts();
    }

    {
        Foo c;
        Foo::print_counts();
    }
    Foo::print_counts();
}

int main()
{
    example();
}
