#ifndef CONSTANT_H
#define CONSTANT_H

#include "src/Object.h"
namespace ds {

class Constant : public Object
{
  public:
    Constant();
    ~Constant();
    void process();
  protected:
  private:
};

}
#endif // CONSTANT_H
