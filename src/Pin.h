#ifndef PIN_H
#define PIN_H

#include "ofMain.h"
#include "boost/variant.hpp"
#include "boost/shared_ptr.hpp"

typedef boost::variant<float, string, ofColor> Type;

struct SpreadStruct
{
    string name;
    vector<Type> data;
};

typedef boost::shared_ptr<SpreadStruct> Spread;

namespace ds {

class Pin : public ofRectangle
{
    public:
        Pin(Spread _value, ofColor _color, int _maxConnections=0);
        virtual ~Pin();

        Spread value;

        int connections;
        int maxConnections;
        bool isFree();
        void setInvalid();
        bool bIsInvalid;

        ofColor color;

        void setValue(Spread _value);

        float mouseX, mouseY;
        bool bIsActive;
        void draw(float x, float y);
        void addConnection();
        void removeConnection();
        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);
    protected:
    private:
};

}

#endif // PIN_H
