#include "PipeLine.h"



#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/variant.hpp"



#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>







// Реализация TechFunc1
void PipeLine::TechFunc1(int i) {
    int DesiredType[5] = {0, 1, 1, 1, 2};
    auto TypeDesireedTypeOut = MainData[i];
    
    if (DesiredType[i] == 1) {
        TypeDesireedTypeOut = 0;
        InputPos<int>(parametr[i], get<int>(TypeDesireedTypeOut), i);
    } else if(DesiredType[i] == 0) {
        TypeDesireedTypeOut = "";
        InputPos<string>(parametr[i], get<string>(TypeDesireedTypeOut), i);
    } else if(DesiredType[i] == 2) {
        unsigned par = 0;
        TypeDesireedTypeOut = par;
        InputPos<unsigned>(parametr[i], get<unsigned>(TypeDesireedTypeOut), i);
    }
}

// Реализация шаблонной функции (должна остаться в заголовке или здесь с explicit instantiation)
template <typename T> 
T PipeLine::InputPos(string NameOfInput, T DesireedTypeIn, int id) {
    cout << NameOfInput << metadata[id];
    cin >> DesireedTypeIn;
    variant<int, unsigned, string> DesireedTypeInVariant = DesireedTypeIn;
    MainData[id] = DesireedTypeInVariant;
    return DesireedTypeIn;
}

// Явное инстанцирование шаблона для нужных типов
template int PipeLine::InputPos<int>(string, int, int);
template unsigned PipeLine::InputPos<unsigned>(string, unsigned, int);
template string PipeLine::InputPos<string>(string, string, int);

// Реализация публичных методов
void PipeLine::update() {
    cout << "-----------------" << endl;
    cout << "Enetr this number for change parametr." << endl;
    for (int i = 0; i < size(parametr); i++) {
        cout << parametr[i] << i << endl;
    }

    int NumOfPar;
    cout << "Input number of parametr: ";
    cin >> NumOfPar;

    TechFunc1(NumOfPar);
    cout << "-----------------" << endl;
}

void PipeLine::create() {
    cout << "-----------------" << endl;
    cout << "Create a new pipeline." << endl;
    for(size_t i = 0; i < 5; i++) {
        TechFunc1(i);
    }
    cout << "-----------------" << endl;
}

void PipeLine::PrintData() {
    cout << "-----------------" << endl;
    for (int i = 0; i < size(MainData); i++) {
        cout << parametr[i] << metadata[i];
        visit([](const auto& value) {
            cout << value;
        }, MainData[i]);
        cout << endl;
    }
    cout << "-----------------" << endl;
}




template<class Archive>
void PipeLine::serialize(Archive& archive) {
    archive(
        MainData,    // сериализуем основные данные
        parametr,    // сериализуем параметры
        metadata     // сериализуем метаданные
    );
    // Примечание: временные массивы вроде DesiredType не сериализуем
}

template void PipeLine::serialize<cereal::BinaryOutputArchive>(cereal::BinaryOutputArchive&);
template void PipeLine::serialize<cereal::BinaryInputArchive>(cereal::BinaryInputArchive&);





