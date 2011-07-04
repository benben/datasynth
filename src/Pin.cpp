#include "Pin.h"

using namespace ds;

Pin::Pin(Type _value)
{
    ofRegisterMouseEvents(this);
    value = _value;
    mouseX = 0;
    mouseY = 0;
    width = 15;
    height = 15;
}

Pin::~Pin()
{
    ofUnregisterMouseEvents(this);
    cout << "Pin killed!" << endl;
}

void Pin::draw(float _x, float _y)
{
    x = _x;
    y = _y;
    if(inside(mouseX, mouseY))
    {
        ofSetColor(255,240,0,255);
    }
    else
    {
        ofSetColor(255,180,0,255);
    }
    ofRect(x, y, width, height);
}

void Pin::mouseMoved(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}

void Pin::mousePressed(ofMouseEventArgs & args)
{
    if(inside(args.x, args.y))
    {
        bIsActive = true;
    }
    else
    {
        bIsActive = false;
    }
}

void Pin::mouseDragged(ofMouseEventArgs & args)
{
    if(!bIsActive) {
    if(inside(args.x, args.y))
    {
        bIsActive = true;
    }
    else
    {
        bIsActive = false;
    }
    }
}

void Pin::mouseReleased(ofMouseEventArgs & args)
{
}
