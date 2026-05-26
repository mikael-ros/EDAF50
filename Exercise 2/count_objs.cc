#include <iostream>
using std::cout;
using std::endl;


class Foo {
private:
    static int created;
    static int alive;
public:
    Foo() {++created; ++alive;}
    ~Foo() {--alive;}                                           // Step 2

    static void reset_counts() {                                // Step 2
        created = 0;                                            // Step 2
        alive = 0;                                              // Step 2
    }                                                           // Step 2

    static void print_count() {                                 // Step 1
        cout << "Created Foo objects = " << created << endl;    // Step 1
    }                                                           // Step 1

    static void print_count_ratio() {                           // Step 2
        cout << "Alive Foo objects:" << alive << " / "          // Step 2
        << created << " created" << endl;                       // Step 2
    }                                                           // Step 2
};

int Foo::created{0};
int Foo::alive{0};

void example()
{
    {
        Foo a;
        a.print_count();

        Foo b;
        a.print_count();
    }

    {
        Foo c;
        Foo::print_count();
    }
    Foo::print_count();
}

void example2()                                                 // Step 2
{
    {
        Foo a;
        a.print_count_ratio();                                  // Step 2

        Foo b;
        a.print_count_ratio();                                  // Step 2
    }

    {
        Foo c;
        Foo::print_count_ratio();                               // Step 2
    }
    Foo::print_count_ratio();                                   // Step 2
}

int main()
{
    example();
    Foo::reset_counts();                                        // Step 2
    example2();                                                 // Step 2
}
