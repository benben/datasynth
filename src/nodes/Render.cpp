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

    win = ofxFensterManager::get()->createFenster(0, 0 ,1200, 800, OF_WINDOW);
    win->setWindowTitle("Render");
    win->setBackgroundColor(0);
	renderWin = new RenderWindow();
	renderWin->setup();
    win->addListener(renderWin);
    bValueIsSaveable = true;

    saver.init(10, 0, true);

    ofAddListener(ofEvents.keyReleased, this, &Render::keyReleased);
    ofAddListener(win->events.draw, this, &Render::start);
    ofAddListener(win->events.update, this, &Render::stop);
}

Render::~Render()
{
    ofRemoveListener(ofEvents.keyReleased, this, &Render::keyReleased);
    ofRemoveListener(win->events.draw, this, &Render::start);
    ofRemoveListener(win->events.update, this, &Render::stop);
    ofxFensterManager::get()->deleteFenster(win);
    delete renderWin;
}

void Render::start(ofEventArgs & args)
{
    saver.begin();
}

void Render::stop(ofEventArgs & args)
{
    saver.end();
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

void Render::keyReleased(ofKeyEventArgs & args)
{
    if(args.key=='s') {
        cout << "pressed in render" << endl;
        char str[1024];
        sprintf(str, "%d%d%d_%d%d%d.png", ofGetYear(), ofGetMonth(), ofGetDay(), ofGetHours(), ofGetMinutes(), ofGetSeconds());
        saver.finish(ofToString(str), true);
    }
}
