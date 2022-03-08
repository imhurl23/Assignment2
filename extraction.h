#ifndef Extraction_H
#define Extraction_H

namespace HRLISA004 {

	//function to read through commend lines and get the width and height of the pgm referenced by imgfile ptr 
	std::tuple<int, int> parseHeaderInfo(std::ifstream & imgfileptr);

	//function to get 
	unsigned char ** getBinaryData(std::ifstream & imgfileptr);
 }
#endif