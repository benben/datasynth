#include "BaseNode.h"

using namespace ds;

BaseNode::BaseNode()
{
    ofAddListener(ofxFensterManager::get()->getPrimaryWindow()->events.draw, this, &BaseNode::draw);
    ofRegisterMouseEvents(this);
    type = "";
    mouseX = 0;
    mouseY = 0;
    bIsInvalid = false;
    bIsActive = false;
    color.r = 255;
    color.g = 180;
    color.b = 0;
}

BaseNode::~BaseNode()
{
    basedelete();
}

void BaseNode::init()
{
}

void BaseNode::process()
{
}

void BaseNode::basedraw()
{
    if(inside(mouseX, mouseY))
    {
        ofSetColor(color.r,color.g+40,color.b);
    }
    else
    {
        ofSetColor(color.r,color.g,color.b,255);
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

void BaseNode::draw(ofEventArgs & args)
{
    basedraw();
}

void BaseNode::mouseMoved(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}

void BaseNode::mousePressed(ofMouseEventArgs & args)
{
    if(inside(mouseX, mouseY))
    {
        bIsActive = true;
    }
}

void BaseNode::mouseDragged(ofMouseEventArgs & args)
{
    if(inside(mouseX, mouseY) && bIsActive)
    {
        x = args.x - (mouseX-x);
        y = args.y - (mouseY-y);
    }
    mouseX = args.x;
    mouseY = args.y;
}

void BaseNode::mouseReleased(ofMouseEventArgs & args)
{
    bIsActive = false;
}

void BaseNode::setInvalid()
{
    bIsInvalid = true;
    BOOST_FOREACH(Pin* pin, input)
        pin->setInvalid();
    BOOST_FOREACH(Pin* pin, output)
        pin->setInvalid();
}

void BaseNode::basedelete()
{
    ofUnregisterMouseEvents(this);
    ofRemoveListener(ofxFensterManager::get()->getPrimaryWindow()->events.draw, this, &BaseNode::draw);
    cout << "calling basedelete!" << endl;
    BOOST_FOREACH(Pin* pin, input)
        delete pin;
    input.clear();
    BOOST_FOREACH(Pin* pin, output)
        delete pin;
    output.clear();
}
