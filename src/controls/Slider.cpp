#include "Slider.h"

Slider::Slider(float* _x, float* _y, string _name, float* _val, bool* _bIsNodeActive)
{
    ofRegisterMouseEvents(this);
    bIsNodeActive = _bIsNodeActive;
    val = _val;
    name = _name;
    min = 0;
    max = 3;
    x = _x;
    y = _y;
    b.x = *x;
    b.y = *y;
    b.width = 200;
    b.height = 20;
}

Slider::~Slider()
{
    ofUnregisterMouseEvents(this);
}

void Slider::draw()
{
    b.x = *x;
    b.y = *y;

    ofFill();
    ofSetColor(30, 30, 80);
    ofRect(b);

    float valAsPct = ofMap(*val, min, max, 0, b.width, true );
    ofEnableAlphaBlending();
    ofSetColor(180, 180, 180);
    ofRect(b.x+1, b.y+1, valAsPct-1, b.height-2);

    ofSetColor(230, 230, 230, 255);

    float stringY = b.y + 14;

    ofDrawBitmapString(name, b.x + 4, stringY);
    string valStr;
    valStr = ofToString(*val, 3);
    ofDrawBitmapString(valStr , (b.x + b.width) - 3 - valStr.length() * 8, stringY );
}
void Slider::setValue(Spread _val)
{
    *val = _val->data[0];
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
    if(b.inside(args.x,args.y))
    {
        setValue(args.x, args.y, true);
        bIsActive = true;
        *bIsNodeActive = false;
    }
}

void Slider::mouseDragged(ofMouseEventArgs & args)
{
    if(b.inside(args.x,args.y) && bIsActive)
    {
        setValue(args.x, args.y, false);
    }
}

void Slider::mouseReleased(ofMouseEventArgs & args)
{
   bIsActive = false;
}
