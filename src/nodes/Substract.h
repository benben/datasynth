#ifndef SUBSTRACT_H
#define SUBSTRACT_H

#include "src/BaseNode.h"
namespace ds {

class Substract : public BaseNode
{
  public:
    Substract(int _ID, float _x, float _y, string _name);
    ~Substract();
    void process();
  protected:
  private:
};

}
#endif // SUBSTRACT_H
