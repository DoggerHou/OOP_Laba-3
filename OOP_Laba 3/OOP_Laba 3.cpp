#include <iostream>
#include <ctime>
#include <time.h>
#include <Windows.h>
#include <fstream>
#include <iomanip>
using namespace std;

string Metal_Names[16];
string People_Names[36];
class BaseClass {        //базовый абстрактный класс 
public:
    BaseClass() {
        cout << "BaseClass()\n";
    }
    virtual ~BaseClass() {
        cout << "~BaseClass()\n";
    }
    virtual void ShowName() = 0;
};

class People : public BaseClass {//класс Люди
private:
    string name;                //имя человека
    int weight;                 //Вес человека
    int height;                 //Рост человека
public:     
    People() {
        cout << "People()\n";
        name = People_Names[rand() % 36];
        weight = rand() % 100 + 50;     //вес
        height = rand() % 50 + 150;     //рост
    }
    void SetPeopleParam(int weigth, int height) { //конструктор с параметрами
            this->weight = weigth;
            this->height = height;
    }
    virtual ~People() {
        cout << "~People()\n";
    }
    virtual void ShowName() override {//переопределенная функиця Вывода имени
        cout << name<<endl;
    }
    void ShowParam() {
        cout << name << "   " << weight << "   " << height << endl;
    }
};

class Metal : public BaseClass { //Класс металлы
private:
    string name;
public:
    Metal() {
        cout << "Metal()\n";
        name = Metal_Names[rand() % 16];
    }
    virtual ~Metal() {
        cout << "~Metal()\n";
    }
    virtual void ShowName() override {
        cout << name<<endl;
    }
};

class Matrix : public BaseClass {
private:
    int** FirstMatrix;
    int** SecondMatrix;
    int** AnswerMatrix;
    int matrix_size;
public:
    Matrix() {
        matrix_size = rand() % 6 + 2;//задаем размер квадратной матрицы
        FirstMatrix = new int*[matrix_size];       //объявляем размеры (от 2 до 7)
        SecondMatrix = new int* [matrix_size];
        AnswerMatrix = new int* [matrix_size];
        for (int i = 0; i < matrix_size; i++) {
            FirstMatrix[i] = new int[matrix_size];
            SecondMatrix[i] = new int[matrix_size];
            AnswerMatrix[i] = new int[matrix_size];
        }
        for (int i = 0; i < matrix_size; i++) 
            for (int j = 0; j < matrix_size; j++) {
                FirstMatrix[i][j] = rand()%100;
                SecondMatrix[i][j] = rand()%100;
                AnswerMatrix[i][j] = NULL;
            }
    }
    ~Matrix() {
        delete FirstMatrix;
        delete SecondMatrix;
        delete AnswerMatrix;
    }
    void SumMatrix() {
        for (int i = 0; i < matrix_size; i++)
            for (int j = 0; j < matrix_size; j++)
                AnswerMatrix[i][j] = FirstMatrix[i][j] + SecondMatrix[i][j];
    }
    void MultMatrix() {
        for (int i = 0; i < matrix_size; i++)
            for (int j = 0; j < matrix_size; j++) {
                AnswerMatrix[i][j] = NULL;
                for (int k = 0; k < matrix_size; k++)
                    AnswerMatrix[i][j] += FirstMatrix[i][k] * SecondMatrix[k][j];
            }
    }
    void PrintAnswer() {
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++)
                cout << setw(8) << AnswerMatrix[i][j];
            cout << endl;
        }
    }
    virtual void ShowName() override {}
};

class Storage {         //Класс хранилище
private:
    BaseClass** objects;        //массив указателей на указатели типа BaseClass
    int size;                   //размер массива
    void Resize() {     //Увеличиваем размер массива, если вышли за его пределы
        BaseClass** objects2 = new BaseClass * [size * 2];
        for (int i = 0; i < size; ++i)
            objects2[i] = objects[i];
        for (int i = size; i < size * 2; ++i)
            objects2[i] = nullptr;

        delete[] objects;
        objects = objects2;
        size = size * 2;
    }
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

};

int main()
{
    
    unsigned int Start_Time = clock();
    setlocale(LC_ALL,"rus");
    srand(time(NULL));
    ifstream f1in("Metals.txt");
    for (int i = 0; i < 16; i++) {  //Массив имен металлов
        f1in >> Metal_Names[i];
    }
    
    ifstream fin2("Names.txt");
    for (int i = 0; i < 36; i++) {  //Массив имен Людей
        fin2 >> People_Names[i];
    }
    Storage MyStorage(200);

    /**for (int i = 0; i < 1000; i++) {
        cout << i;
        if(rand()%2==1)
            MyStorage.SetObject(i, new Metal);
        else
            MyStorage.SetObject(i, new People);
        if (dynamic_cast<Metal*>(MyStorage.GetObjectClass(i)))
            dynamic_cast<Metal*>(MyStorage.GetObjectClass(i))->ShowName();
        else
            dynamic_cast<People*>(MyStorage.GetObjectClass(i))->ShowParam();
    }
    */

    Storage MyStorage2(4);
    MyStorage2.SetObject(0, new Matrix);;
    dynamic_cast<Matrix*>(MyStorage2.GetObjectClass(0))->MultMatrix();
    dynamic_cast<Matrix*>(MyStorage2.GetObjectClass(0))->PrintAnswer();


    unsigned int End_Time = clock();
    cout <<"\nВремя выполнения программы:"<< End_Time - Start_Time;
}
