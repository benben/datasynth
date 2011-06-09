#include "menu.h"

menu::menu()
{
    //ctor
    //bIsVisible = false;
}

menu::~menu()
{
    //dtor
}

void menu::setup()
{
    bIsVisible = false;
    XML.loadFile("menu.xml");
    XmlEntries = XML.getNumTags("ENTRY");
    for(int i = 0; i < XmlEntries; i++)
    {
        entry temp;
        temp.text = XML.getValue("ENTRY", "", i);
        entries.push_back(temp);
    }
}
void menu::draw()
{
    if(bIsVisible)
    {
        for(int i = 0; i < entries.size(); i++)
        {
            ofFill();
            if(mouseIsOn(mouseX, mouseY,entries[i].box))
            {
                ofSetColor(150,150,150,255);
            }
            else
            {
                ofSetColor(50,50,50,255);
            }
            ofRect(entries[i].box.x,entries[i].box.y,entries[i].box.width,entries[i].box.height);
            ofSetColor(255,255,255,255);
            ofDrawBitmapString(entries[i].text,entries[i].box.x + 3,entries[i].box.y + entries[i].box.height - 3);
        }

    }
}

bool menu::mouseIsOn(int _mouseX,int _mouseY,ofRectangle _box)
{
    if((_mouseX >= _box.x) && (_mouseX <= _box.x + _box.width) && (_mouseY >= _box.y) && (_mouseY <= _box.y + _box.height))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void menu::init()
{
    x = mouseX+15;
    y = mouseY+15;
    for(int i = 0; i < entries.size(); i++)
    {
        entries[i].box.x = x;
        entries[i].box.y = y + (i * 16);
        entries[i].box.width = 100;
        entries[i].box.height = 15;
    }
    bIsVisible = true;
}
void menu::close()
{
    bIsVisible = false;
}
