#include <iostream>

using namespace std;

// ромбовидное наследование

class Animal
{
public:
    virtual void sleep() { cout << "Animal sleep" << endl; }
    Animal() { cout << "Animal ctor" << endl; }
    virtual ~Animal() { cout << "~Animal" << endl; }
};

class Dog : public virtual Animal
{
public:
    Dog() { cout << "Dog ctor" << endl; }
    virtual ~Dog() { cout << "~Dog" << endl; }
};

class Bird : public virtual Animal
{
public:
    Bird() { cout << "Bird ctor" << endl; }
    virtual ~Bird() { cout << "~Bird" << endl; }
};

class Mammal
{
public:
    Mammal() { cout << "Mammal ctor" << endl; }
    virtual ~Mammal() { cout << "~Mammal" << endl; }
};

///             |----virtual Animal---|   |---virtual Mammal--|
class DogBird : public Dog, public Bird,  public virtual Mammal
{
public:
    DogBird() { cout << "DogBird ctor" << endl; }
    virtual ~DogBird() { cout << "~DogBird" << endl; }
};

int main()
{
    DogBird confused;
    confused.sleep();
    /// ЗА СОЗДАНИЕ ANIMAL ОТВЕТСТВЕНЕН КЛАСС DOGBIRD!!!
    /// Конструирование: Animal, Mammal, Dog, Bird, Dogbird
    /// Разрушение - в обратном порядке: Dogbird, Bird, Dog, Mammal, Animal

    return 0;
}
