#include "Max.h"
using namespace ds;

Max::Max(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = "Max";
    color.r = 255;
    color.g = 255;
    color.b = 0;
    width = 31;

    Spread temp(new SpreadStruct);
    temp->name = "none";
    input.push_back(new Pin(temp, color));

    Spread temp2(new SpreadStruct);
    temp2->name = "Max";
    output.push_back(new Pin(temp2, color));
}

Max::~Max()
{
    input.clear();
    output.clear();
}

void Max::process()
{
    if(!bProcessed)
    {
        if(input[0]->value->data.size() > 0)
        {
            Spread temp(new SpreadStruct);
            temp->name = "none";
            float max = boost::get<float>(input[0]->value->data[0]);
            for(unsigned int i = 0; i < input[0]->value->data.size(); i++)
            {
                if(boost::get<float>(input[0]->value->data[i]) > max)
                {
                    max = boost::get<float>(input[0]->value->data[i]);
                }
            }
            temp->data.push_back(max);
            output[0]->setValue(temp);
        }
        bProcessed = true;
    }
}
