#ifndef OBJECT_H
#define OBJECT_H

#include <ofMain.h>


class object : public ofRectangle
{
    public:
        object();
        virtual ~object();
        void draw();
        vector <int> input;
        vector <int> output;
        void process();
    protected:
    private:
};

#endif // OBJECT_H
