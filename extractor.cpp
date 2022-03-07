#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include "frame_sequence.h"

int main(int argc, char *argv[]){
	std::string filename;
	if (argc < 2) {filename << argv[1]; }
	 
	for (int i = 0; i < argc; i++){
		std::cout << argv[i] << std::endl;
	}


	ifstream myfile(filename, ios::binary); // open file in binary mode
	return 0;
}