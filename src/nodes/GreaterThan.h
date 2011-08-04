#ifndef GREATERTHAN_H
#define GREATERTHAN_H

#include "src/BaseNode.h"
namespace ds {

class GreaterThan : public BaseNode
{
  public:
    GreaterThan(int _ID, float _x, float _y, string _name);
    ~GreaterThan();
    void process();
  protected:
  private:
};

}
#endif // GREATERTHAN_H
