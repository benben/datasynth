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

            //create objects here
            ObjectPtr temp = factory(XMLObjects.getAttribute("OBJECT","NAME", "", i).c_str());

            temp->name = (string)XMLObjects.getAttribute("OBJECT","NAME", "", i);
            temp->type = (string)XMLObjects.getAttribute("OBJECT","TYPE", "", i);
            temp->x = Menu::Get()->x;
            temp->y = Menu::Get()->y;
            XMLObjects.pushTag("OBJECT",i);

            /*if(temp->output.size() >= temp->input.size())
            {
                temp->width = (temp->output.size() * 10) + 50;
            }
            else
            {
                temp->width = (temp->input.size() * 10) + 50;
            } */
            temp->width = 150;
            temp->height = 30;
            objects.push_back(temp);
            printf("\n");
            XMLObjects.popTag();
        }
    }
}
//--------------------------------------------------------------
void Core::keyPressed(int key)
{
}
//--------------------------------------------------------------
void Core::keyReleased(int key)
{
    if (key == ' ')
    {
        cout << "processing..." << endl;
        BOOST_FOREACH(ObjectPtr node, objects)
            node->process();
        cout << "...finished!" << endl;
    }
}
//--------------------------------------------------------------
void Core::mouseMoved(int x, int y )
{
    bool temp = false;
    //check if mouse is over an object
    for(unsigned int i = 0; i < objects.size(); i++)
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
        for(unsigned int i = 0; i < objects.size(); i++)
        {
            if((x >= objects[i]->x) && (x <= objects[i]->x + objects[i]->width) && (y >= objects[i]->y) && (y <= objects[i]->y + objects[i]->height))
            {
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
