#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

class BaseClass {        //базовый абстрактный класс Материалы
public:
    BaseClass() {
        cout << "BaseClass()\n";
    }
    virtual ~BaseClass() {
        cout << "~BaseClass()\n";
    }
    virtual void ShowName() = 0;
    virtual bool isA(const string& who) {
        return (who == "BaseClass");
    }
};

class People : public BaseClass {
private:
    string name = "Chelovek";
public:
    People() {
        cout << "People()\n";
    }
    virtual ~People() {
        cout << "~People()\n";
    }
    virtual void ShowName() override {
        cout << name;
    }
    virtual bool isA(const string& who) override {
        return (who == "People") || (who == "BaseClass");
    }
};

class Metal:public BaseClass {
private:
    string name = "Iron";
public:
    Metal() {
        cout << "Metal()\n";
    }
    virtual ~Metal() {
        cout << "~Metal()\n";
    }
    virtual void ShowName() override {
        cout << name;
    }
    virtual bool isA(const string& who) override {
        return (who == "Metal") || (who == "BaseClass");
    }
};

class Storage {         //Класс хранилище
private:
    BaseClass** objects;        //массив указателей на указатели типа BaseClass
    int size;                   //размер массива
public:
    Storage(int size) {         //Конструктор(задаем размер при создании
        this->size = size;
        objects = new BaseClass * [size];
    }
    void SetObject(int index, BaseClass* object) {//помещаем объект
        objects[index] = object;
    }
    BaseClass &GetObjectClass(int index) {      //возвращаем объект дочернего класса
        return *objects[index];
    }
    void DeleteObject(int index) {              //удаляем объект
        delete objects[index];
    }
};

int main()
{
    unsigned int Start_Time = clock();
    setlocale(LC_ALL,"rus");
    unsigned int End_Time = clock();
    Storage MyStorage(228);
    for (int i = 0; i < 100; i++) {
        MyStorage.SetObject(i, new People);
        MyStorage.DeleteObject(i);
    }
    cout <<"\nВремя выполнения программы:"<< End_Time - Start_Time;
}
