#ifndef LESSTHAN_H
#define LESSTHAN_H

#include "src/BaseNode.h"
namespace ds {

class LessThan : public BaseNode
{
  public:
    LessThan(int _ID, float _x, float _y, string _name);
    ~LessThan();
    void process();
  protected:
  private:
};

}
#endif // LESSTHAN_H
