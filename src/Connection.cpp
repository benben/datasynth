#include "Connection.h"
using namespace ds;

Connection::Connection(NodePtr _outNode, int _outPinID, NodePtr _inNode, int _inPinID)
{
    outNode = _outNode;
    outPinID = _outPinID;
    inNode = _inNode;
    inPinID = _inPinID;
    inNode->input[inPinID]->addConnection();
    outNode->output[outPinID]->addConnection();
    ofRegisterMouseEvents(this);
    ofAddListener(inNode->input[inPinID]->deleteEvent, this, &Connection::setInvalid);
    ofAddListener(outNode->output[outPinID]->updateEvent, this, &Connection::process);
    bIsInvalid = false;
    mouseX = 0;
    mouseY = 0;
}

Connection::~Connection()
{
    cout << "removing connection" << endl;
    ofRemoveListener(inNode->input[inPinID]->deleteEvent, this, &Connection::setInvalid);
    ofRemoveListener(outNode->output[outPinID]->updateEvent, this, &Connection::process);
    inNode->input[inPinID]->removeConnection();
    outNode->output[outPinID]->removeConnection();
    ofUnregisterMouseEvents(this);
}

void Connection::setInvalid(int & args)
{
    bIsInvalid = true;
}

void Connection::process(int & args)
{
    if(inNode->input[inPinID]->bIsInvalid || outNode->output[outPinID]->bIsInvalid)
    {
        bIsInvalid = true;
    }
    else
    {
        try
        {
            inNode->input[inPinID]->setValue(outNode->output[outPinID]->value);
            inNode->bProcessed = false;
        }
        catch(...)
        {
            bIsInvalid = true;
        }
    }
}

void Connection::draw()
{
    if(!bIsInvalid)
    {
        ofSetColor(255,255,255,255);
        ofLine(outNode->output[outPinID]->x+7, outNode->output[outPinID]->y+7, inNode->input[inPinID]->x+7, inNode->input[inPinID]->y+7);
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
    v1.set(outNode->output[outPinID]->x+7, outNode->output[outPinID]->y+7);
    v2.set(inNode->input[inPinID]->x+7, inNode->input[inPinID]->y+7);
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
