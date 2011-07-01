#ifndef OBJECT_H
#define OBJECT_H

#include "ofMain.h"
#include "boost/variant.hpp"

typedef boost::variant<int, float, double> Type;

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

        vector<Type> input;
        vector<Type> output;
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
