#ifndef PIN_H
#define PIN_H

#include "ofMain.h"
#include "boost/variant.hpp"

typedef boost::variant<int, float, double> Type;

namespace ds {

class Pin : public ofRectangle
{
    public:
        Pin(Type _value);
        virtual ~Pin();
        Type value;
    protected:
    private:
};

}

#endif // PIN_H
