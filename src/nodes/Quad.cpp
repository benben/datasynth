#include "Quad.h"
using namespace ds;

Quad::Quad(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = _name;
    width = 159;

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
    Spread x3(new SpreadStruct);
    x3->name = "X3";
    input.push_back(new Pin(x3, color, 1));
    Spread y3(new SpreadStruct);
    y3->name = "Y3";
    input.push_back(new Pin(y3, color, 1));
    Spread x4(new SpreadStruct);
    x4->name = "X4";
    input.push_back(new Pin(x4, color, 1));
    Spread y4(new SpreadStruct);
    y4->name = "Y4";
    input.push_back(new Pin(y4, color, 1));

    //Color Input
    Spread c(new SpreadStruct);
    c->name = "Color";
    input.push_back(new Pin(c, color, 1));
    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Quad::drawQuad);
}

Quad::~Quad()
{
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Quad::drawQuad);
    input.clear();
    output.clear();
}

void Quad::process()
{
}

void Quad::drawQuad(ofEventArgs & args)
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
            if(input[8]->value->data.size() > 0)
            {
                ofSetColor(boost::get<ofColor>(input[8]->value->data[it % input[8]->value->data.size()]));
            }
            else
            {
                ofSetColor(255,255,255,255);
            }
            float x1 = (int)boost::get<float>(input[0]->value->data[it % input[0]->value->data.size()]);
            float y1 = (int)boost::get<float>(input[1]->value->data[it % input[1]->value->data.size()]);
            float x2 = (int)boost::get<float>(input[2]->value->data[it % input[2]->value->data.size()]);
            float y2 = (int)boost::get<float>(input[3]->value->data[it % input[3]->value->data.size()]);
            float x3 = (int)boost::get<float>(input[4]->value->data[it % input[4]->value->data.size()]);
            float y3 = (int)boost::get<float>(input[5]->value->data[it % input[5]->value->data.size()]);
            float x4 = (int)boost::get<float>(input[6]->value->data[it % input[6]->value->data.size()]);
            float y4 = (int)boost::get<float>(input[7]->value->data[it % input[7]->value->data.size()]);

            ofNoFill();
            ofSetPolyMode(OF_POLY_WINDING_NONZERO);
            ofBeginShape();
                ofVertex(x1,y1);
                ofVertex(x2,y2);
                ofVertex(x3,y3);
                ofVertex(x4,y4);
            ofEndShape();
            ofFill();
            it++;
        }
    }
}
