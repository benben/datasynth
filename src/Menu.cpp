#include "Menu.h"

using namespace ds;

Menu::Menu()
{
    XMLObjects.loadFile("objects.xml");
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
            temp.name = XML.getAttribute("ENTRY","NAME", "", 0).c_str();
            if(XML.getAttribute("ENTRY","TYPE", "", 0) != "")
            {
                temp.handler = XML.getAttribute("ENTRY","TYPE", "", 0).c_str();
            }
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
        temp.name = XMLObjects.getAttribute("OBJECT","NAME", "", i).c_str();
        temp.type = XMLObjects.getAttribute("OBJECT","TYPE", "", i).c_str();
        temp.handler = "CreateNode";
        temp.level = 1;
        temp.box.width = 100;
        temp.box.height = 15;
        temp.bIsVisible = false;
        entries.push_back(temp);
    }
    ofRegisterMouseEvents(this);
    ofAddListener(ofxFensterManager::get()->getPrimaryWindow()->events.draw, this, &Menu::draw);
    bMouseIsOnNode = false;
}

Menu::~Menu()
{
    ofUnregisterMouseEvents(this);
    ofRemoveListener(ofxFensterManager::get()->getPrimaryWindow()->events.draw, this, &Menu::draw);
}

void Menu::draw(ofEventArgs & args)
{
    int k = 0;
    for(unsigned int i = 0; i < entries.size(); i++)
    {
        if(entries[i].bIsVisible)
        {
            ofFill();
            if(entries[i].box.inside(mouseX, mouseY))
            {
                for(unsigned int j = 0; j < entries.size(); j++)
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

void Menu::mouseMoved(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}

void Menu::mousePressed(ofMouseEventArgs & args)
{
    //cout << "pressed (" << args.button << "," << x << "," << y << ")" << " bMouseIsOnNode: " << bMouseIsOnNode << endl;
}

void Menu::mouseDragged(ofMouseEventArgs & args)
{
}

void Menu::mouseReleased(ofMouseEventArgs & args)
{
    //cout << "released (" << args.button << "," << x << "," << y << ")" << " bMouseIsOnNode: " << bMouseIsOnNode << endl;
    if(!bMouseIsOnNode)
    {
        if(args.button == 0)
        {
            for(unsigned int i = 0; i < entries.size(); i++)
            {
                if(entries[i].box.inside(mouseX, mouseY) && entries[i].bIsVisible)
                {
                    menuEventType temp;
                    temp.handler = entries[i].handler;
                    temp.value = entries[i].name;
                    temp.valueType = entries[i].type;
                    ofNotifyEvent(menuEvent,temp,this);
                }
            }
        }
        //toggle
        if(args.button == 2)
        {
            x = args.x;
            y = args.y;
            int level = 0;
            for(unsigned int i = 0; i < entries.size(); i++)
            {
                //make all visible entries invisible first
                entries[i].bIsVisible = false;
                //move only the entries of the root level to the mouse pos and make them visible
                if(entries[i].parent == 0)
                {

                    entries[i].box.x = x;
                    entries[i].box.y = y + (level * (entries[i].box.height +1));
                    entries[i].bIsVisible = true;
                    level++;
                }
            }
        }
        else
        {
            for(unsigned int i = 0; i < entries.size(); i++)
            {
                entries[i].bIsVisible = false;
            }
        }
    }
}
