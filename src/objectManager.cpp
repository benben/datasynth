#include "objectManager.h"

objectManager::objectManager()
{
    myMenu = new menu();
    myMenu->init();
    ofAddListener(myMenu->newObjectEvent, this, &objectManager::createObject);
}

objectManager::~objectManager()
{
    //dtor
}

void objectManager::createObject(entry & args)
{
    printf("creating object!\n");
}
