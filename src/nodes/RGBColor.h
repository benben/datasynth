#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include "src/BaseNode.h"
namespace ds {

class RGBColor : public BaseNode
{
  public:
    RGBColor(int _ID, float _x, float _y, string _name);
    ~RGBColor();
    void process();
  protected:
  private:
};

}
#endif // RGBCOLOR_H
