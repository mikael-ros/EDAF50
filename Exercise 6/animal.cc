#include <iostream>
using std::cout;
using std::endl;

class Animal {
public:
    Animal(const std::string& name) :name(name) {}
    virtual std::string get_sound() const =0;
    void speak() const {
        cout << name << " says "
        << get_sound()
        << "!\n";
    }
private:
    std::string name;
};

class Dog : public Animal {
public:
    using Animal::Animal;
    std::string get_sound() const { 
        return {"Woof"};
    }
};

class Cat : public Animal {
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
