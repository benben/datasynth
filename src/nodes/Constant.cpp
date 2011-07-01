#include "Constant.h"
using namespace ds;

Constant::Constant()
{
    output.push_back(0.0);
    //remove this stupid reference to the name, since this is set only once (when factory is working with init vars... :) )
    slider = new Slider(&x, &y, &name, &boost::get<double>(output[0]));
}

Constant::~Constant()
{
}

void Constant::process()
{
    cout << "process from Constant()\n";
    cout << "output pin: " << output[0] << endl;
}
