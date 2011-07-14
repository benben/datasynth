#include "Render.h"

using namespace ds;

Render::Render(float _x, float _y, string _name)
{
    x = _x;
    y = _y;
    name = _name;
    color.r = 0;
    color.g = 235;
    color.b = 60;
    win = ofxFensterManager::get()->createFenster(600, 400, OF_WINDOW);
	renderWin = new RenderWindow();
	renderWin->setup();
    win->addListener(renderWin);

}

Render::~Render()
{
    //ofxFensterManager::get()->removeFenster(win);
}

void Render::process()
{
    //cout << "process from Render()\n";
}

void Render::draw(ofEventArgs & args)
{
    //leave this if you wanna draw the basic shapes
    basedraw();
}
