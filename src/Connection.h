#ifndef CONNECTION_H
#define CONNECTION_H

#include "src/Pin.h"

namespace ds {

class Connection
{
    public:
        Connection(Pin * _out, Pin * _in);
        ~Connection();
        Pin * in;
        Pin * out;
        void process();
        void draw(ofEventArgs & args);
        void setInvalid(int & args);

        float mouseX, mouseY;

        bool bIsInvalid;

        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);
        bool mouseIsOn();
    protected:
    private:
};

}
#endif // CONNECTION_H
