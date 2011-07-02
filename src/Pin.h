#ifndef PIN_H
#define PIN_H

#include "ofMain.h"
#include "boost/variant.hpp"

typedef boost::variant<int, float, double> Type;

namespace ds {

class Pin : public ofRectangle
{
    public:
        Pin(Type _value);
        virtual ~Pin();
        Type value;

        float mouseX, mouseY;
        bool bMouseStartsOn, bMouseIsOn, bMouseEndsOn, bIsActive;
        void draw(float x, float y);
        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);
    protected:
    private:
};

}

#endif // PIN_H
