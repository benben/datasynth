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
            temp->width = 150;
            temp->height = 30;
            objects.push_back(temp);
            printf("\n");
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
        //cout << "processing connections..." << endl;
        for(unsigned int i = 0; i < connections.size(); i++)
        {
            if(connections[i]->bIsInvalid)
            {
                delete connections[i];
                connections.erase(connections.begin()+i);
            }
            else
            {
                connections[i]->process();
            }
        }
        //cout << "processing nodes..." << endl;
        BOOST_FOREACH(ObjectPtr node, objects)
            node->process();
        //cout << "...finished!" << endl;
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
            if(objects[i]->inside(x,y))
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
    Pin* in=0;
    Pin* out=0;
    for(unsigned int i = 0; i < objects.size(); i++)
    {
        for(unsigned int j = 0; j < objects[i]->input.size(); j++)
        {
            if(objects[i]->input[j]->bIsActive)
            {
                cout << "input active: " << i << " " << j << endl;
                in = objects[i]->input[j];
            }
        }
        for(unsigned int j = 0; j < objects[i]->output.size(); j++)
        {
            if(objects[i]->output[j]->bIsActive)
            {
                cout << "output active: " << i << " " << j << endl;
                out = objects[i]->output[j];
            }
        }
    }
    if(in != NULL && out != NULL)
    {
        cout << "make connection" << endl;
        connections.push_back(new Connection(out, in));
    }
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
