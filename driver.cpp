#include "PGMimageProcessor.cpp" 
#include <limits>

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " [options] <inputPGMfile> \n"
              <<  "<inputPGMfile> MUST BE a valid PGM image" 
              << "Options:\n"
              << "-s <int> <int> (-s min max) ; set the minimum and maximum valid components size "
              << "-t <int> set the threshold for component detection (default=128, limit to [0. . . 255])"
              << "-p print out all the component data and the total component number and the sizes of the smallest and largest components."
              << "-w <outPGMfile> write out all retained components as foreground/background pixels to a new PGM file given by <outPGMfile>"
              << std::endl;
}



int main(int argc, char *argv[]){
     if (argc < 3) {
        show_usage(argv[0]);
        return 1;
    }

int min = 3;
int max = std::numeric_limits<int>::max(); 
int threshold = 128;
bool print = false; 
std::string outfilename = "NULL"; 

std::string imgfilename  = argv[1];

for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        //set the minimum and maximum valid components size
        if (arg == "-s") {
            //get min 
            min = std::stoi(argv[i+1]);
            //get max if not another flag 
            if (argv[i+2][1] != '-'){max = std::stoi(argv[i+2]); i++;}
            i++;
        }
            //set threshold
          else  if (arg == "-t") {
            threshold = std::stoi(argv[i+1]);
            i++;
        }    

            //print flag
         else  if (arg == "-p") {
            print = true; 
        }    

            // write flag 
          else  if (arg == "-w") {
            outfilename  = argv[i+1];
            i++;
        }    
    }

    //process the image
    HRLISA004::PGMimageProcessor proc(imgfilename,threshold);
    proc.extractComponents(128, min, max);



    //print components 
    if (print == true){
        // as the total component number and the sizes of the smallest and largest components.
        proc.printComponents();
    }

    //write file
    if (outfilename != "NULL"){
        proc.writeComponents(outfilename);
    }

    return 0; 
}