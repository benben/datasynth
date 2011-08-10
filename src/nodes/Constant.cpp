#include "Constant.h"
using namespace ds;

Constant::Constant(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    value = 0.0;
    Spread temp(new SpreadStruct);
    temp->name = "none";
    temp->data.push_back(value);
    output.push_back(new Pin(temp, color));
    x = _x;
    y = _y;
    name = _name;
    FloatInputPtr t(new FloatInput(&x, &y, name, &value, &bProcessed, &bIsActive));
    floatinput = t;
    SliderPtr s(new Slider(&x, &y, name, &value, &bProcessed, &bIsActive));
    slider = s;
    slider->setValue(value);
    bValueIsSaveable = true;
    height = 40;
    bProcessed = false;
}

Constant::~Constant()
{
    output.clear();
}

string Constant::getValueAsString()
{
    return ofToString(value);
}

void Constant::setValueFromString(string _val)
{
    value = ofToFloat(_val);
}

void Constant::process()
{
    if(!bProcessed)
    {
        //cout << "process from Constant()\n";
        //output[0]->value->data[0] = value;
        Spread temp(new SpreadStruct);
        temp->name = "none";
        temp->data.push_back(value);
        output[0]->setValue(temp);
        bProcessed = true;
    }
    //cout << "output pin: " << output[0]->value.data[0] << endl;
}

void Constant::draw()
{
    floatinput->draw();
    slider->draw();
}
