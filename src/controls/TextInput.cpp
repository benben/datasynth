#include "TextInput.h"

using namespace ds;

TextInput::TextInput(float* _x, float* _y, string _name, float* _value, bool* _bIsNodeActive)
{
    ofRegisterMouseEvents(this);
    ofRegisterKeyEvents(this);
    bIsNodeActive = _bIsNodeActive;
    name = _name;
    value = _value;
    x = _x;
    y = _y;
    b.x = *x;
    b.y = *y;
    b.width = 147;
    b.height = 15;
}

TextInput::~TextInput()
{
    ofUnregisterMouseEvents(this);
    ofUnregisterKeyEvents(this);
}

void TextInput::draw()
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

void TextInput::setValue(string _val)
{
    *value = boost::lexical_cast<float>(_val);
}

void TextInput::keyPressed(ofKeyEventArgs & args)
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

void TextInput::keyReleased(ofKeyEventArgs & args)
{
}

void TextInput::mouseMoved(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}

void TextInput::mousePressed(ofMouseEventArgs & args)
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

void TextInput::mouseDragged(ofMouseEventArgs & args)
{
}

void TextInput::mouseReleased(ofMouseEventArgs & args)
{
}
