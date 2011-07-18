#ifndef SLIDER_H
#define SLIDER_H

#include "src/BaseNode.h"

namespace ds

{

class Slider
{
    public:
        Slider(float* _x, float* _y, string _name, float* _val, bool* _bIsNodeActive);
        ~Slider();
        void draw();
        void setValue(float mx, float my, bool bCheck);
        void setValue(float _val);
        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);

        float* val;
        float* x, * y;
        float min, max;
        string name;
        ofRectangle b;

        bool bIsActive;
        bool* bIsNodeActive;

    protected:
    private:
};

}

#endif // SLIDER_H
