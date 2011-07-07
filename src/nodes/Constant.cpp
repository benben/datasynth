#include "Constant.h"
using namespace ds;

Constant::Constant(float _x, float _y, string _name)
{
    output.push_back(new Pin(0.0));
    x = _x;
    y = _y;
    name = _name;
    SliderPtr s(new Slider(&x, &y, name, &boost::get<double>(output[0]->value)));
    slider = s;
}

Constant::~Constant()
{
}

void Constant::init()
{
    cout << "init from constant: " << output[0]->value << endl;
    slider->setValue(output[0]->value);
}

void Constant::process()
{
    //cout << "process from Constant()\n";
    //cout << "output pin: " << output[0]->value << endl;
}

void Constant::draw(ofEventArgs & args)
{
    //leave this if you wanna draw the basic shapes
    basedraw();
}
