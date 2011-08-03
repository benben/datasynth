#ifndef ADD_H
#define ADD_H

#include "src/BaseNode.h"
namespace ds {

class Add : public BaseNode
{
  public:
    Add(int _ID, float _x, float _y, string _name);
    ~Add();
    void process();
  protected:
  private:
};

}
#endif // ADD_H
