#include "Multiply.h"
using namespace ds;

Multiply::Multiply()
{
  input.push_back(0.0);
  input.push_back(0.0);
  output.push_back(0.0);
}

Multiply::~Multiply()
{
}

void Multiply::process()
{
  cout << "process from Multiply()\n";
  output[0] = boost::get<double>(input[0]) * boost::get<double>(input[1]);
  cout << "output pin: " << output[0] << endl;
}
