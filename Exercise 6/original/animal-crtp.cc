#include <iostream>
using std::cout;
using std::endl;

template <typename Derived>
class Animal {
public:
    Animal(const std::string& name) :name(name) {}
    void speak() const {
        cout << name << " says "
        << static_cast<const Derived*>(this)->get_sound()
        << "!\n";
    }
private:
    std::string name;
};

class Dog : public Animal<Dog> {
public:
    using Animal::Animal;
    std::string get_sound() const { 
        return {"Woof"};
    }
};

class Cat : public Animal<Cat> {
public:
    using Animal::Animal;
    std::string get_sound() const { 
        return {"Meow"};
    }
};

int main()
{
    Dog d{"Fido"};
    Cat c{"Caesar"};

    d.speak();
    c.speak();
}
