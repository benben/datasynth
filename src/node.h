#ifndef NODE_H
#define NODE_H

#include <ofMain.h>


class node : public ofRectangle
{
    public:
        node();
        virtual ~node();
        void draw();
        vector <int> inputs;
        vector <int> outputs;
        void process();
    protected:
    private:
};

#endif // NODE_H
