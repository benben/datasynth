#include "Render.h"

using namespace ds;

Render::Render(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    x = _x;
    y = _y;
    name = _name;
    color.r = 0;
    color.g = 235;
    color.b = 60;

    Spread temp(new SpreadStruct);
    temp->name = "none";
    temp->data.push_back(0.0);
    input.push_back(new Pin(temp, color));

    win = ofxFensterManager::get()->createFenster(0, 0 ,640, 360, OF_WINDOW);
    win->setWindowTitle("Render");
    win->setBackgroundColor(0);
	renderWin = new RenderWindow();
	renderWin->setup();
    win->addListener(renderWin);
    bValueIsSaveable = true;
}

Render::~Render()
{
    ofxFensterManager::get()->deleteFenster(win);
    delete renderWin;
}

void Render::process()
{
    win->setBackgroundColor(boost::get<float>(input[0]->value->data[0]));
}

string Render::getValueAsString()
{
    ofPoint pos = win->getWindowPosition();
    ofPoint size = win->getWindowSize();
    string str = ofToString(pos.x) + "," + ofToString(pos.y) + "," + ofToString(size.x) + "," + ofToString(size.y);
    return ofToString(str);
}

void Render::setValueFromString(string _val)
{
    vector<string> v = ofSplitString(_val,",");
    win->setWindowPosition(ofToInt(v[0]), ofToInt(v[1]));
    win->setWindowShape(ofToInt(v[2]), ofToInt(v[3]));
}