/** 
class PipeLine
{
private:

variant<int, unsigned, string> MainData[5];

string parametr[5] = {"Name: ", "Length: ", "Diameter: ", "Works normally: ", "Age: "};
string metadata[5] = {"", "", "", "(0 - false, 1 - true) ", ""};

void TechFunc1(int i) {
    int DesiredType[5] = {0, 1, 1, 1, 2};
    auto TypeDesireedTypeOut = MainData[i];
    //cout << parametr[i] << endl;
    //visit([](const auto& value) {
    //    cout << value << endl;
    //}, TypeDesireedTypeOut);
    //cout << DesiredType[i] << endl;
    //string TypeDesireedTypeOutString = typeid(TypeDesireedTypeOut).name();
    //cout << TypeDesireedTypeOutString << endl;
    //cout  << TypeDesireedTypeOutString << endl; holds_alternative<int>(TypeDesireedTypeOut)
    if (DesiredType[i] == 1) {
        TypeDesireedTypeOut = 0;
        InputPos<int>(parametr[i], get<int>(TypeDesireedTypeOut), i);
    } else if(DesiredType[i] == 0) {
        TypeDesireedTypeOut = "";
        InputPos<string>(parametr[i], get<string>(TypeDesireedTypeOut), i);
    } else if(DesiredType[i] == 2) {
        unsigned par = 0;
        TypeDesireedTypeOut = par;
        InputPos<unsigned>(parametr[i], get<unsigned>(TypeDesireedTypeOut), i);
    }
}

template <typename T> T InputPos(string NameOfInput, T DesireedTypeIn, int id)
{
    //cout << typeid(DesireedTypeIn).name() << endl;
    cout << NameOfInput << metadata[id];
    cin >> DesireedTypeIn;
    //cout << endl;
    //cout << DesireedTypeIn << endl;
    variant<int, unsigned, string> DesireedTypeInVariant = DesireedTypeIn;
    MainData[id] = DesireedTypeInVariant;
    return DesireedTypeIn;
}

public:
    string name;
    int length;
    int diameter;
    int status;
    unsigned age;
    void update()
    {
        cout << "-----------------" << endl;
        cout << "Enetr this number for change parametr." << endl;
        for (int i = 0; i < size(parametr); i++) {
            cout << parametr[i] << i << endl;
        }

        int NumOfPar;
        cout << "Input number of parametr: ";
        cin >> NumOfPar;

        TechFunc1(NumOfPar);
        cout << "-----------------" << endl;
    }
    void create()
    {
        cout << "-----------------" << endl;
        cout << "Create a new pipeline." << endl;
        for(size_t i=0; i<5; i++) {
            TechFunc1(i);
        }
        cout << "-----------------" << endl;
    }
    void PrintData() {
        cout << "-----------------" << endl;
        for (int i = 0; i < size(MainData); i++) {
            cout << parametr[i] << metadata[i];
            visit([](const auto& value) {
                cout << value;
            }, MainData[i]);
            cout << endl;
        }
        cout << "-----------------" << endl;
    }
};
**/


class PipeLine
{
private:

variant<int, unsigned, string> MainData[5];

string parametr[5] = {"Name: ", "Length: ", "Diameter: ", "Works normally: ", "Age: "};
string metadata[5] = {"", "", "", "(0 - false, 1 - true) ", ""};

void TechFunc1(int i) {
    int DesiredType[5] = {0, 1, 1, 1, 2};
    auto TypeDesireedTypeOut = MainData[i];
    //cout << parametr[i] << endl;
    //visit([](const auto& value) {
    //    cout << value << endl;
    //}, TypeDesireedTypeOut);
    //cout << DesiredType[i] << endl;
    //string TypeDesireedTypeOutString = typeid(TypeDesireedTypeOut).name();
    //cout << TypeDesireedTypeOutString << endl;
    //cout  << TypeDesireedTypeOutString << endl; holds_alternative<int>(TypeDesireedTypeOut)
    if (DesiredType[i] == 1) {
        TypeDesireedTypeOut = 0;
        InputPos<int>(parametr[i], get<int>(TypeDesireedTypeOut), i);
    } else if(DesiredType[i] == 0) {
        TypeDesireedTypeOut = "";
        InputPos<string>(parametr[i], get<string>(TypeDesireedTypeOut), i);
    } else if(DesiredType[i] == 2) {
        unsigned par = 0;
        TypeDesireedTypeOut = par;
        InputPos<unsigned>(parametr[i], get<unsigned>(TypeDesireedTypeOut), i);
    }
}

template <typename T> T InputPos(string NameOfInput, T DesireedTypeIn, int id)
{
    //cout << typeid(DesireedTypeIn).name() << endl;
    cout << NameOfInput << metadata[id];
    cin >> DesireedTypeIn;
    //cout << endl;
    //cout << DesireedTypeIn << endl;
    variant<int, unsigned, string> DesireedTypeInVariant = DesireedTypeIn;
    MainData[id] = DesireedTypeInVariant;
    return DesireedTypeIn;
}

public:
    string name;
    int length;
    int diameter;
    int status;
    unsigned age;
    void update()
    {
        cout << "-----------------" << endl;
        cout << "Enetr this number for change parametr." << endl;
        for (int i = 0; i < size(parametr); i++) {
            cout << parametr[i] << i << endl;
        }

        int NumOfPar;
        cout << "Input number of parametr: ";
        cin >> NumOfPar;

        TechFunc1(NumOfPar);
        cout << "-----------------" << endl;
    }
    void create()
    {
        cout << "-----------------" << endl;
        cout << "Create a new pipeline." << endl;
        for(size_t i=0; i<5; i++) {
            TechFunc1(i);
        }
        cout << "-----------------" << endl;
    }
    void PrintData() {
        cout << "-----------------" << endl;
        for (int i = 0; i < size(MainData); i++) {
            cout << parametr[i] << metadata[i];
            visit([](const auto& value) {
                cout << value;
            }, MainData[i]);
            cout << endl;
        }
        cout << "-----------------" << endl;
    }
};