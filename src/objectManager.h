#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "ofEvents.h"
#include "src/object.h"
#include "src/menu.h"

class objectManager
{
    public:
        objectManager();
        virtual ~objectManager();
        void createObject(entry & args);
        vector <object> objects;

        menu* myMenu;
    protected:
    private:
};

#endif // OBJECTMANAGER_H
