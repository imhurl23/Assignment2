#include <cstdlib>
#include <tuple>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include "frame_sequence.h"
#include "extraction.h"



int main(int argc, char *argv[]){
	std::string filename;
	if (argc > 2) {filename = argv[1]; }
	else {
		filename = "examples/larger_image.pgm";
	}
	

	std::ifstream imgfile(filename, std::ios::binary); // open file in binary mode
	if (!imgfile) {
	std::cerr << "File open failed!" << std::endl;
	} 

	HRLISA004::parseHeaderInfo(imgfile);
	
	

	return 0;}


 std::tuple<int, int> HRLISA004::parseHeaderInfo(std::ifstream & imgfileptr){
	char array[100];
	std::string str;

	getline(imgfileptr,str);
	if ( str!= "P5") {
		std::cerr << "File format incorrect" << std::endl;
	}
	while (getline(imgfileptr,str)){
		if (str[0] != '#'){
			std::cout << "BREAK" << std::endl;
			break;
		}
		std::cout << "The next line is " << str << std::endl;
	}
	int width, height; 
	std::istringstream iss(str);
	iss >> width >> std::ws; 
	iss >> height >> std::ws;
	std::cout << width <<  "," << height << std::endl;
	return std::make_tuple(width,height);

}



