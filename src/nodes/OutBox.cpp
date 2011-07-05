#include "OutBox.h"
using namespace ds;

OutBox::OutBox(float _x, float _y, string _name)
{
    //set inputs and outputs to initial values here
    x = _x;
    y = _y;
    name = _name;
    input.push_back(new Pin(0.0, 1));
}

OutBox::~OutBox()
{
}

void OutBox::process()
{
    //cout << "process from OutBox()\n";
}

void OutBox::draw(ofEventArgs & args)
{
    //leave this if you wanna draw the basic shapes
    basedraw(args);
    ofDrawBitmapString(ofToString(input[0]->value),x+80, y+20);
}
