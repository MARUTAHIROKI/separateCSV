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
int readConfigFile(std::ifstream* config_file) {
	std::string str;
	std::vector<std::string> result;
    std::cout << "1" << std::endl;

	// // 各種パラメータを取得
	getline(*config_file, str);
	result = split(str, ':');
    std::cout << result[1] << std::endl;

    csv_file.open(result[1]);
    if(csv_file.fail()){
        std::cout << "3" << std::endl;
        std::cerr << "Failed to read the csv file." << std::endl;
        return -1;
    }
    getline(csv_file, str);
    std::cout << str << std::endl;

    std::cout << "2" << std::endl;


	// limitx = std::stof(result[1]);
	// getline(config_file, str);
	// result = split(str, '=');
	// result[1].copy(file_name, 256);


	// // Combine path and file name.
	// strcpy(output_csv_file_name, file_name);
	// strcpy(jpeg_file_name, file_name);
	// strcat(path, output_csv_file_name);
	// strcpy(output_csv_temp_dis, output_csv_file_name);
	// strcpy(ubh_file_name, path);
	// strcat(ubh_file_name, ".ubh");
	// strcpy(csv_file_name, path);
	// strcat(csv_file_name, ".csv");
	// strcat(output_csv_file_name, "_result.csv");
	// strcat(output_csv_temp_dis, "_xy.csv");
	// strcat(jpeg_file_name, ".jpg");	

	// // The file open as read only
	// if ((fp = fopen(ubh_file_name, "r")) == 0) {
	// 	std::cout << "Failed to read the UBH file." << std::endl;
	// 	return EXIT_FAILURE;
	// }

	return 1;
}

int main(int argc, char *argv[]){
    std::ifstream config_file("configure.txt");
	if (config_file.fail()) {
		std::cerr << "Failed to read the config file." << std::endl;
		return -1;
	}

    std::string line;
    std::vector<std::string> result;

    readConfigFile(&config_file);

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

    return 0;
}