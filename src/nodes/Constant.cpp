#include "Constant.h"
using namespace ds;

Constant::Constant(float _x, float _y, string _name)
{
    value = 0.0;
    Spread temp(new SpreadStruct);
    temp->name = "none";
    temp->data.push_back(value);
    output.push_back(new Pin(temp, color));
    x = _x;
    y = _y;
    name = _name;
    SliderPtr s(new Slider(&x, &y, name, &value, &bIsActive));
    slider = s;
    bValueIsSaveable = true;
}

Constant::~Constant()
{
}

void Constant::init()
{
    //cout << "init from constant: " << output[0]->value << endl;
    slider->setValue(value);
}

string Constant::getValueAsString()
{
    cout << ofToString(value) << endl;
    return ofToString(value);
}

void Constant::process()
{
    output[0]->value->data[0] = value;
    //cout << "process from Constant()\n";
    //cout << "output pin: " << output[0]->value.data[0] << endl;
}

void Constant::draw()
{
    //leave this if you wanna draw the basic shapes
    basedraw();
    slider->draw();
}
