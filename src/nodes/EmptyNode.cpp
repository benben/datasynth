#include "EmptyNode.h"
using namespace ds;

EmptyNode::EmptyNode(int _ID, float _x, float _y, string _name)
{
    ID =_ID;
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
    if(!bProcessed)
    {
        cout << "process from EmptyNode()\n";
        //output[0]->setValue(temp);
        //cout << "output pin: " << output[0] << endl;
        bProcessed = true;
    }
}
