#include "ofMain.h"
#include "Core.h"
#include "ofxFensterManager.h"
#include <boost/program_options.hpp>
using namespace ds;
namespace po=boost::program_options;
//========================================================================
int main(int argc, char *argv[]){

    //ProgramParams commandLine = ProgramParams(argc, argv);
    try
    {
        po::options_description desc("Allowed options");
        desc.add_options()
        ("help", "print this help message")
        ("width", po::value<int>(), "set width of start window")
        ("height", po::value<int>(), "set height of start window")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc <<endl;
        }

        int width = 800;
        int height = 800;

        if (vm.count("width") & vm.count("height")){
            width = vm["width"].as<int>();
            height = vm["height"].as<int>();
        }

        ofSetupOpenGL(ofxFensterManager::get(), width ,height, OF_WINDOW);
	    ofRunFensterApp(new Core());

    }
    catch(...)
    {
        std::cout << "Check your input params" << std::endl;
    }
}

