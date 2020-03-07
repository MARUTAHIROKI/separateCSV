csv:
	g++ -std=c++14 -O2 -Wall separateCSV.cpp -o csv.out

exe:
	g++ -std=c++14 -O2 -Wall separateCSV.cpp -o CSVSeparator.exe -static-libgcc -static-libstdc++