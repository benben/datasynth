#include "OutBox.h"
using namespace ds;

OutBox::OutBox()
{
    //set inputs and outputs to initial values here
    input.push_back(new Pin(0.0));
}

OutBox::~OutBox()
{
}

void OutBox::process()
{
    cout << "process from OutBox()\n";
    //cout << "output pin: " << output[0] << endl;
}

void OutBox::draw(ofEventArgs & args)
{
    //leave this if you wanna draw the basic shapes
    basedraw(args);
    ofDrawBitmapString(ofToString(input[0]->value),x+80, y+20);
}
