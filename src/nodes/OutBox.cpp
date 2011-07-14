#include "OutBox.h"
using namespace ds;

OutBox::OutBox(float _x, float _y, string _name)
{
    //set inputs and outputs to initial values here
    x = _x;
    y = _y;
    name = _name;
    color.r = 230;
    color.g = 230;
    color.b = 230;
    Spread temp(new SpreadStruct);
    temp->name = "none";
    temp->data.push_back(0.0);
    input.push_back(new Pin(temp, color, 1));
}

OutBox::~OutBox()
{
    input.clear();
}

void OutBox::process()
{
    //cout << "process from OutBox()\n";
}

void OutBox::draw(ofEventArgs & args)
{
    //leave this if you wanna draw the basic shapes
    basedraw();
    height = 30 + (input[0]->value->data.size()-1)*11;
    for(unsigned int i = 0; i < input[0]->value->data.size(); i++)
    {
        ofDrawBitmapString(ofToString(input[0]->value->data[i]),x+80, y+20+(i*11));
    }
}
