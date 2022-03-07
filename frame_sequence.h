#ifndef FrameSequence_H
#define FrameSequence_H

class FrameSequence
{
private:
std::vector<unsigned char **> imageSequence;


public:
Matrix(void) {rows = cols = 0; space = NULL; }
Matrix(int r, int c);
Matrix();
int GetRowSize(void){ return rows;}
int GetColSize(void){ return cols;}
double g(int i, int j);
void s(int i, int j, double val);
};
#endif