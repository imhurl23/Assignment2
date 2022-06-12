#define CATCH_CONFIG_MAIN  // This tells catch to provide a main() function. Only do this in one cpp file
#include "catch.hpp"
#include "PGMimageProcessor.cpp"


#define PGMIMG HRLISA004::PGMimageProcessor // macro to make referencing the PGMimageProcessor class easier 
#define CONCOMP HRLISA004::ConnectedComponent // macro to make referencing the ConnectedComponent class easier 

// Tests for the ConnectedComponent Class

TEST_CASE ("ConnectedComponent class Unit Tests")
{
	SECTION (" Default Constructor")
	{

		CONCOMP component;
		std::cout << "default" << std::endl;
		REQUIRE(component.getNumPixels() == 0);
		REQUIRE(component.getID() == -1);
		// REQUIRE((*component.getCoordinatesPTR()).size() == 0);

	}


	SECTION ("Custom Constructor")
	{
		std::cout << "custom" << std::endl;
		CONCOMP component(22);

		REQUIRE(component.getNumPixels() == 0);
		REQUIRE(component.getID() == 22);
	
	}



	SECTION ("Copy Constructor")
	{
		std::cout << "copy" << std::endl;
		CONCOMP component1(1);
		component1.addPixel(std::make_pair(100,100));
		CONCOMP component2(component1);// Call the copy constructor


		REQUIRE(component1.getNumPixels() == component2.getNumPixels());
		component1.addPixel(std::make_pair(200,200)); 
		REQUIRE(component1.getNumPixels() != component2.getNumPixels());


		REQUIRE(component1.getID() == component2.getID()); // Make sure that they are NOT pointing to the same bit of memory
		REQUIRE(component1.getCoordinatesPTR() != component2.getCoordinatesPTR() ); // But make sure they have the same value
	}

	SECTION ("Move Constructor")
	{


		CONCOMP component1(1); 
		component1.addPixel(std::make_pair(100,100));
		component1.addPixel(std::make_pair(200,200));

		
		
		CONCOMP component2(std::move(component1));

		// Test for component1
		REQUIRE((*component1.getCoordinatesPTR()).size() == 0); 

		// Test for component2
		REQUIRE(component2.getID() == 1);
		REQUIRE(component2.getPixel(0) == (std::make_pair<int,int>(100,100)));
		REQUIRE((*component1.getCoordinatesPTR()).size()  == 0); // check that the vector field was stripped
	}

	SECTION ("Copy Assignment Operator")
	{
		CONCOMP c1(5);
		CONCOMP c2;

		c1 = c2; // Call the copy assignment operator 


		REQUIRE(c1.getNumPixels() == c2.getNumPixels());
		c1.addPixel(std::make_pair(200,200)); 
		REQUIRE(c1.getNumPixels() != c2.getNumPixels());


		REQUIRE(c1.getID() == c2.getID()); 
		REQUIRE(c1.getCoordinatesPTR() != c2.getCoordinatesPTR() ); // Make sure that they are NOT pointing to the same bit of memory

	}



	SECTION ("Move Assignment Operator")
	{
		CONCOMP c1(5);
		c1.addPixel(std::make_pair<int, int> (100,100));
		c1.addPixel(std::make_pair<int, int> (200,200));
		CONCOMP c2;


		c2 = std::move(c1); // Call the move assignment operator


		
		// Test for component1
		REQUIRE((*c1.getCoordinatesPTR()).size() == 0); 

		// Test for component2
		REQUIRE(c2.getID() == 5);
		REQUIRE(c2.getPixel(1) == (std::make_pair<int,int>(200,200)));
		REQUIRE((*c1.getCoordinatesPTR()).size()  == 0); // check that the vector field was stripped


	}

	SECTION ("Add Pixel"){
		CONCOMP c1(1);
		REQUIRE (c1.getNumPixels() == 0 ); 
		for (int i = 0; i < 10; i ++){
			c1.addPixel(std::make_pair<int,int>(6,6));
		}
		REQUIRE (c1.getNumPixels() == 10 ); 
		REQUIRE (c1.getPixel(5) == (std::make_pair<int,int>(6,6)) ); 
	}


		SECTION ("Get Pixel"){
		CONCOMP c1(1);
		c1.addPixel(std::make_pair<int,int>(90,9));
		REQUIRE (c1.getNumPixels() == 1 ); 
		REQUIRE (c1.getPixel(0) == (std::make_pair<int,int>(90,9)) ); 
	}


	SECTION ("Get Coordinates PTR"){
		CONCOMP c1(1);
		std::vector< std::pair<int,int> > * coordsPtr = c1.getCoordinatesPTR(); 
		
			for (int i = 0; i < 10; i ++){
			c1.addPixel(std::make_pair<int,int>(1,4));
		}
		//ptr is returned 
		REQUIRE (c1.getCoordinatesPTR() ==  coordsPtr); 
		std::pair<int,int> elem4  = (*coordsPtr)[4];
		//data is accessible 
		REQUIRE (c1.getPixel(4) ==  elem4); 
		
	}

}



