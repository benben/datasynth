#include "Multiply.h"
using namespace ds;

Multiply::Multiply()
{
    input.push_back(new Pin(0.0));
    input.push_back(new Pin(0.0));
    output.push_back(new Pin(0.0));
}

Multiply::~Multiply()
{
    basedelete();
}

void Multiply::process()
{
    cout << "process from Multiply()\n";
    output[0]->value = boost::get<double>(input[0]->value) * boost::get<double>(input[1]->value);
    cout << "output pin: " << output[0]->value << endl;
}
