#ifndef CONNECTION_H
#define CONNECTION_H

#include "src/Pin.h"
#include "ofxFensterManager.h"

namespace ds {

class Connection
{
    public:
        Connection(Pin * _out, int _outNodeID, int _outPinID, Pin * _in, int _inNodeID, int _inPinID);
        ~Connection();
        Pin * in;
        Pin * out;
        int outNodeID, outPinID, inNodeID, inPinID;
        void process();
        void draw();

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
