#include "Object.h"
using namespace ds;

Object::Object()
{
    ofAddListener(ofEvents.draw, this, &Object::draw);
}

Object::~Object()
{
    ofRemoveListener(ofEvents.draw, this, &Object::draw);
}

void Object::process()
{
    cout << "process from Object()\n";
}

void Object::draw(ofEventArgs & args)
{
    ofSetColor(255,230,0,255);
    ofRect(x,y,width,height);
    for(unsigned int j = 0; j < input.size(); j++)
    {
        ofSetColor(80,80,80,255);
        ofRect(x+(j*8),y,8,8);
        ofSetColor(255,230,0,255);
        ofRect(x+(j*8),y,7,7);
    }
    ofSetColor(0,0,0,255);
    ofDrawBitmapString(name, x+2, y+20);
    for(unsigned int j = 0; j < output.size(); j++)
    {
        ofSetColor(80,80,80,255);
        ofRect(x+(j*8),y+height-8,8,8);
        ofSetColor(255,230,0,255);
        ofRect(x+(j*8),y+height-7,7,7);
    }
}
