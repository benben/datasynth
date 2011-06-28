#include "Core.h"
using namespace ds;

//--------------------------------------------------------------
void Core::setup()
{
    cout << "setup started" << endl;
    ofBackground(80);
    XMLObjects.loadFile("objects.xml");
    XMLObjects.pushTag("OBJECTS", 0);
    ofAddListener(Menu::Get()->newObjectEvent, this, &Core::createObject);
    cout << "setup finished" << endl;
}
//--------------------------------------------------------------
void Core::update()
{
}
//--------------------------------------------------------------
void Core::draw()
{
}
//--------------------------------------------------------------
void Core::createObject(entry & args)
{
    for(int i = 0; i < XMLObjects.getNumTags("OBJECT"); i++)
    {
        if(args.name == XMLObjects.getAttribute("OBJECT","NAME", "", i))
        {
            printf("creating %s!\n", XMLObjects.getAttribute("OBJECT","NAME", "", i).c_str());
            printf("\ttype:\t%s!\n", XMLObjects.getAttribute("OBJECT","TYPE", "", i).c_str());
            Object* temp = new Object();
            temp->name = (string)XMLObjects.getAttribute("OBJECT","NAME", "", i);
            temp->type = (string)XMLObjects.getAttribute("OBJECT","TYPE", "", i);
            temp->x = Menu::Get()->x;
            temp->y = Menu::Get()->y;
            XMLObjects.pushTag("OBJECT",i);
            /*Pin temp_pin;
            for(int j = 0; j < XMLObjects.getNumTags("INPUT"); j++)
            {
                printf("\tinput[%d]:\t%s\t(%s)\n", j, XMLObjects.getAttribute("INPUT","NAME", "", j).c_str(), XMLObjects.getAttribute("INPUT","TYPE", "", j).c_str());
                temp_pin.name = XMLObjects.getAttribute("INPUT","NAME", "", j);
                temp_pin.type = XMLObjects.getAttribute("INPUT","TYPE", "", j);
                temp->input.push_back(temp_pin);
            }
            for(int j = 0; j < XMLObjects.getNumTags("OUTPUT"); j++)
            {
                printf("\toutput[%d]:\t%s\t(%s)\n", j, XMLObjects.getAttribute("OUTPUT","NAME", "", j).c_str(), XMLObjects.getAttribute("OUTPUT","TYPE", "", j).c_str());
                temp_pin.name = XMLObjects.getAttribute("OUTPUT","NAME", "", j);
                temp_pin.type = XMLObjects.getAttribute("OUTPUT","TYPE", "", j);
                temp->output.push_back(temp_pin);
            }*/
            if(temp->output.size() >= temp->input.size())
            {
                temp->width = (temp->output.size() * 10) + 50;
            }
            else
            {
                temp->width = (temp->input.size() * 10) + 50;
            }
            temp->height = 30;
            objects.push_back(temp);
            printf("\n");
            XMLObjects.popTag();
        }
    }
}
//--------------------------------------------------------------
void Core::destroyObject(Object* _obj)
{
    delete _obj;
}
//--------------------------------------------------------------
void Core::keyPressed(int key)
{
}
//--------------------------------------------------------------
void Core::keyReleased(int key)
{
}
//--------------------------------------------------------------
void Core::mouseMoved(int x, int y )
{
    bool temp = false;
    //check if mouse is over an object
    for(int i = 0; i < objects.size(); i++)
    {
        if((x >= objects[i]->x) && (x <= objects[i]->x + objects[i]->width) && (y >= objects[i]->y) && (y <= objects[i]->y + objects[i]->height))
        {
            temp = true;
            break;
        }
        else
        {
            temp = false;
        }
    }
    if(temp)
    {
        Menu::Get()->bMouseIsOnObject = true;
    }
    else
    {
        Menu::Get()->bMouseIsOnObject = false;
    }
}
//--------------------------------------------------------------
void Core::mouseDragged(int x, int y, int button)
{
}
//--------------------------------------------------------------
void Core::mousePressed(int x, int y, int button)
{
    if(button == 2)
    {
        for(int i = 0; i < objects.size(); i++)
        {
            if((x >= objects[i]->x) && (x <= objects[i]->x + objects[i]->width) && (y >= objects[i]->y) && (y <= objects[i]->y + objects[i]->height))
            {
                destroyObject(objects[i]);
                objects.erase(objects.begin()+i);
                break;
            }
        }
    }
}
//--------------------------------------------------------------
void Core::mouseReleased(int x, int y, int button)
{
}
//--------------------------------------------------------------
void Core::windowResized(int w, int h)
{
}
//--------------------------------------------------------------
void Core::gotMessage(ofMessage msg)
{
}
//--------------------------------------------------------------
void Core::dragEvent(ofDragInfo dragInfo)
{
}
//--------------------------------------------------------------
void Core::exit()
{
    ofRemoveListener(Menu::Get()->newObjectEvent, this, &Core::createObject);
}
