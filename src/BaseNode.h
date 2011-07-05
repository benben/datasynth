#ifndef BASENODE_H
#define BASENODE_H

#include "src/Pin.h"
#include <boost/foreach.hpp>

namespace ds {

class BaseNode : public ofRectangle
{
    public:
        BaseNode(const BaseNode&); //prevent copying
        BaseNode& operator=(const BaseNode&);

        BaseNode();
        //BaseNode(float _x, float _y, string _name);
        virtual ~BaseNode();
        void basedelete();

        string name;

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
#endif // BASENODE_H
