#pragma once
#include <iostream>
#include <variant>
#include <string>
#include <array>

using namespace std;

class ObjectTemplate {
private:
    //string parametr[5] = {"Name: ", "Length: ", "Diameter: ", "Works normally: ", "Age: "};
    //string metadata[5] = {"", "", "", "(0 - false, 1 - true) ", ""};
    //int DesiredType[5] = {0, 1, 1, 1, 2};
    string parametr[5];
    string metadata[5];
    int DesiredType[5];
    void TechFunc1(int i);
    
    template <typename T> 
    T InputPos(string NameOfInput, T DesireedTypeIn, int id);

    template <typename T> 
    T DetectedInput(T& value, int up, int down);

public:
    ObjectTemplate();
    ObjectTemplate(string parametr_[5], string metadata_[5], int DesiredType_[5]);
    ~ObjectTemplate();
    variant<int, unsigned, string> MainData[5];
    string name;
    int length;
    int diameter;
    int status;
    unsigned age;
    
    void update();
    void create();
    void PrintData();
    template<class Archive>
    void serialize(Archive& archive);
};