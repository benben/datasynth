#include "RGBColor.h"
using namespace ds;

RGBColor::RGBColor(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = "RGB";
    width = 47;
    color.r = 232;
    color.g = 47;
    color.b = 47;
    Spread h(new SpreadStruct);
    h->name = "R";
    input.push_back(new Pin(h, color));
    Spread s(new SpreadStruct);
    s->name = "G";
    input.push_back(new Pin(s, color));
    Spread b(new SpreadStruct);
    b->name = "B";
    input.push_back(new Pin(b, color));

    Spread c(new SpreadStruct);
    c->name = "RGBColor";
    output.push_back(new Pin(c, color));
}

RGBColor::~RGBColor()
{
    input.clear();
    output.clear();
}

void RGBColor::process()
{
    if(!bProcessed)
    {
        //cout << "process from RGBColor()\n";
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
            Spread temp(new SpreadStruct);
            temp->name = "none";
            while(it < max)
            {
                float r = boost::get<float>(input[0]->value->data[it % input[0]->value->data.size()]);
                float g = boost::get<float>(input[1]->value->data[it % input[1]->value->data.size()]);
                float b = boost::get<float>(input[2]->value->data[it % input[2]->value->data.size()]);

                ofColor c;
                c.r = (int)r;
                c.g = (int)g;
                c.b = (int)b;
                temp->data.push_back(c);
                it++;
            }
            output[0]->setValue(temp);
        }
        //output[0]->value->data[0] = input[0]->value->data[0] * input[1]->value->data[0];
        //cout << "output pin: " << output[0]->value << endl;
        bProcessed = true;
    }
}
