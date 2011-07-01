#include "Object.h"

using namespace ds;

Object::Object()
{
    ofRegisterMouseEvents(this);
    ofAddListener(ofEvents.draw, this, &Object::draw);
    mouseX = 0;
    mouseY = 0;
}

Object::~Object()
{
    ofUnregisterMouseEvents(this);
    ofRemoveListener(ofEvents.draw, this, &Object::draw);
    input.clear();
    output.clear();
}

void Object::process()
{
}

void Object::basedraw(ofEventArgs & args)
{
    if(inside(mouseX, mouseY))
    {
        ofSetColor(255,240,0,255);
    }
    else
    {
        ofSetColor(255,180,0,255);
    }
    ofRect(x,y,width,height);
    ofSetColor(0,0,0,255);
    ofDrawBitmapString(name, x+2, y+20);
    /*for(unsigned int j = 0; j < input.size(); j++)
    {
        ofSetColor(255,230,0,255);
        ofRect(x+(j*16),y-16,15,15);
    }
    for(unsigned int j = 0; j < output.size(); j++)
    {
        ofSetColor(255,230,0,255);
        ofRect(x+(j*16),y+height+1,15,15);
    }*/
}

void Object::draw(ofEventArgs & args)
{
    basedraw(args);
}

void Object::mouseMoved(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}

void Object::mousePressed(ofMouseEventArgs & args)
{
}

void Object::mouseDragged(ofMouseEventArgs & args)
{
    if(inside(mouseX, mouseY))
    {
        x = args.x - (mouseX-x);
        y = args.y - (mouseY-y);
    }
    mouseX = args.x;
    mouseY = args.y;
}

void Object::mouseReleased(ofMouseEventArgs & args)
{
}
