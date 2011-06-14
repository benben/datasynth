#ifndef OBJECT_H
#define OBJECT_H

#include <ofMain.h>
#include "ofEvents.h"
#include "src/menu.h"

struct pin
{
    string name;
    string type;
};

class object : public ofRectangle
{
    public:
        object();
        virtual ~object();
        void draw(ofEventArgs & args);

        string name;
        string type;

        vector <pin> input;
        vector <pin> output;
        void process();
    protected:
    private:
};

#endif // OBJECT_H
