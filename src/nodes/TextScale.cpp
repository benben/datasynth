#include "TextScale.h"
using namespace ds;

TextScale::TextScale(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = _name;
    width = 111;

    Spread x(new SpreadStruct);
    x->name = "x";
    input.push_back(new Pin(x, color, 1));
    Spread y(new SpreadStruct);
    y->name = "y";
    input.push_back(new Pin(y, color, 1));

    Spread width(new SpreadStruct);
    width->name = "width";
    input.push_back(new Pin(width, color, 1));

    Spread x2(new SpreadStruct);
    x2->name = "start";
    input.push_back(new Pin(x2, color, 1));
    Spread y2(new SpreadStruct);
    y2->name = "end";
    input.push_back(new Pin(y2, color, 1));

    Spread x3(new SpreadStruct);
    x3->name = "step";
    input.push_back(new Pin(x3, color, 1));
    Spread y3(new SpreadStruct);
    y3->name = "color";
    input.push_back(new Pin(y3, color, 1));

    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &TextScale::drawTextScale);
}

TextScale::~TextScale()
{
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &TextScale::drawTextScale);
    input.clear();
    output.clear();
}

void TextScale::process()
{
}

void TextScale::drawTextScale(ofEventArgs & args)
{
    float x = 0;
    float y = 0;
    float width = 0;
    float start = 0;
    float end = 0;
    float step = 50;
    ofFloatColor col = 255;
    if(input[0]->value->data.size() > 0)
        x = boost::get<float>(input[0]->value->data[0]);
    if(input[1]->value->data.size() > 0)
        y = boost::get<float>(input[1]->value->data[0]);
    if(input[2]->value->data.size() > 0)
        width = boost::get<float>(input[2]->value->data[0]);
    if(input[3]->value->data.size() > 0)
        start = boost::get<float>(input[3]->value->data[0]);
    if(input[4]->value->data.size() > 0)
        end = boost::get<float>(input[4]->value->data[0]);
    if(input[5]->value->data.size() > 0)
        step = boost::get<float>(input[5]->value->data[0]);
    if(input[6]->value->data.size() > 0)
        col = boost::get<ofFloatColor>(input[6]->value->data[0]);

    ofSetColor(col.r,col.g,col.b);

    if(width != 0 && step != 0 && step >= 1)
    {
        ofRect(x,y,1,10);
        ofDrawBitmapString(ofToString(start,1),x-4,y+23);
        ofRect(x+width,y,1,10);
        ofDrawBitmapString(ofToString(end,1),x+width-4,y+23);
        for(int i = (int)floor(start); i < (int)floor(end); i++)
        {
            if(i > (int)floor(start) + step/2 && i < (int)floor(end)-step/2)
            {
                int m = (int)floor(ofMap(i,start,end,0,width)) % (int)step;
                if(m == 0)
                {
                    ofRect(ofMap(i,start,end,x,x+width),y,1,10);
                    ofDrawBitmapString(ofToString(i,0),ofMap(i,start,end,x,x+width)-4,y+23);
                }
            }
        }
    }
}
