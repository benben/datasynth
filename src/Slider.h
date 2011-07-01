#ifndef SLIDER_H
#define SLIDER_H

#include "src/Object.h"

class Slider
{
    public:
        Slider(float* _x , float* _y, string* name, double* _val);
        virtual ~Slider();
        void draw(ofEventArgs & args);
        void setValue(float mx, float my, bool bCheck);
        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);

        double* val;
        float min, max;
        string name;
        ofRectangle b;

        float * parentXPtr, * parentYPtr;
        string* namePtr;
    protected:
    private:
};

#endif // SLIDER_H
