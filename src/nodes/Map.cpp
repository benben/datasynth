#include "Map.h"
using namespace ds;

Map::Map(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = "Map";
    color.r = 255;
    color.g = 255;
    color.b = 0;
    width = 79;

    Spread val(new SpreadStruct);
    val->name = "Value";
    input.push_back(new Pin(val, color));

    Spread min1(new SpreadStruct);
    min1->name = "Min1";
    input.push_back(new Pin(min1, color));

    Spread max1(new SpreadStruct);
    max1->name = "Max1";
    input.push_back(new Pin(max1, color));

    Spread min2(new SpreadStruct);
    min2->name = "Min2";
    input.push_back(new Pin(min2, color));

    Spread max2(new SpreadStruct);
    max2->name = "Max2";
    input.push_back(new Pin(max2, color));

    Spread temp2(new SpreadStruct);
    temp2->name = "Map";
    output.push_back(new Pin(temp2, color));
}

Map::~Map()
{
    input.clear();
    output.clear();
}

void Map::process()
{
    if(!bProcessed)
    {
        if(input[0]->value->data.size() > 0 && input[1]->value->data.size() > 0 && input[2]->value->data.size() > 0 && input[3]->value->data.size() > 0 && input[4]->value->data.size() > 0)
        {
            Spread temp(new SpreadStruct);
            temp->name = "none";
            for(unsigned int i = 0; i < input[0]->value->data.size(); i++)
            {
                float val = boost::get<float>(input[0]->value->data[i]);
                float min1 = boost::get<float>(input[1]->value->data[i % input[1]->value->data.size()]);
                float max1 = boost::get<float>(input[2]->value->data[i % input[2]->value->data.size()]);
                float min2 = boost::get<float>(input[3]->value->data[i % input[3]->value->data.size()]);
                float max2 = boost::get<float>(input[4]->value->data[i % input[4]->value->data.size()]);

                temp->data.push_back(ofMap(val,min1,max1,min2,max2,false));
            }
            output[0]->setValue(temp);
        }
        bProcessed = true;
    }
}
