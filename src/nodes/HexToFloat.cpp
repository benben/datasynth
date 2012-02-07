#include "HexToFloat.h"
using namespace ds;

HexToFloat::HexToFloat(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = "+";
    color.r = 255;
    color.g = 43;
    color.b = 243;
    width = 31;

    Spread temp(new SpreadStruct);
    temp->name = "none";
    //temp->data.push_back(0.0);
    input.push_back(new Pin(temp, color));

    Spread temp2(new SpreadStruct);
    temp2->name = "none";
    //temp2->data.push_back(0.0);
    output.push_back(new Pin(temp2, color));

}

HexToFloat::~HexToFloat()
{
    input.clear();
    output.clear();
}

void HexToFloat::process()
{
    if(!bProcessed)
    {
        int size0 = input[0]->value->data.size();
        if(size0 > 0)
        {
            Spread temp(new SpreadStruct);
            temp->name = "none";
            for(unsigned int i = 0; i < input[0]->value->data.size(); i++)
            {
                float val;

                std::stringstream() >> std::hex >> val;
                temp->data.push_back(val);
            }
            output[0]->setValue(temp);
        }
        bProcessed = true;
    }
}