// Tests for the PGMIMGProcessor Class

TEST_CASE ("PGMIMGProcessor class Unit Tests")
{

	SECTION ("Default Constructor")
	{
		PGMIMG p;

		REQUIRE(p.filename == "NULL");
		REQUIRE(p.getComponentCount() == 0);
		REQUIRE(p.img == nullptr);
		REQUIRE(p.IMGheight == 0 );
		REQUIRE(p.IMGwidth == 0);
	}


	SECTION ("Custom Constructor")
	{

		PGMIMG p("test.pgm", 128 );

		REQUIRE(p.filename == "test.pgm");
		REQUIRE(p.threshold == 128);
		REQUIRE(p.img != nullptr);
		REQUIRE(p.IMGheight == 220 );
		REQUIRE(p.IMGwidth == 180);

	}


	SECTION ("Copy Constructor")
	{
		PGMIMG p1("test.pgm", 128); //// p1.extractComponents(128,10);
		
		PGMIMG p2(p1); // Call the copy constructor
		std::cout << "copy " << std::endl;

		REQUIRE(p1.IMGheight == p2.IMGheight);
		REQUIRE(p1.IMGwidth == p2.IMGwidth);
		REQUIRE(p1.threshold == p2.threshold);

		REQUIRE(p1.filename == p2.filename);
		REQUIRE(p2.getComponentCount()== p1.getComponentCount());

		REQUIRE(p1.img != p2.img); // dynamically allocated arrays not have same memory location stipulation
		REQUIRE(p1.outimg != p2.outimg);

		for (int i =0; i < p1.IMGheight; i+=10){
			for (int j =0; j<p2.IMGwidth; j+=10){
				REQUIRE(p1.img[i][j] == p2.img[i][j]); //dynamically allocated arrays have the same values stipulation
				REQUIRE(p1.outimg[i][j] == p2.outimg[i][j]);
			}
		}

		
	}

	SECTION ("Move Constructor"){
		PGMIMG p1("test.pgm", 128);
		p1.extractComponents(128,10);
		// std::cout << "P1:" <<p1.getComponentCount() << std::endl;
		unsigned char ** imgAdr = p1.img;
		unsigned char ** outimgAdr = p1.outimg;
		int compCount = p1.getComponentCount();
		PGMIMG p2(std::move(p1)); // Call the move constructor

		
		// // Test for p1
		REQUIRE(p1.img == nullptr); // We need to make sure that p1 is no longer managing any dynamic memory (since we moved it)
		REQUIRE(p1.outimg == nullptr); 

		// ensure filename AND components got moved out 
		REQUIRE(p1.filename != p2.filename); 
		REQUIRE(p1.getComponentCount() == 0); 
		REQUIRE(p2.getComponentCount() == compCount);

		// // Test for p2
		REQUIRE(p2.filename == "test.pgm");
		REQUIRE(p2.threshold == 128);
		REQUIRE(p2.IMGheight == 220 );
		REQUIRE(p2.IMGwidth == 180);
		

		//ensure dyanmic memory is still being pointed to in the right locations
		REQUIRE(p2.img == imgAdr );
		REQUIRE(p2.outimg == outimgAdr);
		
	}

	SECTION ("Copy Assignment Operator")
	{
		PGMIMG p1("test.pgm", 128 );
		p1.extractComponents(128,10);

		
		
	
		int compCount = p1.getComponentCount();
		PGMIMG p2;

		p2 = p1; // Call the copy assignment operator 



		REQUIRE(p1.IMGheight == p2.IMGheight);
		REQUIRE(p1.IMGwidth == p2.IMGwidth);
		REQUIRE(p1.threshold == p2.threshold);

		REQUIRE(p1.filename == p2.filename);
		REQUIRE(p2.getComponentCount()== p1.getComponentCount());

	REQUIRE(p1.img != p2.img); // dynamically allocated arrays not have same memory location stipulation	
		REQUIRE(p1.outimg != p2.outimg);

		for (int i =0; i < p1.IMGheight; i+=10){
			for (int j =0; j<p2.IMGwidth; j+=10){
				REQUIRE(p1.img[i][j] == p2.img[i][j]); //dynamically allocated arrays have the same values stipulation
				REQUIRE(p1.outimg[i][j] == p2.outimg[i][j]);
			}
		}



		// Check the self assignment case

		unsigned char ** imgAdr = p1.img;
		unsigned char ** outimgAdr = p1.outimg;
		p1 = p1;

		REQUIRE(p1.img == imgAdr); // Make sure that the memory address of p1.id has not changed
		REQUIRE(p1.outimg == outimgAdr);

	}



	SECTION ("Move Assignment Operator"){
		PGMIMG p1("test.pgm", 128 );
		p1.extractComponents(128,10);

		unsigned char ** imgAdr = p1.img;
		unsigned char ** outimgAdr = p1.outimg;
	
	int compCount = p1.getComponentCount();
		PGMIMG p2;
		
	
		p2 = std::move(p1); // Call the move assignment operator
	

		// // Test for p1
		REQUIRE(p1.img == nullptr); // We need to make sure that p1 is no longer managing any dynamic memory (since we moved it)
		REQUIRE(p1.outimg == nullptr); 

		// ensure filename got moved out 
		REQUIRE(p1.filename != p2.filename); 
		

		// // Test for p2
		REQUIRE(p2.filename == "test.pgm");
		REQUIRE(p2.threshold == 128);
		REQUIRE(p2.IMGheight == 220 );
		REQUIRE(p2.IMGwidth == 180);

		//ensure dyanmic memory is still being pointed to in the right locations
		REQUIRE(p2.img == imgAdr );
		REQUIRE(p2.outimg == outimgAdr);




		REQUIRE(p1.img == nullptr); // Here we make sure that p1 is no longer managing any memory
		REQUIRE(p1.outimg == nullptr); 


		REQUIRE(p1.getComponentCount() ==0 ); // ensure component vector got moved 
		REQUIRE(p2.getComponentCount() == compCount); // ensure component vector got moved 

		// Check the self assignment case
		p2 = std::move(p2); // Call the move assignment operator
		REQUIRE(p2.img == imgAdr); // Make sure that the memory address of p1.id has not changed
		REQUIRE(p2.outimg == outimgAdr);
		

	}



	SECTION ("Parse Image"){
	
		PGMIMG p1;
		std::ifstream imgfile("test.pgm", std::ios::binary); // open file in binary mode
		if (!imgfile) {
		std::cerr << "File open failed!" << std::endl;
		exit(1);
		} 
		p1.parseImg(imgfile);
		//test params and header reading 
		REQUIRE(p1.IMGheight == 220);
		REQUIRE(p1.IMGwidth == 180);
		//test data 
		REQUIRE(p1.img[0][0] == (unsigned char)'-');
}

	SECTION("Get Component Count "){
		PGMIMG p; 
			for (int i = 0; i < 5; i++){
				CONCOMP c(i);
				(*p.getComponents()).push_back(std::make_shared<CONCOMP>(c));
			}
			REQUIRE(p.getComponentCount() == 5);
		
	}

	SECTION("Is Valid"){
		PGMIMG p1("small2.pgm", 128 );
		std::cout << "validity visual" << std::endl; 
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 5; j++){
				std::cout << p1.isValid(i,j) << "   "; 
			}
			std::cout << "" << std::endl;
		}


		REQUIRE(p1.isValid(-1,0) == false);
		REQUIRE(p1.isValid(1,-1) == false);
		REQUIRE(p1.isValid(6,4) == false);


		REQUIRE(p1.isValid(1,1) == true);
		REQUIRE(p1.isValid(2,3) == true);


		PGMIMG p2("small2.pgm", 128 );
		REQUIRE(p1.isValid(1,1) == true);
		REQUIRE(p1.isValid(1,2) == true);
		REQUIRE(p1.isValid(2,3) == true);
		
	}


		SECTION("BFS"){
		PGMIMG p1("small2.pgm", 128 );
		//give valid seed pixel
		CONCOMP c = p1.bfs(1,1); 
		REQUIRE(c.getNumPixels() == 2); 
		

		PGMIMG p2("small3.pgm", 128 );
		//give valid seed pixel
		CONCOMP c2 = p2.bfs(1,1);
		REQUIRE(c2.getNumPixels() == 11); 

		
	}



		SECTION ("Get Smallest Size" ){
		PGMIMG p("small2.pgm", 128 );
		p.extractComponents(128,0);
		// p.printComponents();
		REQUIRE(p.getSmallestSize() == 2); 



		PGMIMG p2("size.pgm", 128 );
		p2.extractComponents(128,0);
		//size aquried w/ gimp histogram of the pictured triange 
		REQUIRE(p2.getSmallestSize() == 1048); 
		
		

	}
	SECTION ("Get Largest Size" ){

		PGMIMG p("small2.pgm", 128 );
		p.extractComponents(128,0);
		// p.printComponents();
		REQUIRE(p.getLargestSize() == 2); 



		PGMIMG p2("size.pgm", 128 );
		p2.extractComponents(128,0);
		//size aquried w/ gimp histogram of the pictured big triange 
		REQUIRE(p2.getLargestSize() == 5478); 

	}



	SECTION("Print Component Data"){
		PGMIMG p2("test2.pgm", 128 );
		p2.extractComponents(128,0);
		p2.printComponents();
		// evidence of this test is displayed to the terminal output 
	}


	SECTION ("Filter Components By Size"){
		//see with no bounds
		PGMIMG p1("size.pgm", 128 );
		p1.extractComponents(128,0); 
		REQUIRE(p1.getComponentCount() == 4); // Make sure that the 4 blobs are recognized

		// with bounds that exclude 2 
		PGMIMG p2("size.pgm", 128 );
		p2.extractComponents(128,0);
		p2.filterComponentsBySize(1500, 10000000);
		REQUIRE(p2.getComponentCount() == 2); // Make sure that ONLY 2 blobs are recognized


		//reduce num components in the pepper test image 
		PGMIMG p3("test2.pgm", 128 );
		p3.extractComponents(128,0);
		p3.filterComponentsBySize(50, 10000000);
		REQUIRE(p3.getComponentCount() == 3); // Make sure that ONLY 3 large blobs of pepper are recognized


		//use max argument 
		PGMIMG p4("size.pgm", 128 );
		p4.extractComponents(128,50);
		REQUIRE(p4.getComponentCount() == 4); 
		p4.filterComponentsBySize(50, 1800);
		REQUIRE(p4.getComponentCount() == 2); // Make sure that ONLY 2 smaller objects are reckognized 

		PGMIMG p5("test2.pgm", 128 );
		p5.extractComponents(128,1);
		REQUIRE(p5.getComponentCount() == 9); //see all objected before max filter 
		p5.filterComponentsBySize(0, 50);
		REQUIRE(p5.getComponentCount() == 6); 


		} 


	SECTION("Make Out Image (helper method w/ iterator through components)"){
		PGMIMG p3("test2.pgm", 128 );
		p3.extractComponents(128,0);
		p3.makeOutImg(); 
		REQUIRE((unsigned char)p3.outimg[0][0] ==  (unsigned char)0);
	}


	SECTION("Write Components "){
		PGMIMG p3("test2.pgm", 128 );
		p3.extractComponents(128,0);
		// std::cout << p3.getComponentCount() << std::endl;
		p3.makeOutImg();
		p3.writeComponents("test2OUT.pgm");
	
	}

			SECTION("Extract Components"){
		//one simple component 
		PGMIMG p1("dot.pgm", 128 );
		p1.extractComponents(128,0); 
		// std::cout << p1.getComponentCount() << std::endl;
		REQUIRE(p1.getComponentCount() == 1); 

		
		// many simple components
		PGMIMG p2("size.pgm", 128 );
		p2.extractComponents(128,0);
		REQUIRE(p2.getComponentCount() == 4); 

		

		//many complex components
		PGMIMG p4("test2.pgm", 128 );
		p4.extractComponents(128,0);
		//9 determined using gimp threshold 
		REQUIRE(p4.getComponentCount() == 9); 



		//using max and min params 
		PGMIMG p5("minmax.pgm", 200 );
		PGMIMG p6("minmax.pgm", 200 );
		//get only the middle three elems w/ 
		p5.extractComponents(128, 100, 800);
		p6.extractComponents(128,1);

		//middle elems should remain in the p5
		REQUIRE(p5.getComponentCount() == 3); 
		REQUIRE(p6.getComponentCount() == 9); 

	}

}