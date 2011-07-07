#include "ofMain.h"
#include "Core.h"
#include "ofAppGlutWindow.h"

using namespace ds;

//========================================================================
int main( ){

    ofAppGlutWindow window;

	ofSetupOpenGL(&window, 1024,576, OF_WINDOW);			// <-------- setup the GL context
    ofSetWindowPosition(200,100);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new Core());

}
