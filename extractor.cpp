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
	std::tuple<int, int> dims = HRLISA004::parseHeaderInfo(imgfile);
	std::cout <<  std::get<0>(dims) << "," <<  std::get<1>(dims) << std::endl;

	

	return 0;}


 	unsigned char ** HRLISA004::parseHeaderInfo(std::ifstream  & imgfileptr){
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
	

	unsigned char ** img = new unsigned char* [height];
	char * buffer = new char [width*height];
	imgfileptr.read((char *)buffer, width*height);
	// std::cout << &buffer[0][0] << std::endl;


	for (int row = 0; row < height; row++){
		img[row] = new unsigned char [width];
		for (int col = 0; col < width; col++ ){
			int place = row * width + col; 
			img[row][col] = buffer[place];	
		}
	}
	
	return img;
}




