#include "Constant.h"
using namespace ds;

Constant::Constant()
{
  output.push_back(0);
}

Constant::~Constant()
{
}

void Constant::process()
{
  cout << "process from Constant()\n";
  cout << "output pin: " << output[0] << endl;
}
