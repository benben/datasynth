#ifndef MENU_H
#define MENU_H

#include "ofxXmlSettings.h"

struct entry
{
  string text;
  ofRectangle box;
};

class menu
{
    public:
        menu();
        virtual ~menu();
        void setup();
        void draw();
        void init();
        void close();

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
