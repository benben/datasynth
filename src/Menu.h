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
    string type;
    string handler;
    ofRectangle box;
    bool bIsVisible;
};

struct menuEventType
{
    string handler;
    string value;
    string valueType;
};

class Menu : public TSingleton<Menu>
{
    public:
        Menu();
        virtual ~Menu();
        void draw(ofEventArgs & args);
        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);

        bool bMouseIsOnNode;

        ofxXmlSettings XML;
        ofxXmlSettings XMLObjects;
        vector <entry> entries;
        int x, y, mouseX, mouseY;

        ofEvent<menuEventType> menuEvent;
    protected:
    private:
};

}

#endif // MENU_H
