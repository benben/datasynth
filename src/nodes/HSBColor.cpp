#include "HSBColor.h"
using namespace ds;

HSBColor::HSBColor(float _x, float _y, string _name)
{
    x = _x;
    y = _y;
    name = "Color";
    width = 47;
    color.r = 232;
    color.g = 47;
    color.b = 47;
    Spread h(new SpreadStruct);
    h->name = "H";
    input.push_back(new Pin(h, color));
    Spread s(new SpreadStruct);
    s->name = "S";
    input.push_back(new Pin(s, color));
    Spread b(new SpreadStruct);
    b->name = "B";
    input.push_back(new Pin(b, color));

    Spread c(new SpreadStruct);
    c->name = "HSBColor";
    output.push_back(new Pin(c, color));
}

HSBColor::~HSBColor()
{
    input.clear();
    output.clear();
}

void HSBColor::process()
{
    //cout << "process from HSBColor()\n";
    int min = 1;
    int max = 0;
    for(unsigned int i = 0; i < input.size(); i++)
    {
        if(input[i]->value->data.size() > max)
        {
            max = input[i]->value->data.size();
        }
        if(input[i]->value->data.size() < min)
        {
            min = input[i]->value->data.size();
        }
    }
    if(max > 0 && min > 0)
    {
        int it = 0;
        output[0]->value->data.clear();
        //TODO could be problematic?!
        while(it < max)
        {
            float h = boost::get<float>(input[0]->value->data[it % input[0]->value->data.size()]);
            float s = boost::get<float>(input[1]->value->data[it % input[1]->value->data.size()]);
            float b = boost::get<float>(input[2]->value->data[it % input[2]->value->data.size()]);

            ofColor c;
            c.setHsb(h,s,b);
            output[0]->value->data.push_back(c);
            it++;
        }
    }
    //output[0]->value->data[0] = input[0]->value->data[0] * input[1]->value->data[0];
    //cout << "output pin: " << output[0]->value << endl;
}
