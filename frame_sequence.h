#ifndef FrameSequence_H
#define FrameSequence_H

namespace HRLISA004 {
class FrameSequence
{
private:
std::vector<unsigned char **> imageSequence; // stores each extracted frame image as a dynamically allocated unsigned char array
int width; 
int height; 
int x1, y1, x2, y2;
setFrameSize(width, height);

public:

FrameSequence(void); // default constructor 
~FrameSequence(); // destructor 
setFrameSize(int width, int height);

}; }
#endif