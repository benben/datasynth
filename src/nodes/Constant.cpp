#include "Constant.h"
using namespace ds;

Constant::Constant(float _x, float _y, string _name)
{
    Spread temp(new SpreadStruct);
    temp->name = "none";
    temp->data.push_back(0.0);
    output.push_back(new Pin(temp, color));
    x = _x;
    y = _y;
    name = _name;
    SliderPtr s(new Slider(&x, &y, name, &output[0]->value->data[0], &bIsActive));
    slider = s;
}

Constant::~Constant()
{
}

void Constant::init()
{
    //cout << "init from constant: " << output[0]->value << endl;
    slider->setValue(output[0]->value);
}

void Constant::process()
{
    //cout << "process from Constant()\n";
    //cout << "output pin: " << output[0]->value.data[0] << endl;
}

void Constant::draw(ofEventArgs & args)
{
    //leave this if you wanna draw the basic shapes
    basedraw();
}
