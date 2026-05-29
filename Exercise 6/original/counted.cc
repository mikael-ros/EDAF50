#include <utility>
#include <tuple>
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
void print_counts()
{
    int alive;
    int created;
    std::tie(alive, created) = T::get_counts();
    cout << "alive: " << alive;
    cout << " / " << created << " created\n" ;
}

class Foo{
public:
    Foo(int i) :x(i) {++created; ++alive;}
    Foo(const Foo&) {++created; ++alive;}
    Foo(Foo&&) =default;
    ~Foo() {--alive;}
    void print() const {cout << "Foo(" << x << ")\n";}
    static std::pair<int,int> get_counts();

private:
    int x;
    static int created;
    static int alive;
};

int Foo::created{0};
int Foo::alive{0};

std::pair<int,int> Foo::get_counts()
{
    return std::make_pair(alive,created);
}

void fun(Foo)
{
    cout << "in fun(Foo)\n";
    print_counts<Foo>();
}
void example1()
{
    cout << "example1:\n";
    print_counts<Foo>();
    {
        Foo a(10);
        print_counts<Foo>();

        fun(a);
        cout << "back in example1()\n";
        print_counts<Foo>();

        Foo b(20);
        print_counts<Foo>();

        {
            Foo c(1);
            print_counts<Foo>();
        };
        print_counts<Foo>();
    }
    print_counts<Foo>();
}

class Bar {
public:
    Bar(const std::string& s) :s(s) {++created; ++alive;}
    Bar(const Bar&) {++created; ++alive;}
    Bar(Bar&&) =default;
    ~Bar() {--alive;}
    void print() const {cout << "Bar(" << s << ")\n";}
    static std::pair<int,int> get_counts();

private:
    static int created;
    static int alive;
    std::string s;
};

int Bar::created{0};
int Bar::alive{0};

std::pair<int,int> Bar::get_counts()
{
    return std::make_pair(alive,created);
}

void example2()
{
    cout << "example2:\n";
    print_counts<Bar>();
    {
        Bar a("a");
    
        print_counts<Bar>();
        {
            Bar c("c");
            print_counts<Bar>();
        };
        print_counts<Bar>();
    }
    print_counts<Bar>();
}

int main()
{
    example1();
    example2();
}
