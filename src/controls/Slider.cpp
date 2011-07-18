#include "Slider.h"

//some code stolen from here: https://github.com/openframeworks/openFrameworks/blob/master/apps/devApps/guiExample/src/ofSlider.h
using namespace ds;

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
    b.x = *x + 2;
    b.y = *y + 28;
    b.width = 147;
    b.height = 10;
}

Slider::~Slider()
{
    ofUnregisterMouseEvents(this);
}

void Slider::draw()
{
    if(*val >= max)
    {
        max = *val + (*val / 2);
    }
    if(*val <= min)
    {
        min = *val - (*val / 2);
    }
    b.x = *x + 2;
    b.y = *y + 28;

    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(b);
    ofFill();

    float valAsPct = ofMap(*val, min, max, 0, b.width, true );
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0);
    ofRect(b.x, b.y, valAsPct, b.height);
}
void Slider::setValue(float _val)
{
    *val = _val;
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
