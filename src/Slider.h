#ifndef SLIDER_H
#define SLIDER_H

#include "src/BaseNode.h"

class Slider
{
    public:
        Slider(float* _x, float* _y, string* _name, double* _val);
        ~Slider();
        void draw(ofEventArgs & args);
        void setValue(float mx, float my, bool bCheck);
        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);

        double* val;
        float* x, * y;
        float min, max;
        string* name;
        ofRectangle b;

    protected:
    private:
};

#endif // SLIDER_H
