#ifndef CONSTANT_H
#define CONSTANT_H

#include "src/BaseNode.h"
#include "src/controls/Slider.h"
#include "src/controls/TextInput.h"
#include "boost/shared_ptr.hpp"

typedef boost::shared_ptr<ds::TextInput> TextInputPtr;
typedef boost::shared_ptr<ds::Slider> SliderPtr;

namespace ds {

class Constant : public BaseNode
{
  public:
    Constant(float _x, float _y, string _name);
    ~Constant();
    void init();
    void process();
    void draw();

    SliderPtr slider;
    TextInputPtr textinput;

    float value;

    string getValueAsString();
    void setValueFromString(string _val);
  protected:
  private:
};

}
#endif // CONSTANT_H
