#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    myMenu = new menu();
    myMenu->setup();
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    myMenu->draw();
    for(int i = 0; i < nodes.size(); i++) {
        nodes[i].draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    myMenu->mouseX = mouseX;
    myMenu->mouseY = mouseY;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    /*node temp;
    temp.x = mouseX;
    temp.y = mouseY;
    temp.width = 100;
    temp.height= 20;
    nodes.push_back(temp);*/
    if (button == 0)
    {
        myMenu->close();
    }
    if (button == 2)
    {
        myMenu->init();
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
