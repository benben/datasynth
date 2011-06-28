#ifndef OBJECT_H
#define OBJECT_H

#include "ofMain.h"
#include "boost/variant.hpp"

typedef boost::variant<float, int> Type;

namespace ds {

class Object : public ofRectangle
{
    public:
        Object(const Object&); //prevent copying
        Object& operator=(const Object&);

        Object();
        virtual ~Object();

        string name;
        string type;

        vector<Type> input;
        vector<Type> output;
        virtual void process();
        virtual void draw(ofEventArgs & args);
    protected:
    private:
};

}
#endif // OBJECT_H
