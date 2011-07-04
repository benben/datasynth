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
    basedelete();
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
    for(unsigned int i = 0; i < input.size(); i++)
    {
        input[i]->draw(x+(i*16), y-16);
    }
    for(unsigned int i = 0; i < output.size(); i++)
    {
        output[i]->draw(x+(i*16),y+height+1);
    }
    ofSetColor(0,0,0,255);
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

void Object::basedelete()
{
    ofUnregisterMouseEvents(this);
    ofRemoveListener(ofEvents.draw, this, &Object::draw);
    cout << "calling basedelete!" << endl;
    BOOST_FOREACH(Pin* pin, input)
        delete pin;
    input.clear();
    BOOST_FOREACH(Pin* pin, output)
        delete pin;
    output.clear();
}
