#ifndef __CONCOMP__
#define __CONCOMP__
#include <vector>
#include <iostream>
namespace HRLISA004 
{
class ConnectedComponent {
private: 
int numPixels; 
int id; 
std::vector< std::pair<int,int> >  coordinates;


public: 


    ConnectedComponent(); // Default Constructor
		ConnectedComponent(const int row, const int col, std::vector<std::pair<int,int> > const &vec); // Custom Constructor
		ConnectedComponent(int label);
		~ConnectedComponent(); // Destructor
		ConnectedComponent(const ConnectedComponent& comp); // Copy Constructor
		ConnectedComponent(ConnectedComponent && comp); // Move constructor


		ConnectedComponent& operator=(const ConnectedComponent& rhs); // Copy Assignment Operator
		ConnectedComponent& operator=(ConnectedComponent&& rhs); //Move Assignment Operator

		// These are for the unit tests
		int getNumPixels() { return numPixels; }
		int getID() { return id; }
		void setID(int idi) {id = idi;}

		std::pair<int, int> getPixel(int idx); 
        
        // get for coordinates NEED TO DETERMINE CORRECT TYPE ON THIS!!!
        std::vector< std::pair<int,int> >* getCoordinatesPTR();

		void addPixel(std::pair<int,int> pix);
		void printData() const;
};  
}
#endif