#ifndef CONSTANT_H
#define CONSTANT_H

#include "src/Object.h"
#include "src/Slider.h"

namespace ds {

class Constant : public Object
{
  public:
    Constant();
    ~Constant();
    Slider slider;
    void process();
  protected:
  private:
};

}
#endif // CONSTANT_H