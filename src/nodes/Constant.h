#ifndef CONSTANT_H
#define CONSTANT_H

#include "src/Object.h"
#include "src/Slider.h"
#include <boost/scoped_ptr.hpp>

namespace ds {

class Constant : public Object
{
  public:
    Constant();
    ~Constant();
    boost::scoped_ptr<Slider> slider;
    void process();
    void draw(ofEventArgs & args);
  protected:
  private:
};

}
#endif // CONSTANT_H
