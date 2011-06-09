#include "menu.h"

menu::menu()
{
    //ctor
}

menu::~menu()
{
    //dtor
}

void menu::init()
{
    bIsVisible = false;
    XML.loadFile("menu.xml");
    XML.pushTag("MENU", 0);
    bool bScan = true;

    while(bScan)
    {
        if(XML.getNumTags("ENTRY") != 0)
        {
            printf("%s\n", XML.getAttribute("ENTRY","NAME", "", 0).c_str());
            XML.pushTag("ENTRY", 0);
        }
        else
        {
            XML.popTag();
            if (XML.tagExists("ENTRY", 0))
            {
                XML.removeTag("ENTRY", 0);
            }
            else
            {
                bScan = false;
            }
        }
    }

    /*
    for(int i = 0; i < XmlEntries; i++)
    {
        entry temp;
        temp.text = XML.getAttribute("ENTRY","NAME", "", i);
        XML.pushTag("ENTRY", i);
        printf("%d\n", XML.getNumTags("ENTRY"));
        XML.popTag();
        entries.push_back(temp);
    } */
    ofAddListener(ofEvents.draw, this, &menu::draw);
    ofAddListener(ofEvents.mouseMoved, this, &menu::updateMouse);
    ofAddListener(ofEvents.mouseReleased, this, &menu::toggle);
}
void menu::draw(ofEventArgs & args)
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
void menu::toggle(ofMouseEventArgs & args)
{
    if(args.button == 2)
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
    else
    {
        bIsVisible = false;
    }
}
void menu::updateMouse(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}
