#include "Donut.h"
using namespace ds;

Donut::Donut(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = _name;
    width = 90;
    Spread x1(new SpreadStruct);
    x1->name = "X1";
    input.push_back(new Pin(x1, color, 1));
    Spread y1(new SpreadStruct);
    y1->name = "Y1";
    input.push_back(new Pin(y1, color, 1));
    Spread y2(new SpreadStruct);
    y2->name = "Y2";
    input.push_back(new Pin(y2, color, 1));
    Spread width(new SpreadStruct);
    width->name = "width";
    input.push_back(new Pin(width, color, 1));

    //Color Input
    Spread c(new SpreadStruct);
    c->name = "Color";
    input.push_back(new Pin(c, color, 1));
    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Donut::drawDonut);
}

Donut::~Donut()
{
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &Donut::drawDonut);
    input.clear();
    output.clear();
}

void Donut::process()
{
}

void Donut::drawDonut(ofEventArgs & args)
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
            try
            {
                float x1 = boost::get<float>(input[0]->value->data[it % input[0]->value->data.size()]);
                float y1 = boost::get<float>(input[1]->value->data[it % input[1]->value->data.size()]);
                float y2 = boost::get<float>(input[2]->value->data[it % input[2]->value->data.size()]);
                float width = boost::get<float>(input[3]->value->data[it % input[3]->value->data.size()]);

            ofSetPolyMode(OF_POLY_WINDING_ODD);
            vector<ofVec2f> path;
            int num = 100;
            float step = (PI) / num;
            for(int i = num; i >= 0; i--)
            {
                path.push_back(ofVec2f( x1 + (y2-y1)/2*sin(i*step) , (y2-y1)/2 + y1 +  (y2-y1)/2*cos(i*step) ));
            }
            vector<ofVec2f> shape = extrude(path,width);

            ofBeginShape();
            for(int i = 0; i < shape.size(); i++)
            {
                ofVertex(shape[i].x,shape[i].y);
            }
            ofEndShape();
            ofFill();
            it++;
            }
            catch(...)
            {
                //cout << "wrong connection(s). can't process!" << endl;
            }
        }
    }
}

vector<ofVec2f> Donut::extrude(vector<ofVec2f> _path, float _width)
{
    int size = _path.size();
    vector<ofVec2f> temp;
    for(int i = 0; i < size; i++)
    {
        //getting the two path segments around a given path point
        ofVec2f d1 = _path[i] - _path[(i+size-1) % size];
        ofVec2f d2 = _path[(i+1) % size] - _path[i];

        //calculating the angle bisector
        ofVec2f t = d1.getPerpendicular() - d2.getPerpendicular();
        t.rotate(-90);

        //calculating the correct width for the angle bisector (needs to be longer because of its angle)
        float w;
        if(sin(t.angleRad(d1)) != 0)
            w = (_width/2) / sin(t.angleRad(d1));
        else
            w = (_width/2);
        t.scale(w);
        temp.push_back(t + _path[i]);
        t.scale(-w);
        temp.push_back(t + _path[i]);
    }

    //IF polyMode == OF_POLY_WINDING_NONZERO
    //TODO: fix this for paths with size < 3
    if(ofGetStyle().polyMode == 0 && size > 2)
    {
        temp[0] = (_path[0] - _path[1]).getPerpendicular().scale(_width/2) + _path[0];
        temp[1] = (_path[0] - _path[1]).getPerpendicular().scale(-_width/2) + _path[0];
        temp[temp.size()-2] = (_path[size-2] - _path[size-1]).getPerpendicular().scale(_width/2) + _path[size-1];
        temp[temp.size()-1] = (_path[size-2] - _path[size-1]).getPerpendicular().scale(-_width/2) + _path[size-1];
    }

    vector<ofVec2f> ret;
    if(temp.size() > 2)
    {
        for(int i = 0; i < temp.size(); i++)
        {
            if(i % 2 != 0)
                ret.push_back(temp[i]);
        }
        for(int i = temp.size()-1; i > 0; i--)
        {
            if(i % 2 == 0)
                ret.push_back(temp[i]);
        }
        ret.push_back(temp[0]);

        //IF polyMode != OF_POLY_WINDING_NONZERO
        if(ofGetStyle().polyMode != 0)
        {
            //add two more points to close the shape
            ret.push_back(temp[temp.size()-2]);
            ret.push_back(temp[temp.size()-1]);
        }
    }
    return ret;
}
