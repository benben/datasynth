#include "Scale.h"
using namespace ds;

Scale::Scale(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = _name;
    width = 100;

    Spread x(new SpreadStruct);
    x->name = "x";
    input.push_back(new Pin(x, color, 1));
    Spread y(new SpreadStruct);
    y->name = "y";
    input.push_back(new Pin(y, color, 1));

    Spread width(new SpreadStruct);
    width->name = "width";
    input.push_back(new Pin(width, color, 1));
    Spread height(new SpreadStruct);
    height->name = "height";
    input.push_back(new Pin(height, color, 1));

    Spread x2(new SpreadStruct);
    x2->name = "startcolor";
    input.push_back(new Pin(x2, color, 1));
    Spread y2(new SpreadStruct);
    y2->name = "endcolor";
    input.push_back(new Pin(y2, color, 1));

    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Scale::drawScale);
}

Scale::~Scale()
{
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Scale::drawScale);
    input.clear();
    output.clear();
}

void Scale::process()
{
}

void Scale::drawScale(ofEventArgs & args)
{
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
    float startcolor = 255;
    float endcolor = 255;
    if(input[0]->value->data.size() > 0)
        x = boost::get<float>(input[0]->value->data[0]);
    if(input[1]->value->data.size() > 0)
        y = boost::get<float>(input[1]->value->data[0]);
    if(input[2]->value->data.size() > 0)
        width = boost::get<float>(input[2]->value->data[0]);
    if(input[3]->value->data.size() > 0)
        height = boost::get<float>(input[3]->value->data[0]);
    if(input[4]->value->data.size() > 0)
        startcolor = boost::get<float>(input[4]->value->data[0]);
    if(input[5]->value->data.size() > 0)
        endcolor = boost::get<float>(input[5]->value->data[0]);

    ofFloatColor c;
    c.setHsb(0,255,255);
    if(width != 0 && height != 0)
    {
        for(int i = 0; i <= width; i ++)
        {
            c.setHue(ofMap(i,0,width,startcolor,endcolor));
            ofSetColor(c.r,c.g,c.b);
            ofRect(x+i,y,1,height);
        }
    }
}
