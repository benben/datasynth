#include "menu.h"

menu::menu()
{
    XMLObjects.loadFile("objects.xml");
}

menu::~menu()
{
    //dtor
}

void menu::init()
{
    XML.loadFile("menu.xml");
    XML.pushTag("MENU", 0);
    bool bScan = true;
    int id = 0;
    vector <int> parents;
    int createId = 0;

    while(bScan)
    {
        if(XML.getNumTags("ENTRY") != 0)
        {
            id++;
            entry temp;
            temp.id = id;
            temp.name = XML.getAttribute("ENTRY","NAME", "", 0);
            //get the entry id for creating objects
            if(temp.name == "Create")
            {
                createId = temp.id;
            }
            parents.push_back(id);
            temp.parent = parents[parents.size() - 2];
            temp.level = XML.getPushLevel() - 1;
            temp.box.width = 100;
            temp.box.height = 15;
            temp.bIsVisible = false;
            //printf("%d - %d - %d - %s\n", temp.id, parents[parents.size() - 2], temp.level, temp.name.c_str());
            entries.push_back(temp);
            XML.pushTag("ENTRY", 0);
        }
        else
        {
            XML.popTag();
            parents.pop_back();
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
    XMLObjects.pushTag("OBJECTS", 0);
    for(int i = 0; i < XMLObjects.getNumTags("OBJECT"); i++)
    {
        entry temp;
        temp.parent = createId;
        temp.name = XMLObjects.getAttribute("OBJECT","NAME", "", i);
        temp.level = 1;
        temp.box.width = 100;
        temp.box.height = 15;
        temp.bIsVisible = false;
        entries.push_back(temp);
    }
    ofAddListener(ofEvents.draw, this, &menu::draw);
    ofAddListener(ofEvents.mouseMoved, this, &menu::updateMouse);
    ofAddListener(ofEvents.mouseDragged, this, &menu::updateMouse);
    ofAddListener(ofEvents.mouseReleased, this, &menu::click);
}
void menu::click(ofMouseEventArgs & args)
{
    if(args.button == 0)
    {
        for(int i = 0; i < entries.size(); i++)
        {
            if(mouseIsOn(entries[i].box) && entries[i].bIsVisible)
            {
                for(int j = 0; j < XMLObjects.getNumTags("OBJECT"); j++)
                {
                    if(entries[i].name == XMLObjects.getAttribute("OBJECT","NAME", "", j))
                    {
                        //printf("try to create object %s...\n",entries[i].name.c_str());
                        ofNotifyEvent(newObjectEvent,entries[i],this);
                    }
                }
            }
        }
    }
    //toggle
    if(args.button == 2)
    {
        x = mouseX;
        y = mouseY;
        int j = 0;
        for(int i = 0; i < entries.size(); i++)
        {
            //make all visible entries invisible first
            entries[i].bIsVisible = false;
            //move only the entries of the root level to the mouse pos and make them visible
            if(entries[i].parent == 0)
            {
                entries[i].box.x = x;
                entries[i].box.y = y + (j * (entries[i].box.height +1));
                entries[i].bIsVisible = true;
                j++;
            }
        }
    }
    else
    {
        for(int i = 0; i < entries.size(); i++)
        {
            entries[i].bIsVisible = false;
        }
    }
}
void menu::draw(ofEventArgs & args)
{
    int k = 0;
    for(int i = 0; i < entries.size(); i++)
    {
        if(entries[i].bIsVisible)
        {
            ofFill();
            if(mouseIsOn(entries[i].box))
            {
                for(int j = 0; j < entries.size(); j++)
                {
                    if(entries[j].parent == entries[i].id)
                    {
                        entries[j].box.x = entries[i].box.x + entries[i].box.width + 1;
                        entries[j].box.y = entries[i].box.y + (k * (entries[i].box.height +1));
                        k++;
                        entries[j].bIsVisible = true;
                    }
                    else
                    {
                        if(entries[j].level > entries[i].level)
                        {
                            entries[j].bIsVisible = false;
                        }
                    }
                }
                k = 0;
                ofSetColor(150,150,150,255);
            }
            else
            {
                ofSetColor(50,50,50,255);
            }
            ofRect(entries[i].box.x,entries[i].box.y,entries[i].box.width,entries[i].box.height);
            ofSetColor(255,255,255,255);
            ofDrawBitmapString(entries[i].name,entries[i].box.x + 3,entries[i].box.y + entries[i].box.height - 3);
        }
    }
}

bool menu::mouseIsOn(ofRectangle _box)
{
    if((mouseX >= _box.x) && (mouseX <= _box.x + _box.width) && (mouseY >= _box.y) && (mouseY <= _box.y + _box.height))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void menu::updateMouse(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}
