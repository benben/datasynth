#include "Pin.h"

using namespace ds;

Pin::Pin(Spread _value, int _maxConnections)
{
    ofRegisterMouseEvents(this);
    connections = 0;
    maxConnections = _maxConnections;
    value = _value;
    mouseX = 0;
    mouseY = 0;
    width = 15;
    height = 15;
}

Pin::~Pin()
{
    cout << "Pin killed!" << endl;
}

void Pin::setInvalid()
{
    cout << "setting pin invalid..." << endl;
    ofUnregisterMouseEvents(this);
    //notify event to connection
    int x = 10;
    ofNotifyEvent(deleteEvent,x,this);
}

bool Pin::isFree()
{
    if(maxConnections != 0)
    {
        if(connections < maxConnections)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

void Pin::addConnection()
{
    connections++;
}

void Pin::removeConnection()
{
    connections--;
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
