#ifndef DIVIDE_H
#define DIVIDE_H

#include "src/BaseNode.h"
namespace ds {

class Divide : public BaseNode
{
  public:
    Divide(float _x, float _y, string _name);
    ~Divide();
    void process();
  protected:
  private:
};

}
#endif // DIVIDE_H
