#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "ofxXmlSettings.h"
#include "ofEvents.h"
#include "src/singleton.h"
#include "src/menu.h"
#include "src/object.h"

class objectManager : public TSingleton<objectManager>
{
    public:
        objectManager();
        virtual ~objectManager();
        void init();
        void createObject(entry & args);
        void destroyObject(object* _obj);
        void click(ofMouseEventArgs & args);
        void updateMouse(ofMouseEventArgs & args);

        vector <object*> objects;
        ofxXmlSettings XMLObjects;
    protected:
    private:
};

#endif // OBJECTMANAGER_H
