#include "Slider.h"

Slider::Slider(float* _x, float* _y, string* _name, double* _val)
{
    ofRegisterMouseEvents(this);
    ofAddListener(ofEvents.draw, this, &Slider::draw);
    val = _val;
    namePtr = _name;
    name = *namePtr;
    min = 0;
    max = 255;
    parentXPtr = _x;
    parentYPtr = _y;
    b.x = *parentXPtr;
    b.y = *parentYPtr;
    b.width = 200;
    b.height = 20;
}

Slider::~Slider()
{
}

void Slider::draw(ofEventArgs & args)
{
    b.x = *parentXPtr;
    b.y = *parentYPtr;
    name = *namePtr;
    ofFill();
    ofSetColor(30, 30, 80);
    ofRect(b);

    double valAsPct = ofMap( *val, min, max, 0, b.width, true );
    ofEnableAlphaBlending();
    ofSetColor(180, 180, 180);
    ofRect(b.x+1, b.y+1, valAsPct-1, b.height-2);

    ofSetColor(230, 230, 230, 255);

    float stringY = b.y + 14;

    ofDrawBitmapString(name, b.x + 4, stringY);
    string valStr;
    valStr = ofToString(*val, 2);
    ofDrawBitmapString(valStr , (b.x + b.width) - 3 - valStr.length() * 8, stringY );
}

void Slider::setValue(float mx, float my, bool bCheck)
{
    if(b.inside(mx, my) )
    {
        *val = ofMap(mx, b.x, b.x + b.width, min, max, true);
    }
    else
    {
        return;
    }
}

void Slider::mouseMoved(ofMouseEventArgs & args)
{
}

void Slider::mousePressed(ofMouseEventArgs & args)
{
    setValue(args.x, args.y, true);
}

void Slider::mouseDragged(ofMouseEventArgs & args)
{
    setValue(args.x, args.y, false);
}

void Slider::mouseReleased(ofMouseEventArgs & args)
{
    //bGuiActive = false;
}
