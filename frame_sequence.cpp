
#include " frame_sequence.h"



std::vector<unsigned char **> imageSequence; // stores each extracted frame image as a dynamically allocated unsigned char array
int width; 
int height; 
int x1, y1, x2, y2;



HRLISA004::FrameSequence::FrameSequence(void){}
HRLISA004::FrameSequence::~FrameSequence(){
	if(this->imageSequence != nullptr) // We have to make sure we're not trying to relase a bit of memory that doesn't exist.
	{
		
	}}
HRLISA004::FrameSequence::setFrameSize(int width, int height);
HRLISA004::FrameSequence::getWidth(){ return width;}
HRLISA004::FrameSequence::getHeight(return height;);
HRLISA004::FrameSequence::getCoords(std::vector<int> coords{ x1, y1, x2,y2 };);
HRLISA004::FrameSequence::writeFrame(unsigned char **);
HRLISA004::FrameSequence::writeFrames();
