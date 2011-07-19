#include "Pin.h"

using namespace ds;

Pin::Pin(Spread _value, ofColor _color, int _maxConnections)
{
    ofRegisterMouseEvents(this);
    connections = 0;
    maxConnections = _maxConnections;
    value = _value;
    color = _color;
    mouseX = 0;
    mouseY = 0;
    width = 15;
    height = 15;
    bIsInvalid = false;
}

Pin::~Pin()
{
    cout << "Pin killed!" << endl;
    value->data.clear();
}

void Pin::setValue(Spread _value)
{
    value = _value;
}

void Pin::setInvalid()
{
    cout << "setting pin invalid..." << endl;
    ofUnregisterMouseEvents(this);
    bIsInvalid = true;
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
        ofSetColor(color.r,color.g+40,color.b,255);
    }
    else
    {
        ofSetColor(color.r,color.g,color.b,255);
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
}

void Pin::mouseDragged(ofMouseEventArgs & args)
{
}

void Pin::mouseReleased(ofMouseEventArgs & args)
{
}
