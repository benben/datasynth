#include "Text.h"
using namespace ds;

Text::Text(int _ID, float _x, float _y, string _name)
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
    TextInputPtr t(new TextInput(&x, &y, name, &value, &bProcessed, &bIsActive));
    textinput = t;
    bValueIsSaveable = true;
    height = 40;
    bProcessed = false;
}

Text::~Text()
{
    output.clear();
}

string Text::getValueAsString()
{
    return value;
}

void Text::setValueFromString(string _val)
{
    value = _val;
}

void Text::process()
{
    if(!bProcessed)
    {
        cout << "process from Text()\n";
        //output[0]->value->data[0] = value;
        Spread temp(new SpreadStruct);
        temp->name = "none";
        temp->data.push_back(value);
        output[0]->setValue(temp);
        bProcessed = true;
    }
    //cout << "output pin: " << output[0]->value.data[0] << endl;
}

void Text::draw()
{
    textinput->draw();
}
