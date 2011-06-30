#include "Constant.h"
using namespace ds;

Constant::Constant()
{
  output.push_back(0.0);
  slider.init(&boost::get<double>(output[0]));
}

Constant::~Constant()
{
}

void Constant::process()
{
  cout << "process from Constant()\n";
  cout << "output pin: " << output[0] << endl;
}
