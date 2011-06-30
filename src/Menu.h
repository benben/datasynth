#ifndef MENU_H
#define MENU_H

#include "ofxXmlSettings.h"
#include "ofMain.h"
#include "ofEvents.h"
#include "src/Singleton.h"

namespace ds {

struct entry
{
    int id;
    int parent;
    int level;
    string name;
    ofRectangle box;
    bool bIsVisible;
};

class Menu : public TSingleton<Menu>
{
    public:
        Menu();
        virtual ~Menu();
        void draw(ofEventArgs & args);
        void click(ofMouseEventArgs & args);
        void updateMouse(ofMouseEventArgs & args);

        bool mouseIsOn(ofRectangle _box);
        bool bMouseIsOnObject;

        ofxXmlSettings XML;
        ofxXmlSettings XMLObjects;
        vector <entry> entries;
        int x, y, mouseX, mouseY;

        ofEvent<entry> newObjectEvent;
    protected:
    private:
};

}

#endif // MENU_H
