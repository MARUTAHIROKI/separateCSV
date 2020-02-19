// ======================================================================
// Copyright c <2020.2.10> Hiroki Maruta. All rights reserved.
//
// This source code or any portion thereof must not be  
// reproduced or used in any manner whatsoever.
// ======================================================================

#include <iostream>
#include <fstream>
#include <vector>

std::ifstream csv_file;

// Divide text
std::vector<std::string> split(std::string str, char word){
	int first = 0;
	int last = (int)str.find_first_of(word);

	std::vector<std::string> result;

	while(first < str.size()) {
		std::string subStr(str, first, last - first);

		result.push_back(subStr);

		first = last + 1;
		last = (int)str.find_first_of(word, first);

		if(last == std::string::npos) {
			last = (int)str.size();
		}
	}
	return result;
}

// configure.txtで条件を設定
int readConfigFile(std::ifstream* config_file, int *num) {
	std::string str;
	std::vector<std::string> result;

	// CSVファイル名の取得
	getline(*config_file, str);
	result = split(str, ':');
    //std::cout << result[1] << std::endl;

    csv_file.open(result[1]);
    if(csv_file.fail()){
        std::cerr << "Failed to read the csv file." << std::endl;
        return -1;
    }

    // 分割するCSVファイル数を取得
	getline(*config_file, str);
	result = split(str, ':');
    *num = std::stoi(result[1]);
    //std::cout << *num << std::endl;

	return 1;
}

int main(int argc, char *argv[]){
    std::ifstream config_file("configure.txt");
	if (config_file.fail()) {
		std::cerr << "Failed to read the config file." << std::endl;
		return -1;
	}

    int csv_num;
    std::string line;
    std::vector<std::string> result;

    readConfigFile(&config_file, &csv_num);

    // while (getline(csv_file, line)){
    for(int i=0; i<5; i++){
        getline(csv_file, line);
        result = split(line, ',');
        for(int j=0; j<result.size(); j++){
            if((j>=atoi(argv[1]))&&(j<=atoi(argv[2]))){
                std::cout << j << ", " << result[j] << std::endl;
            }
        }
    }

    config_file.close();
    csv_file.close();

    return 0;
}