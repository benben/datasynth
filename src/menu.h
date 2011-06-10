#ifndef MENU_H
#define MENU_H

#include "ofxXmlSettings.h"
#include "ofMain.h"
#include "ofEvents.h"

struct entry
{
    int id;
    int parent;
    string name;
    ofRectangle box;
};

class menu
{
    public:
        menu();
        virtual ~menu();
        void init();
        void draw(ofEventArgs & args);
        void toggle(ofMouseEventArgs & args);
        void updateMouse(ofMouseEventArgs & args);

        bool mouseIsOn(int _mouseX, int _mouseY, ofRectangle _box);

        ofxXmlSettings XML;
        int XmlEntries;
        vector <entry> entries;
        bool bIsVisible;
        int x, y, mouseX, mouseY;
    protected:
    private:
};

#endif // MENU_H
