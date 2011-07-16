#ifndef BASENODE_H
#define BASENODE_H

#include "ofxFensterManager.h"
#include "src/Pin.h"
#include <boost/foreach.hpp>

namespace ds {

class BaseNode : public ofRectangle
{
    public:
        BaseNode(const BaseNode&); //prevent copying
        BaseNode& operator=(const BaseNode&);

        BaseNode();
        virtual ~BaseNode();
        void basedelete();

        string name;
        string type;

        bool bIsInvalid;
        void setInvalid();

        vector<Pin*> input;
        vector<Pin*> output;
        virtual void init();
        virtual void process();
        virtual void basedraw();
        virtual void draw();

        ofColor color;

        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);
        float mouseX, mouseY;
        bool bIsActive;
        bool bValueIsSaveable;

        virtual string getValueAsString();
        virtual void setValueFromString(string _val);
    protected:
    private:
};

}
#endif // BASENODE_H
