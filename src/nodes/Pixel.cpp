#include "Pixel.h"
using namespace ds;

Pixel::Pixel(float _x, float _y, string _name)
{
    x = _x;
    y = _y;
    name = _name;
    width = 100;
    Spread x(new SpreadStruct);
    x->name = "X";
    input.push_back(new Pin(x, color, 1));
    Spread y(new SpreadStruct);
    y->name = "Y";
    input.push_back(new Pin(y, color, 1));
    Spread c(new SpreadStruct);
    c->name = "Color";
    input.push_back(new Pin(c, color, 1));
    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Pixel::drawMe);
}

Pixel::~Pixel()
{
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Pixel::drawMe);
    input.clear();
}

void Pixel::process()
{
}

void Pixel::drawMe(ofEventArgs & args)
{
    int size0 = input[0]->value->data.size();
    int size1 = input[1]->value->data.size();
    int size2 = input[2]->value->data.size();
    if(size0 > 0 && size1 > 0 && size2 > 0)
    {
        int max = 0;
        if(size0 >= size1)
            max = size0;
        else
            max = size1;

        if(size2 >= max)
            max = size2;

        int it = 0;
        while(it < max)
        {
            ofFloatColor c = boost::get<ofFloatColor>(input[2]->value->data[it % size2]);
            ofSetColor(c.r,c.g,c.b,255);
            ofRect(boost::get<float>(input[0]->value->data[it % size0]), boost::get<float>(input[1]->value->data[it % size1]),1,1);
            it++;
        }
    }
}
