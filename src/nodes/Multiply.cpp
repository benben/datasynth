#include "Multiply.h"
using namespace ds;

Multiply::Multiply(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = "*";
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
    input.push_back(new Pin(temp2, color));
    Spread temp3(new SpreadStruct);
    temp3->name = "none";
    temp3->data.push_back(0.0);
    output.push_back(new Pin(temp3, color));
}

Multiply::~Multiply()
{
    input.clear();
    output.clear();
}

void Multiply::process()
{
    if(!bProcessed)
    {
        //cout << "process from Multiply()\n";
        int size0 = input[0]->value->data.size();
        int size1 = input[1]->value->data.size();
        if(size0 > 0 && size1 > 0)
        {
            int max = 0;
            if(size0 >= size1)
                max = size0;
            else
                max = size1;
            int it = 0;
            Spread temp(new SpreadStruct);
            temp->name = "none";
            while(it < max)
            {
                //cout << it << endl;
                temp->data.push_back(boost::get<float>(input[0]->value->data[it % size0]) * boost::get<float>(input[1]->value->data[it % size1]));
                it++;
            }
            output[0]->setValue(temp);
        }
        //output[0]->value->data[0] = input[0]->value->data[0] * input[1]->value->data[0];
        //cout << "output pin: " << output[0]->value << endl;
        bProcessed = true;
    }
}
