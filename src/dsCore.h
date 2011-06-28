#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "src/menu.h"
#include "src/object.h"

class dsCore : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void createObject(entry & args);
        void destroyObject(object* _obj);

        vector <object*> objects;
        ofxXmlSettings XMLObjects;
};
