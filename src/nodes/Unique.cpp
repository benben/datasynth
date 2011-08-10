#include "Unique.h"
using namespace ds;

Unique::Unique(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = "Unique";
    color.r = 255;
    color.g = 255;
    color.b = 0;
    width = 31;

    Spread temp(new SpreadStruct);
    temp->name = "none";
    input.push_back(new Pin(temp, color));

    Spread temp2(new SpreadStruct);
    temp2->name = "Unique";
    output.push_back(new Pin(temp2, color));
}

Unique::~Unique()
{
    input.clear();
    output.clear();
}

void Unique::process()
{
    if(!bProcessed)
    {
        if(input[0]->value->data.size() > 0)
        {
            Spread temp(new SpreadStruct);
            temp->name = "none";
            for(unsigned int i = 0; i < input[0]->value->data.size(); i++)
            {
                bool isIn = false;
                for(unsigned int j = 0; j < temp->data.size(); j++)
                {
                    try
                    {
                        if(boost::get<float>(input[0]->value->data[i]) == boost::get<float>(temp->data[j]))
                        {
                            isIn = true;
                        }
                    }
                    catch(...)
                    {
                        try
                        {
                            if(boost::get<string>(input[0]->value->data[i]) == boost::get<string>(temp->data[j]))
                            {
                                isIn = true;
                            }
                        }
                        catch(...)
                        {
                            ofFloatColor col1 = boost::get<ofFloatColor>(input[0]->value->data[i]);
                            ofFloatColor col2 = boost::get<ofFloatColor>(temp->data[j]);
                            if(col1.r == col2.r && col1.g == col2.g && col1.b == col2.b)
                            {
                                isIn = true;
                            }
                        }
                    }
                }
                if(!isIn)
                {
                    temp->data.push_back(input[0]->value->data[i]);
                }
            }
            output[0]->setValue(temp);
        }
        bProcessed = true;
    }
}
