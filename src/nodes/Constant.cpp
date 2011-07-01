#include "Constant.h"
using namespace ds;

Constant::Constant()
{
    output.push_back(new Pin(0.0));
    //TODO: remove this stupid reference to the name, since this is set only once (when factory is working with init vars... :) )
    //boost::scoped_ptr<Shoe> x(new Shoe);
    //boost::scoped_ptr<Slider> slider(new Slider(&x, &y, &name));
}

Constant::~Constant()
{
}

void Constant::process()
{
    cout << "process from Constant()\n";
    cout << "output pin: " << output[0]->value << endl;
}

void Constant::draw(ofEventArgs & args)
{
    //leave this if you wanna draw the basic shapes
    basedraw(args);
}
