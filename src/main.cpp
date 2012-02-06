#include "ofMain.h"
#include "Core.h"
#include "ofxFensterManager.h"
#include "ProgramParams.h"
using namespace ds;

//========================================================================
int main(int argc, char *argv[]){

    ProgramParams commandLine = ProgramParams(argc, argv);

    if (commandLine.hasOption("width")){
        std::cout << "Bin da" <<endl;
    }

    //if commandLine.has()


	ofSetupOpenGL(ofxFensterManager::get(), 800 ,800, OF_WINDOW);
	ofRunFensterApp(new Core());
}

