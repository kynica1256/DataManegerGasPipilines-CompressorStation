#include "PipeLine.h"
#include <fstream>
#include <iostream>


// Вариант 2: Если структура другая
#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/variant.hpp"

using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <type_traits>

#include <variant>
#include <vector>


#include <cstdio>
#include <cstdlib>

#include <string> 












struct FilesData {
    vector<string> NamesOfFiles;
    // Функция для сериализации
    template <class Archive>
    void serialize(Archive& ar) {
        ar(NamesOfFiles); // Передаем массив и другие члены
    }
};



template <typename T> 
void SavePipeLine(const T& pl, const string& filename) {
    ofstream os(filename, ios::binary);
    cereal::BinaryOutputArchive archive(os);
    archive(pl);
}

FilesData MainMenu(FilesData NamesOfFilesStructure) {
    vector<string> NamesOfFiles = NamesOfFilesStructure.NamesOfFiles;
    PipeLine CopiesOfClass[NamesOfFiles.size()];
    if (NamesOfFiles.size() == 0) {
        int DesiredNum;
        cout << "[Exit - Ctrl+C, Create a new - 0]: " << endl;
        cin >> DesiredNum;
        if (DesiredNum == 0) {
            PipeLine NewPipeLine;
            NewPipeLine.create();
            string FileName = "Data"+to_string(NamesOfFiles.size())+".bin";
            SavePipeLine(NewPipeLine, FileName);
            NamesOfFilesStructure.NamesOfFiles.push_back(FileName);
            return NamesOfFilesStructure;
        } else {}
    }
    for (int i = 1; i < NamesOfFiles.size(); i++) {
        PipeLine pipeline;
        try {
            ifstream is(NamesOfFiles[i], ios::binary);
            cereal::BinaryInputArchive archive(is);
            archive(pipeline);
        } catch (const exception& e) {
            cerr << "Error -- " << endl;
            //pipeline = FilesData();
        }
        CopiesOfClass[i] = pipeline;
        visit([](const auto& value) {
            cout << value;
        }, pipeline.MainData[0]);
        cout << ": " << i << endl;
    }
    int DesiredNum;
    cout << "[Desired number, Exit - Ctrl+C, Create a new - 0]: " << endl;
    cin >> DesiredNum;
    if (DesiredNum == 0) {
        PipeLine NewPipeLine;
        NewPipeLine.create();
        string FileName = "Data"+to_string(NamesOfFiles.size())+".bin";
        SavePipeLine(NewPipeLine, FileName);
        NamesOfFilesStructure.NamesOfFiles.push_back(FileName);
        return NamesOfFilesStructure;
    } else {
       DesiredNum--;
    }
    CopiesOfClass[DesiredNum].PrintData();
    cout << "[Update - 0, Delete - 1, Pass - 2, Exit - Ctrl+C]: ";
    int cmnd;
    cin >> cmnd;
    switch (cmnd) {
        case 0:
            CopiesOfClass[DesiredNum].update();
            break;
        case 1:
            if( remove( NamesOfFiles[DesiredNum].c_str() ) != 0 ) {
                std::cout << "Uninstallation error, try restarting the program. If the problem persists, please contact technical support." << endl;
            } else {
                std::cout << "Successfully deleted." << endl;
                NamesOfFilesStructure.NamesOfFiles.erase(NamesOfFilesStructure.NamesOfFiles.begin() + DesiredNum);
            }
            break;
        default:
            cout << "";
    }
    return NamesOfFilesStructure;
}



int main() {

}