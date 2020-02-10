// ======================================================================
// Copyright c <2020.2.10> Hiroki Maruta. All rights reserved.
//
// This source code or any portion thereof must not be  
// reproduced or used in any manner whatsoever.
// ======================================================================


#include <iostream>
#include <fstream>

int main(){
    std::ifstream csv_file("/Users/marurun/Downloads/TEST4003 江口.CSV");
    std::string line;

    if(csv_file.fail()){
        std::cerr << "Failure" << std::endl;
        return -1;
    }

    // while (getline(csv_file, line)){
    for(int i=0; i<5; i++){
        getline(csv_file, line);
        std::cout << line << std::endl;

    }

    return 0;
}