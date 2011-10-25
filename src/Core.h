#pragma once

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxXmlSettings.h"
#include "ofxTileSaver.h"
#include "src/Factory.h"
#include "src/Menu.h"

namespace ds {

class Core : public ofxFensterListener {

	public:
		void setup();
		void update();
		void draw();
        void exit();

        void save();
        ofxXmlSettings saveXml;
        void load();
        ofxXmlSettings loadXml;
        bool bLoad;

        void keyPressed(int key, ofxFenster* win);
        void keyReleased(int key, ofxFenster* win);
        void mouseMoved(int x, int y, ofxFenster* win);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

		void handleMenuEvent(menuEventType & args);

        Factory factory;

        int ID;
        vector <NodePtr> nodes;
        vector <ConnectionPtr> connections;
        ofxXmlSettings XMLObjects;

        NodePtr out, in;
        int outNodeID, outPinID, inNodeID, inPinID;
        bool isInSet, isOutSet;

        bool checkID(int _ID);
        NodePtr getNodeByID(int _ID);

        bool bShowFPS;

        ofxTileSaver saver;
};

}
