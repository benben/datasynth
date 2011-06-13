#include "objectManager.h"

objectManager::objectManager()
{
    //ctor
}

objectManager::~objectManager()
{
    //dtor
}

void objectManager::init()
{
    XMLObjects.loadFile("objects.xml");
    XMLObjects.pushTag("OBJECTS", 0);
    myMenu = new menu();
    myMenu->init();
    ofAddListener(myMenu->newObjectEvent, this, &objectManager::createObject);
}

void objectManager::createObject(entry & args)
{

    for(int i = 0; i < XMLObjects.getNumTags("OBJECT"); i++)
    {
        if(args.name == XMLObjects.getAttribute("OBJECT","NAME", "", i))
        {
            printf("creating %s!\n", XMLObjects.getAttribute("OBJECT","NAME", "", i).c_str());
            printf("type %s!\n", XMLObjects.getAttribute("OBJECT","TYPE", "", i).c_str());
        }
    }
}
