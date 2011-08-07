#include "FloatInput.h"

using namespace ds;

FloatInput::FloatInput(float* _x, float* _y, string _name, float* _value, bool* _bProcessed, bool* _bIsNodeActive)
{
    ofRegisterMouseEvents(this);
    ofRegisterKeyEvents(this);
    bIsNodeActive = _bIsNodeActive;
    bProcessed = _bProcessed;
    name = _name;
    value = _value;
    x = _x;
    y = _y;
    b.x = *x;
    b.y = *y;
    b.width = 147;
    b.height = 15;
}

FloatInput::~FloatInput()
{
    ofUnregisterMouseEvents(this);
    ofUnregisterKeyEvents(this);
}

void FloatInput::draw()
{
    b.x = *x + 2;
    b.y = *y + 11;

    ofNoFill();
    ofSetColor(0,0,0,255);
    ofRect(b);
    if(!bIsActive)
    {
        ofDrawBitmapString(ofToString(*value),b.x+3,b.y+12);
    }
    else
    {
        ofDrawBitmapString(input,b.x+3,b.y+12);
    }
    ofFill();
}

void FloatInput::setValue(string _val)
{
    *value = boost::lexical_cast<float>(_val);
    *bProcessed = false;
}

void FloatInput::keyPressed(ofKeyEventArgs & args)
{
    if(bIsActive)
    {
        //BACKSPACE
        if(args.key == OF_KEY_BACKSPACE)
        {
            if(input.size() > 0)
            {
                input.erase(input.end()-1);
            }
        }
        //ENTER
        else if(args.key == OF_KEY_RETURN)
        {
            //if first char is a dot, add a zero in front
            if(input[0] == '.')
            {
                input = "0" + input;
            }
            setValue(input);
            bIsActive = false;
        }
        //EVERYTHING ELSE
        else
        {
            input.push_back(args.key);
        }
    }
}

void FloatInput::keyReleased(ofKeyEventArgs & args)
{
}

void FloatInput::mouseMoved(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}

void FloatInput::mousePressed(ofMouseEventArgs & args)
{
    if(b.inside(args.x,args.y))
    {
        if(args.button == 0)
        {
            *bIsNodeActive = false;
            bIsActive = true;
            input = ofToString(*value);
        }
    }
    else
    {
        bIsActive = false;
    }
}

void FloatInput::mouseDragged(ofMouseEventArgs & args)
{
}

void FloatInput::mouseReleased(ofMouseEventArgs & args)
{
}
