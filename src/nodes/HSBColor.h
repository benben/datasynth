#ifndef HSBCOLOR_H
#define HSBCOLOR_H

#include "src/BaseNode.h"
namespace ds {

class HSBColor : public BaseNode
{
  public:
    HSBColor(int _ID, float _x, float _y, string _name);
    ~HSBColor();
    void process();
  protected:
  private:
};

}
#endif // HSBCOLOR_H
