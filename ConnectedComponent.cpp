  #include "ConnectedComponent.h"

  #define CONCOMP HRLISA004::ConnectedComponent // macro to make referencing the PGMimageProcessor class easier 
		// Default Constructor
        CONCOMP::ConnectedComponent(): numPixels(0), id(-1), coordinates(0) {} 


		// Custom Constructor
		CONCOMP::ConnectedComponent(int label): id(label), numPixels(0),  coordinates(0) {} 

		// Destructor
		CONCOMP::~ConnectedComponent(){} 

		// Copy Constructor
		CONCOMP::ConnectedComponent(const ConnectedComponent& comp): numPixels(comp.numPixels), id(comp.id), coordinates(0) {
			// for loop for coordinates 


			coordinates.begin();
			// std::cout << "begin" << std::endl;
			comp.coordinates.begin();
			// std::cout << "comp" << std::endl;
			// coordinates(comp.coordinates.begin(), comp.coordinates.end());

			
			for (int i = 0; i < comp.coordinates.size(); i++){
					coordinates.push_back(comp.coordinates[i]);
			}

			
	
		}

		// Move constructor
		CONCOMP::ConnectedComponent(ConnectedComponent && comp): numPixels(comp.numPixels), id(comp.id){
			coordinates = std::move(comp.coordinates);

		}

		// Copy Assignment Operator
		CONCOMP& CONCOMP::operator=(const CONCOMP & rhs){
				if(this != &rhs) {
					numPixels = rhs.numPixels; id = rhs.id; 

								
					for (int i = 0; i < rhs.coordinates.size(); i++){
							coordinates.push_back(rhs.coordinates[i]);
					}

				}
				return *this;
		}

		//Move Assignment Operator
		CONCOMP& CONCOMP::operator=(CONCOMP && rhs){
			numPixels = rhs.numPixels; id = rhs.id; 
			coordinates = std::move(rhs.coordinates);
			return *this;
		} 


		/* function to add a pixel represented by an std::pair of coorinates into the vector of pairs representing all component coordinates*/
		void CONCOMP::addPixel(std::pair<int,int> pix){
			coordinates.push_back(pix);
			numPixels++;
			
		}

		/*simply print the data for id and num pixles to the standard console*/
		void CONCOMP::printData() const{
			std::cout << id << ":" << numPixels << std::endl;
		}
		
        
		/*return the pair data for a pixel at a given idx in the vector*/
		std::pair<int, int>  CONCOMP::getPixel(int idx){
			return coordinates[idx];
		}
		

		        
		/*return a pointer to the coordinates data*/
        std::vector< std::pair<int,int> >* CONCOMP::getCoordinatesPTR(){
			return  &coordinates;
		}
