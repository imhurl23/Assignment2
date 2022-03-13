#ifndef Extraction_H
#define Extraction_H

namespace HRLISA004 {

	//function to read through commend lines and get the width and height of the pgm referenced by imgfile ptr 
	unsigned char ** parseHeaderInfo(std::ifstream & imgfileptr);
	std::string writeToFile(unsigned char **);

 }
#endif