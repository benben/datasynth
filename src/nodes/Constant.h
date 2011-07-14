#ifndef CONSTANT_H
#define CONSTANT_H

#include "src/BaseNode.h"
#include "src/Slider.h"
#include "boost/shared_ptr.hpp"

typedef boost::shared_ptr<Slider> SliderPtr;

namespace ds {

class Constant : public BaseNode
{
  public:
    Constant(float _x, float _y, string _name);
    ~Constant();
    SliderPtr slider;
    void init();
    void process();
    void draw();
  protected:
  private:
};

}
#endif // CONSTANT_H
