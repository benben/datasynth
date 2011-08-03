#ifndef MODULO_H
#define MODULO_H

#include "src/BaseNode.h"
namespace ds {

class Modulo : public BaseNode
{
  public:
    Modulo(int _ID, float _x, float _y, string _name);
    ~Modulo();
    void process();
  protected:
  private:
};

}
#endif // MODULO_H
