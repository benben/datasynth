#include "OutBox.h"
using namespace ds;

OutBox::OutBox(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    //set inputs and outputs to initial values here
    x = _x;
    y = _y;
    name = _name;
    width = 70;
    color.r = 230;
    color.g = 230;
    color.b = 230;
    Spread temp(new SpreadStruct);
    temp->name = "none";
    input.push_back(new Pin(temp, color, 1));
}

OutBox::~OutBox()
{
    input.clear();
}

void OutBox::process()
{
    //cout << "process from OutBox()\n";
}

void OutBox::draw()
{
    height = 30 + (input[0]->value->data.size()-1)*11;
    if(input[0]->value->data.size() > 0)
    {
        int t = 0;
        if(input[0]->value->data.size() > 100)
        {
            t = 100;
        }
        else
        {
            t = input[0]->value->data.size();
        }
        for(unsigned int i = 0; i < t; i++)
        {
            try
            {
                ofFloatColor c = boost::get<ofFloatColor>(input[0]->value->data[i]);
                ofSetColor(c.r,c.g,c.b,255);
                ofRect(x,y+(i*11),150,11);
                ofSetColor(c.invert());
                ofDrawBitmapString(ofToString(c.getHue())+","+ofToString(c.getSaturation())+","+ofToString(c.getBrightness()),x, y+10+(i*11));
            }
            catch(const boost::bad_get &v)
            {
                try
                {
                    ofDrawBitmapString(ofToString(boost::get<float>(input[0]->value->data[i])),x+3, y+13+(i*11));
                }
                catch(const boost::bad_get &v)
                {
                    ofDrawBitmapString(boost::get<string>(input[0]->value->data[i]),x+3, y+13+(i*11));
                }

            }
        }
    }
    else
    {
        ofDrawBitmapString("OutBox",x+3, y+13);
    }
}
