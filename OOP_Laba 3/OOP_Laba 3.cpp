#include <iostream>
#include <ctime>
#include <time.h>
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
};

class People : public BaseClass {
private:
    string name = "Human";
    int weight;
    int length;
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
    People(int weigth, int heigth) {
        this->weight = weigth;
        this->length = length;
    }
};

class Metal : public BaseClass {
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
    void MetalNazi() {
        cout << "Nazi\n";
    }
};

class Storage {         //Класс хранилище
private:
    BaseClass** objects;        //массив указателей на указатели типа BaseClass
    int size;                   //размер массива
public:
    Storage(int size) {         //Конструктор(задаем размер при создании)
        this->size = size;
        objects = new BaseClass * [size];
    }
    void SetObject(int index, BaseClass* object) {//помещаем объект
        if (index + 1 > size)
            Resize();
        objects[index] = object;
    }
    BaseClass *GetObjectClass(int index) {      //возвращаем указатель на объект дочернего класса
        return objects[index];
    }
    void DeleteObject(int index) {              //удаляем объект
        delete objects[index];
        for (int i = index + 1; i < size - 1; i++) {//убираем дырки после удаления
            objects[i] = objects[i + 1];
        }
    }

    void Resize() {
        BaseClass** objects2 = new BaseClass * [size * 2];
        for (int i = 0; i < size; ++i)
            objects2[i] = objects[i];
        for (int i = size; i < size * 2; ++i)
            objects2[i] = nullptr;

        delete[] objects;
        objects = objects2;
        size = size * 2;
    }
};

int main()
{
    unsigned int Start_Time = clock();
    setlocale(LC_ALL,"rus");
    unsigned int End_Time = clock();
    srand(time(NULL));
    Storage MyStorage(200);
    //MyStorage.SetObject(0, new Metal);
    //if (dynamic_cast<Metal*>(MyStorage.GetObjectClass(0)))
    //    dynamic_cast<Metal*>(MyStorage.GetObjectClass(0))->MetalNazi();

    for (int i = 0; i < 1000; i++) {
        cout << i;
        MyStorage.SetObject(i, new Metal);
        dynamic_cast<Metal*>(MyStorage.GetObjectClass(i))->MetalNazi();
        
    }
    cout <<"\nВремя выполнения программы:"<< End_Time - Start_Time;
}
