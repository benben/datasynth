#include "Min.h"
using namespace ds;

Min::Min(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = "Min";
    color.r = 255;
    color.g = 255;
    color.b = 0;
    width = 31;

    Spread temp(new SpreadStruct);
    temp->name = "none";
    input.push_back(new Pin(temp, color));

    Spread temp2(new SpreadStruct);
    temp2->name = "Min";
    output.push_back(new Pin(temp2, color));
}

Min::~Min()
{
    input.clear();
    output.clear();
}

void Min::process()
{
    if(!bProcessed)
    {
        if(input[0]->value->data.size() > 0)
        {
            Spread temp(new SpreadStruct);
            temp->name = "none";
            float min = boost::get<float>(input[0]->value->data[0]);
            for(unsigned int i = 0; i < input[0]->value->data.size(); i++)
            {
                if(boost::get<float>(input[0]->value->data[i]) < min)
                {
                    min = boost::get<float>(input[0]->value->data[i]);
                }
            }
            temp->data.push_back(min);
            output[0]->setValue(temp);
        }
        bProcessed = true;
    }
}
