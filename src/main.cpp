#include "ofMain.h"
#include "Core.h"
#include "ofxFensterManager.h"

using namespace ds;

//========================================================================
int main( ){
	ofSetupOpenGL(ofxFensterManager::get(), 800 ,800, OF_WINDOW);
	ofRunFensterApp(new Core());
}
