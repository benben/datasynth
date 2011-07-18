#ifndef MIN_H
#define MIN_H

#include "src/BaseNode.h"
namespace ds {

class Min : public BaseNode
{
  public:
    Min(float _x, float _y, string _name);
    ~Min();
    void process();
  protected:
  private:
};

}
#endif // MIN_H
