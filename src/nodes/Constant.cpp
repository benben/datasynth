#include "Constant.h"
using namespace ds;

Constant::Constant(float _var)
{
  output.push_back(_var);
}

Constant::~Constant()
{
  cout << "process from Constant()\n";
  cout << "output pin: " << output[0] << endl;
}

void Constant::process()
{
  cout << "process from Constant()\n";
  cout << "output pin: " << output[0] << endl;
}
