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
            printf("\ttype:\t%s!\n", XMLObjects.getAttribute("OBJECT","TYPE", "", i).c_str());
            //object* temp = new object();
            //temp->name = XMLObjects.getAttribute("OBJECT","NAME", "", i);
            //temp->type = XMLObjects.getAttribute("OBJECT","TYPE", "", i);
            XMLObjects.pushTag("OBJECT",i);
            for(int j = 0; j < XMLObjects.getNumTags("INPUT"); j++)
            {
                printf("\tinput[%d]:\t%s\t(%s)\n", j, XMLObjects.getAttribute("INPUT","NAME", "", j).c_str(), XMLObjects.getAttribute("INPUT","TYPE", "", j).c_str());
            }
            for(int j = 0; j < XMLObjects.getNumTags("OUTPUT"); j++)
            {
                printf("\toutput[%d]:\t%s\t(%s)\n", j, XMLObjects.getAttribute("OUTPUT","NAME", "", j).c_str(), XMLObjects.getAttribute("OUTPUT","TYPE", "", j).c_str());
            }
            printf("\n");
            XMLObjects.popTag();
        }
    }
}
