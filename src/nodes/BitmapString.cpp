#include "BitmapString.h"
using namespace ds;

BitmapString::BitmapString(int _ID, float _x, float _y, string _name)
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
    Spread str(new SpreadStruct);
    str->name = "str";
    input.push_back(new Pin(str, color, 1));
    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &BitmapString::drawBitmapString);
}

BitmapString::~BitmapString()
{
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &BitmapString::drawBitmapString);
    input.clear();
}

void BitmapString::process()
{
}

void BitmapString::drawBitmapString(ofEventArgs & args)
{
    int size0 = input[0]->value->data.size();
    int size1 = input[1]->value->data.size();
    int size2 = input[2]->value->data.size();
    if(size0 > 0 && size1 > 0 && size2 > 0)
    {
        int it = 0;
        int max = maxSliceCount();
        while(it < max)
        {
            ofSetColor(255,255,255,255);
            float x = (int)boost::get<float>(input[0]->value->data[it % size0]);
            float y = (int)boost::get<float>(input[1]->value->data[it % size1]);
            string str = boost::get<string>(input[2]->value->data[it % size2]);
            ofDrawBitmapString(str,x,y);
            it++;
        }
    }
}
