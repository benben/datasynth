#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "src/BaseNode.h"
namespace ds {

class Multiply : public BaseNode
{
  public:
    Multiply(float _x, float _y, string _name);
    ~Multiply();
    void process();
  protected:
  private:
};

}
#endif // MULTIPLY_H
