#include "dsCore.h"

//--------------------------------------------------------------
void dsCore::setup()
{
    cout << "setup started" << endl;
    ofBackground(80);
    XMLObjects.loadFile("objects.xml");
    XMLObjects.pushTag("OBJECTS", 0);
    ofAddListener(menu::Get()->newObjectEvent, this, &dsCore::createObject);
    cout << "setup finished" << endl;
}
//--------------------------------------------------------------
void dsCore::update()
{
}
//--------------------------------------------------------------
void dsCore::draw()
{
}

void dsCore::createObject(entry & args)
{
    for(int i = 0; i < XMLObjects.getNumTags("OBJECT"); i++)
    {
        if(args.name == XMLObjects.getAttribute("OBJECT","NAME", "", i))
        {
            printf("creating %s!\n", XMLObjects.getAttribute("OBJECT","NAME", "", i).c_str());
            printf("\ttype:\t%s!\n", XMLObjects.getAttribute("OBJECT","TYPE", "", i).c_str());
            object* temp = new object();
            temp->name = (string)XMLObjects.getAttribute("OBJECT","NAME", "", i);
            temp->type = (string)XMLObjects.getAttribute("OBJECT","TYPE", "", i);
            temp->x = menu::Get()->x;
            temp->y = menu::Get()->y;
            XMLObjects.pushTag("OBJECT",i);
            pin temp_pin;
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
            }
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

void dsCore::destroyObject(object* _obj)
{
    delete _obj;
}
//--------------------------------------------------------------
void dsCore::keyPressed(int key)
{
}
//--------------------------------------------------------------
void dsCore::keyReleased(int key)
{
}
//--------------------------------------------------------------
void dsCore::mouseMoved(int x, int y )
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
        menu::Get()->bMouseIsOnObject = true;
        cout << "true" << endl;
    }
    else
    {
        menu::Get()->bMouseIsOnObject = false;
        cout << "false" << endl;
    }
}
//--------------------------------------------------------------
void dsCore::mouseDragged(int x, int y, int button)
{
}
//--------------------------------------------------------------
void dsCore::mousePressed(int x, int y, int button)
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
void dsCore::mouseReleased(int x, int y, int button)
{
}
//--------------------------------------------------------------
void dsCore::windowResized(int w, int h)
{
}
//--------------------------------------------------------------
void dsCore::gotMessage(ofMessage msg)
{
}
//--------------------------------------------------------------
void dsCore::dragEvent(ofDragInfo dragInfo)
{
}
//--------------------------------------------------------------
void dsCore::exit()
{
    ofRemoveListener(menu::Get()->newObjectEvent, this, &dsCore::createObject);
}
