#include <utility>
#include <tuple>
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
struct Counted{
    Counted() {++created; ++alive;}
    Counted(const Counted&) {++created; ++alive;}
    Counted(Counted&&) =default;
    ~Counted() {--alive;}

    static std::pair<int,int> get_counts();
    static void print_counts();

private:
    static int created;
    static int alive;
};

template <typename T>
std::pair<int,int>
Counted<T>::get_counts()
{
    return std::make_pair(alive,created);
}

template<typename T>
int Counted<T>::created{0};

template<typename T>
int Counted<T>::alive{0};

template <typename T>
void
Counted<T>::print_counts()
{
    int alive;
    int created;
    std::tie(alive, created) = Counted<T>::get_counts();
    cout << "alive: " << alive;
    cout << " / " << created << " created\n" ;
}

class Foo : public Counted<Foo>{
public:
    Foo(int i) :x(i) {}
    void print() const {cout << "Foo(" << x << ")\n";}
private:
    int x;
};

void fun(Foo)
{
    cout << "in fun(Foo)\n";
    Foo::print_counts();
}
void example1()
{
    cout << "example1:\n";
    Foo::print_counts();
    {
        Foo a(10);
        Foo::print_counts();

        fun(a);
        cout << "back in example1()\n";
        Foo::print_counts();

        Foo b(20);
        Counted<Foo>::print_counts();

        {
            Foo c(1);
            Foo::print_counts();
        };
        Foo::print_counts();
    }
    Foo::print_counts();
}

class Bar : public Counted<Bar> {
public:
    Bar(const std::string& s) :s(s) {}
    void print() const {cout << "Bar(" << s << ")\n";}
private:
    std::string s;
    
};

void example2()
{
    cout << "example2:\n";
    Bar::print_counts();
    {
        Bar a("a");
    
        Counted<Bar>::print_counts();
        {
            Bar c("c");
            Bar::print_counts();
        };
        Bar::print_counts();
    }
    Bar::print_counts();
}

int main()
{
    example1();
    example2();
}
