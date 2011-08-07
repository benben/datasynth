#ifndef CONSTANT_H
#define CONSTANT_H

#include "src/BaseNode.h"
#include "src/controls/Slider.h"
#include "src/controls/FloatInput.h"
#include "boost/shared_ptr.hpp"

typedef boost::shared_ptr<ds::FloatInput> FloatInputPtr;
typedef boost::shared_ptr<ds::Slider> SliderPtr;

namespace ds {

class Constant : public BaseNode
{
  public:
    Constant(int _ID, float _x, float _y, string _name);
    ~Constant();
    void process();
    void draw();

    SliderPtr slider;
    FloatInputPtr floatinput;

    float value;

    string getValueAsString();
    void setValueFromString(string _val);
  protected:
  private:
};

}
#endif // CONSTANT_H
