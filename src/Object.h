#ifndef OBJECT_H
#define OBJECT_H

#include "src/Pin.h"

namespace ds {

class Object : public ofRectangle
{
    public:
        Object(const Object&); //prevent copying
        Object& operator=(const Object&);

        Object();
        virtual ~Object();

        string name;
        string type;

        vector<Pin*> input;
        vector<Pin*> output;
        virtual void process();
        virtual void basedraw(ofEventArgs & args);
        virtual void draw(ofEventArgs & args);

        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);
        float mouseX, mouseY;
    protected:
    private:
};

}
#endif // OBJECT_H
