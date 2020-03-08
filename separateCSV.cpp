// ======================================================================
// Copyright c <2020.3.8> Hiroki Maruta. All rights reserved.
//
// This source code or any portion thereof must not be  
// reproduced or used in any manner whatsoever.
// ======================================================================

#include <iostream>
#include <fstream>
#include <vector>

// プロトタイプ宣言
std::vector<std::string> split(std::string str, char word);
int readConfigFile(std::ifstream& config_file, std::string& csv_name, int& num, int& skip_num, std::string& cols_name);


int main(int argc, char *argv[]){
    std::ifstream config_file("configure.txt");
    std::ifstream csv_file;
    std::ofstream out_csv[256];
    
	if (config_file.fail()) {
		std::cerr << "Failed to read the config file." << std::endl;
		return -1;
	}

    int csv_num, skip_num;
    std::string cols_name, csv_name;
    std::string line;
    std::vector<std::string> result;

    // 設定ファイルの読み込み
    readConfigFile(config_file, csv_name, csv_num, skip_num, cols_name);

    // CSVファイルの読み込み
    csv_file.open(csv_name);
    if(csv_file.fail()){
        std::cerr << "Failed to read the csv file." << std::endl;
        return -1;
    }

    char filename[256];
    for(int i=0; i<csv_num; i++){
        sprintf(filename, "separated%03d.csv", i);
        out_csv[i].open(filename);
    }
    
    // CSVファイルを１行ずつ読み込んで，","で分割して一定間隔でCSVファイルに保存
    int skip_counter = 0, row_counter = 0;
    while(getline(csv_file, line)){
        if((row_counter > 3)&&(skip_counter != skip_num)) { // スキップするか判定・実行
            skip_counter++;
            continue;
        }

        int i=0;
        int min_col=0, max_col=result.size() / csv_num;

        result = split(line, ',');
        for(int j=0; j<result.size(); j++){
            if(cols_name == "x"){
                if(((j%4) == 2) || ((j%4) == 3)) continue; // time,X軸列だけ出力するためY,Z軸をスキップ
            }else if(cols_name == "y"){
                if(((j%4) == 1) || ((j%4) == 3)) continue; // time,Y軸列だけ出力
            }else if(cols_name == "z"){
                if(((j%4) == 1) || ((j%4) == 2)) continue; // time,Z軸列だけ出力
            }

            if((j>=min_col)&&(j<=max_col)){
                out_csv[i] << result[j] << ",";
                if(max_col==j) {
                    min_col += result.size() / csv_num;
                    max_col += result.size() / csv_num;
                    i++;
                }
            }
        }

        // 改行
        for(int k=0; k<csv_num; k++){
            out_csv[k] << std::endl;
        }
        skip_counter = 0;
        row_counter++;
    }

    // ファイルを閉じる
    config_file.close();
    csv_file.close();
    for(int i=0; i<csv_num; i++){
        out_csv[i].close();
    }

    return 0;
}


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
int readConfigFile(std::ifstream& config_file, std::string& csv_name, int& num, int& skip_num, std::string& cols_name) {
	std::string str;
	std::vector<std::string> result;

	// CSVファイル名の取得
	getline(config_file, str);
	result = split(str, ':');
    csv_name = result[1];
    //std::cout << result[1] << std::endl;

    // 分割するCSVファイル数を取得
	getline(config_file, str);
	result = split(str, ':');
    num = std::stoi(result[1]);
    //std::cout << num << std::endl;

    // 行スキップ数の取得
	getline(config_file, str);
	result = split(str, ':');
    skip_num = std::stoi(result[1]);

    // 抽出列の取得
	getline(config_file, str);
	result = split(str, ':');
    cols_name = result[1];

	return 1;
}