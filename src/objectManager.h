#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "ofxXmlSettings.h"
#include "ofEvents.h"
#include "src/object.h"
#include "src/menu.h"

class objectManager
{
    public:
        objectManager();
        virtual ~objectManager();
        void init();
        void createObject(entry & args);
        vector <object> objects;

        menu* myMenu;
        ofxXmlSettings XMLObjects;
    protected:
    private:
};

#endif // OBJECTMANAGER_H
