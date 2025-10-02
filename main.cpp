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

#include <stdexcept>





/**
template <typename T> 
bool DetectedInput(T value, string type) {
	switch (cmnd) {
		case 1:
			
		default:
			
	}
}

template <typename T> 
T DetectedInput(const T& value) {
    cin << value;
    if (value.fail()) {
    	cin.clear();
    	cout << "input error. Try again.";
	throw invalid_argument("Invalid argument. Try again.");
    } else {
	return value;
    }
}**/
template <typename T>
T DetectedInput(T& value, int up, int down) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cout << "input error. Try again." << endl;
        throw invalid_argument("Invalid argument. Try again.");
    } else if (up < value || down > value) {
	cout << "input error. Try again." << endl;
	throw invalid_argument("Invalid argument. Try again.");
    }
    return value;
}


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
        //cin >> DesiredNum;
    	try {
    		int DesiredNum = DetectedInput<int>(DesiredNum, 0, 0);
    	} catch (const exception& e) {
		return NamesOfFilesStructure;
    	}
        if (DesiredNum == 0) {
	    try {
            	PipeLine NewPipeLine;
            	NewPipeLine.create();
	    	NewPipeLine.PrintData();
            	string FileName = "Data"+to_string(NamesOfFiles.size())+".bin";
            	SavePipeLine(NewPipeLine, FileName);
            	NamesOfFilesStructure.NamesOfFiles.push_back(FileName);
            	return NamesOfFilesStructure;
            } catch (const exception& e) {
		return NamesOfFilesStructure;
	    }
        } else {}
    }
    for (int i = 1; i < NamesOfFiles.size()+1; i++) {
        PipeLine pipeline;
        try {
            ifstream is(NamesOfFiles[i-1], ios::binary);
            cereal::BinaryInputArchive archive(is);
            archive(pipeline);
        } catch (const exception& e) {
            cerr << "Error -- " << endl;
        }
        CopiesOfClass[i-1] = pipeline;
        visit([](const auto& value) {
            cout << value;
        }, pipeline.MainData[0]);
        cout << ": " << i << endl;
    }
    int DesiredNum;
    cout << "[Desired number, Exit - Ctrl+C, Create a new - 0]: " << endl;
    //cin >> DesiredNum;
    try {
    	int DesiredNum = DetectedInput<int>(DesiredNum, 0, 0);
    } catch (const exception& e) {
	return NamesOfFilesStructure;
    }
    if (DesiredNum == 0) {
	try {
        	PipeLine NewPipeLine;
        	NewPipeLine.create();
		NewPipeLine.PrintData();
        	string FileName = "Data"+to_string(NamesOfFiles.size())+".bin";
        	SavePipeLine(NewPipeLine, FileName);
        	NamesOfFilesStructure.NamesOfFiles.push_back(FileName);
        	return NamesOfFilesStructure;
        } catch (const exception& e) {
		return NamesOfFilesStructure;
	}
    } else {
       DesiredNum--;
    }
    CopiesOfClass[DesiredNum].PrintData();
    cout << "[Update - 0, Delete - 1, Pass - 2, Exit - Ctrl+C]: ";
    int cmnd;
    //cin >> cmnd;
    try {
    	int cmnd = DetectedInput<int>(cmnd, 2, 0);
    } catch (const exception& e) {
	return NamesOfFilesStructure;
    }
    PipeLine pipeline;
    string FileName = "Data"+to_string(DesiredNum)+".bin";
    switch (cmnd) {
        case 0:
            pipeline = CopiesOfClass[DesiredNum];
            pipeline.update();
            CopiesOfClass[DesiredNum] = pipeline;
	    SavePipeLine(pipeline, FileName);
	    pipeline.PrintData();
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
	FilesData Data;
	{
        std::ifstream is("PipesData.bin", std::ios::binary);
        cereal::BinaryInputArchive input_archive(is);
        input_archive(Data);
	}
	//for (string i: Data.NamesOfFiles) {
    	//	std::cout << i << ' ';
	//}
	Data = MainMenu(Data);
	SavePipeLine(Data, "PipesData.bin");
}