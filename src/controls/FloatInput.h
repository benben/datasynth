#ifndef FLOATINPUT_H
#define FLOATINPUT_H

#include <boost/lexical_cast.hpp>
#include "src/BaseNode.h"

namespace ds
{

class FloatInput
{
    public:
        FloatInput(float* _x, float* _y, string _name, float* _value, bool* _bProcessed,  bool* _bIsNodeActive);
        ~FloatInput();
        void draw();
        void setValue(string _val);
        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);

        virtual void keyPressed(ofKeyEventArgs & args);
        virtual void keyReleased(ofKeyEventArgs & args);

        string name;
        float* value;
        float* x, * y;
        ofRectangle b;

        bool bIsActive;
        bool* bIsNodeActive;
        bool* bProcessed;

        int mouseX, mouseY;

        string input;
    protected:
    private:
};

}

#endif // FLOATINPUT_H
