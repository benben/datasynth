#include "Point.h"
using namespace ds;

Point::Point(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
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
    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Point::drawPoints);
}

Point::~Point()
{
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Point::drawPoints);
    input.clear();
}

void Point::process()
{
}

void Point::drawPoints(ofEventArgs & args)
{
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
        while(it < max)
        {
            ofSetColor(255,255,255,255);
            float x = (int)boost::get<float>(input[0]->value->data[it % size0]);
            float y = (int)boost::get<float>(input[1]->value->data[it % size1]);
            ofLine(x-3,y,x+2,y);
            ofLine(x,y-2,x,y+3);
            it++;
        }
    }
}
