#ifndef PIN_H
#define PIN_H

#include "ofMain.h"
#include "boost/variant.hpp"

struct Spread
{
    string name;
    vector<double> data;

    Spread operator<<(Spread const& _s)
    {
        return _s;
    }
};

typedef boost::variant<float> Type;

namespace ds {

class Pin : public ofRectangle
{
    public:
        Pin(Type _value, int _maxConnections=0);
        virtual ~Pin();

        Type value;

        int connections;
        int maxConnections;
        bool isFree();
        void setInvalid();

        ofEvent<int> deleteEvent;

        float mouseX, mouseY;
        bool bMouseStartsOn, bMouseIsOn, bMouseEndsOn, bIsActive;
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
