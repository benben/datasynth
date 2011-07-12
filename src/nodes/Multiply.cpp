#include "Multiply.h"
using namespace ds;

Multiply::Multiply(float _x, float _y, string _name)
{
    x = _x;
    y = _y;
    name = _name;
    Spread temp(new SpreadStruct);
    temp->name = "none";
    temp->data.push_back(0.0);
    input.push_back(new Pin(temp, color));
    Spread temp2(new SpreadStruct);
    temp2->name = "none";
    temp2->data.push_back(0.0);
    input.push_back(new Pin(temp2, color));
    Spread temp3(new SpreadStruct);
    temp3->name = "none";
    temp3->data.push_back(0.0);
    output.push_back(new Pin(temp3, color));
}

Multiply::~Multiply()
{
}

void Multiply::process()
{
    //cout << "process from Multiply()\n";
    output[0]->value->data[0] = input[0]->value->data[0] * input[1]->value->data[0];
    //cout << "output pin: " << output[0]->value << endl;
}
