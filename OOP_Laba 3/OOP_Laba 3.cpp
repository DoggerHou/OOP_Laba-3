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
//        cout << "BaseClass()\n";
    }
    virtual ~BaseClass() {
 //       cout << "~BaseClass()\n";
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
//        cout << "People()\n";
        name = People_Names[rand() % 36];
        weight = rand() % 100 + 50;     //вес
        height = rand() % 50 + 150;     //рост
    }
    virtual ~People() {         //деструктор
//        cout << "~People()\n";
    }
    void SetPeopleParam(int weigth, int height) { //конструктор с параметрами
            this->weight = weigth;
            this->height = height;
    }
    
    void ShowParam() {
 //       cout <<"\t\t" << name << "   " << weight << "   " << height << endl;
    }


    virtual void ShowName() override {} //переопределенная функиця Вывода имени
};

class Metal : public BaseClass { //Класс металлы
private:
    string name;
public:
    Metal() {
//        cout << "Metal()\n";
        name = Metal_Names[rand() % 16];
    }
    virtual ~Metal() {
 //       cout << "~Metal()\n";
    }
    virtual void ShowName() override {
//        cout <<"\t\t\t" << name << endl;
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
//        cout << "Matrix()\n";
    }
    virtual ~Matrix() {
        delete FirstMatrix;
        delete SecondMatrix;
        delete AnswerMatrix;
//        cout << "~Matrix()\n";
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
        for (int i = 0; i < matrix_size; i++)
            for (int j = 0; j < matrix_size; j++)
                int k;
                //               cout << setw(8) << AnswerMatrix[i][j];
                //           cout << endl;
                //       }
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
        for (int i = 0; i < size; i++)  //костыль для обработки утечки памяти
            objects[i] = nullptr;
    }
    void SetObject(int index, BaseClass* object) {//помещаем объект
        if (index + 1 > size)
            Resize();
        if(objects[index] == nullptr)           //проверка, если в индексе есть элемент
            objects[index] = object;
        else {
            delete objects[index];
            objects[index] = object;
        }
    }

    BaseClass *GetObjectClass(int index) {      //возвращаем указатель на объект дочернего класса
        return objects[index];
    }

    void DeleteObject(int index) {              //удаляем объект
        if (objects[index] != nullptr) {
            delete objects[index];
            objects[index] = nullptr;
        }
    }
    int GetSize() {
        return size;
    }

};

int main()
{
    int action_amount;
    setlocale(LC_ALL,"rus");
    srand(time(NULL));
    ifstream fin1("Metals.txt");
    for (int i = 0; i < 16; i++) {  //Массив имен металлов
        fin1 >> Metal_Names[i];
    }
    
    ifstream fin2("Names.txt");
    for (int i = 0; i < 36; i++) {  //Массив имен Людей
        fin2 >> People_Names[i];
    }

    Storage MyStorage(1000);
    cout << "Введите количество действий:";
    cin >> action_amount;
    unsigned int Start_Time = clock();
    for (int i = 0; i < action_amount; i++) {
        int random_chose = rand() % 3;
        if (random_chose == 0) {        //случайное удаление
            int random_index = rand() % MyStorage.GetSize();
            MyStorage.DeleteObject(random_index);
        }
        if (random_chose == 1) {       //случайное заполнение
            int random_index = rand() % MyStorage.GetSize();
            int random_class = rand() % 3;
            if (random_class == 0)
                MyStorage.SetObject(random_index, new Metal);
            if (random_class == 1)
                MyStorage.SetObject(random_index, new People);
            if (random_class == 2)
                MyStorage.SetObject(random_index, new Matrix);
        }
        if (random_chose == 2) {    //случайный вызов методов дочерних классов
            int random_index = rand() % MyStorage.GetSize();
            if (dynamic_cast<Metal *>(MyStorage.GetObjectClass(random_index)))//для Metal
                dynamic_cast<Metal *>(MyStorage.GetObjectClass(random_index))->ShowName();

            if (dynamic_cast<People *>(MyStorage.GetObjectClass(random_index))) {//для People
                if (rand() % 2 == 0)
                    dynamic_cast<People*>(MyStorage.GetObjectClass(random_index))->ShowParam();
                else
                    dynamic_cast<People *>(MyStorage.GetObjectClass(random_index))
                    ->SetPeopleParam(rand() % 1000 + 200, rand() % 20 + 10);
            }
            if (dynamic_cast<Matrix*>(MyStorage.GetObjectClass(random_index))) {//для Matrix
                if (rand() % 3 == 0)
                    dynamic_cast<Matrix*>(MyStorage.GetObjectClass(random_index))->SumMatrix();
                else if (rand() % 3 == 1)
                    dynamic_cast<Matrix*>(MyStorage.GetObjectClass(random_index))->MultMatrix();
                else
                    dynamic_cast<Matrix*>(MyStorage.GetObjectClass(random_index))->PrintAnswer();
            }
        }
    }
    unsigned int End_Time = clock();
    cout <<"\nВремя выполнения программы:"<< End_Time - Start_Time;
}
