#ifndef CONNECTION_H
#define CONNECTION_H

#include "src/Pin.h"
#include "src/BaseNode.h"
#include "ofxFensterManager.h"

typedef boost::shared_ptr<ds::BaseNode> NodePtr;

namespace ds {

class Connection
{
    public:
        Connection(NodePtr _outNode, int _outPinID, NodePtr _inNodeID, int _inPinID);
        ~Connection();
        NodePtr inNode;
        NodePtr outNode;
        int outPinID, inPinID;
        void setInvalid(int & args);
        void process(int & args);
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
