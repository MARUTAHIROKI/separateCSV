// ======================================================================
// Copyright c <2020.2.10> Hiroki Maruta. All rights reserved.
//
// This source code or any portion thereof must not be  
// reproduced or used in any manner whatsoever.
// ======================================================================


#include <iostream>
#include <fstream>
#include <vector>

// Divide text
std::vector<std::string> split(std::string str, char del) {
	int first = 0;
	int last = (int)str.find_first_of(del);

	std::vector<std::string> result;

	while (first < str.size()) {
		std::string subStr(str, first, last - first);

		result.push_back(subStr);

		first = last + 1;
		last = (int)str.find_first_of(del, first);

		if (last == std::string::npos) {
			last = (int)str.size();
		}
	}
	return result;
}

int main(){
    std::ifstream csv_file("/Users/marurun/Downloads/TEST4003 江口.CSV");
    std::string line;
    std::vector<std::string> result;

    if(csv_file.fail()){
        std::cerr << "Failure to open CSV file" << std::endl;
        return -1;
    }

    // while (getline(csv_file, line)){
    for(int i=0; i<1; i++){
        getline(csv_file, line);
        result = split(line, ',');
        for(int j=0; j<result.size(); j++) std::cout << j << ", " << result[j] << std::endl;
    }

    return 0;
}