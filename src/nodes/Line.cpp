#include "Line.h"
using namespace ds;

Line::Line(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = _name;
    width = 79;
    Spread x1(new SpreadStruct);
    x1->name = "X1";
    input.push_back(new Pin(x1, color, 1));
    Spread y1(new SpreadStruct);
    y1->name = "Y1";
    input.push_back(new Pin(y1, color, 1));
    Spread x2(new SpreadStruct);
    x2->name = "X2";
    input.push_back(new Pin(x2, color, 1));
    Spread y2(new SpreadStruct);
    y2->name = "Y2";
    input.push_back(new Pin(y2, color, 1));
    //Color Input
    Spread c(new SpreadStruct);
    c->name = "Color";
    input.push_back(new Pin(c, color, 1));
    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Line::drawLines);
}

Line::~Line()
{
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Line::drawLines);
    input.clear();
    output.clear();
}

void Line::process()
{
}

void Line::drawLines(ofEventArgs & args)
{
    int min = 1;
    int max = 0;
    //size-1 becaue we don't check the color input
    for(unsigned int i = 0; i < input.size()-1; i++)
    {
        if(input[i]->value->data.size() > max)
        {
            max = input[i]->value->data.size();
        }
        if(input[i]->value->data.size() < min)
        {
            min = input[i]->value->data.size();
        }
    }
    if(max > 0 && min > 0)
    {
        int it = 0;
        while(it < max)
        {
            if(input[4]->value->data.size() > 0)
            {
                ofSetColor(boost::get<ofColor>(input[4]->value->data[it % input[4]->value->data.size()]));
            }
            else
            {
                ofSetColor(255,255,255,255);
            }
            float x1 = (int)boost::get<float>(input[0]->value->data[it % input[0]->value->data.size()]);
            float y1 = (int)boost::get<float>(input[1]->value->data[it % input[1]->value->data.size()]);
            float x2 = (int)boost::get<float>(input[2]->value->data[it % input[2]->value->data.size()]);
            float y2 = (int)boost::get<float>(input[3]->value->data[it % input[3]->value->data.size()]);
            ofLine(x1,y1,x2,y2);
            it++;
        }
    }
}
