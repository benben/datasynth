#include "EmptyNode.h"
using namespace ds;

EmptyNode::EmptyNode(float _x, float _y, string _name)
{
    x = _x;
    y = _y;
    name = _name;
    //set inputs and outputs to initial values here
    //output.push_back(0.0);
}

EmptyNode::~EmptyNode()
{
}

void EmptyNode::process()
{
    cout << "process from EmptyNode()\n";
    //cout << "output pin: " << output[0] << endl;
}

void EmptyNode::draw()
{
    //leave this if you wanna draw the basic shapes
    basedraw();
}
