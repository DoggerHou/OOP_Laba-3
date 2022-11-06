#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

class Animal 
{
private:
    string name;
public:
    virtual void sound() = 0;
};

class Dog: public Animal 
{
public:
    //Dog() { cout << "Dog()"; }
    void sound() override 
    {
        cout<<"bark-bark\n";
    }  
    void chaseCat() {}
};

class Cat : public Animal 
{
public:
    void sound() override 
    {
        cout << "mew-mew\n";
    }
    void catchMouse() {}
};

int main()
{
    unsigned int Start_Time = clock();
    setlocale(LC_ALL,"rus");
    Animal* storage1[100];
    unsigned int End_Time = clock();
    storage1[0] = new Dog();
    cout <<"\nВремя выполнения программы:"<< End_Time - Start_Time;
}
