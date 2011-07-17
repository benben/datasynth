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
    win = ofxFensterManager::get()->createFenster(600, 0 ,600, 400, OF_WINDOW);
	renderWin = new RenderWindow();
	renderWin->setup();
    win->addListener(renderWin);
}

Render::~Render()
{
    ofxFensterManager::get()->deleteFenster(win);
    delete renderWin;
}
