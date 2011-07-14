#include "Connection.h"
using namespace ds;

Connection::Connection(Pin * _out, int _outNodeID, int _outPinID, Pin * _in, int _inNodeID, int _inPinID)
{
    cout << "creating connection..." << endl;
    out = _out;
    outNodeID = _outNodeID;
    outPinID = _outPinID;
    in = _in;
    inNodeID = _inNodeID;
    inPinID = _inPinID;
    in->addConnection();
    out->addConnection();
    ofAddListener(ofxFensterManager::get()->getPrimaryWindow()->events.draw, this, &Connection::draw);
    ofRegisterMouseEvents(this);
    bIsInvalid = false;
    mouseX = 0;
    mouseY = 0;
}

Connection::~Connection()
{
    cout << "removing connection" << endl;
    in->removeConnection();
    out->removeConnection();
    ofRemoveListener(ofxFensterManager::get()->getPrimaryWindow()->events.draw, this, &Connection::draw);
    ofUnregisterMouseEvents(this);
}

void Connection::process()
{
    if(in->bIsInvalid || out->bIsInvalid)
    {
        bIsInvalid = true;
    }
    else
    {
        in->setValue(out->value);
    }
}

void Connection::draw(ofEventArgs & args)
{
    if(!bIsInvalid)
    {
        ofSetColor(255,255,255,255);
        ofLine(out->x+7, out->y+7, in->x+7, in->y+7);
    }
}
void Connection::mouseMoved(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}

void Connection::mousePressed(ofMouseEventArgs & args)
{
}

void Connection::mouseDragged(ofMouseEventArgs & args)
{
}

void Connection::mouseReleased(ofMouseEventArgs & args)
{
}

bool Connection::mouseIsOn()
{
    float distance = 1000;
    ofVec2f v1;
    ofVec2f v2;
    ofVec2f vMouse;
    v1.set(out->x+7, out->y+7);
    v2.set(in->x+7, in->y+7);
    vMouse.set(mouseX, mouseY);
    ofVec2f segment = v2 - v1;
    if(segment.length() != 0)
    {
        distance = ((vMouse.x - v1.x)*(v2.x - v1.x) + (vMouse.y - v1.y)*(v2.y - v1.y)) / (segment.length() * segment.length());
        if(distance < 1 && distance > 0)
        {
            distance = (v1.x*(vMouse.y-v2.y)+v2.x*(v1.y-vMouse.y)+vMouse.x*(v2.y-v1.y)) / sqrt( (v2.x-v1.x)*(v2.x-v1.x) + (v1.y-v2.y)*(v1.y-v2.y) );
            distance = sqrt(distance*distance);
        }
        else
        {
            if((v1 - vMouse).length() < (v2 - vMouse).length())
            {
                distance = (v1 - vMouse).length();
            }
            else
            {
                distance = (v2 - vMouse).length();
            }
        }
    }
    else
    {
        return false;
    }
    if(distance < 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}
