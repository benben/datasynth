#include "Circle.h"
using namespace ds;

Circle::Circle(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = _name;

    Spread x(new SpreadStruct);
    x->name = "X";
    input.push_back(new Pin(x, color, 1));
    Spread y(new SpreadStruct);
    y->name = "Y";
    input.push_back(new Pin(y, color, 1));
    Spread r(new SpreadStruct);
    y->name = "Radius";
    input.push_back(new Pin(r, color, 1));
    Spread c(new SpreadStruct);
    c->name = "Color";
    input.push_back(new Pin(c, color, 1));
    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Circle::drawMe);

    height = 40;
    bProcessed = false;
}

Circle::~Circle()
{
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Circle::drawMe);
    input.clear();
}

void Circle::process()
{
}

void Circle::drawMe(ofEventArgs & args)
{
    int size0 = input[0]->value->data.size();
    int size1 = input[1]->value->data.size();
    int size2 = input[2]->value->data.size();
    int size3 = input[3]->value->data.size();
    if(size0 > 0 && size1 > 0 && size2 > 0)
    {
        int it = 0;
        while(it < maxSliceCount())
        {
            if(size3 > 0)
            {
                ofSetColor(boost::get<ofColor>(input[3]->value->data[it % size3]));
            }
            else
            {
                ofSetColor(255,0,0,255);
            }
            ofSetCircleResolution(100);
            ofCircle(boost::get<float>(input[0]->value->data[it % size0]), boost::get<float>(input[1]->value->data[it % size1]), boost::get<float>(input[2]->value->data[it % size2]));
            it++;
        }
    }
}
