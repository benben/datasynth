#ifndef UNIQUE_H
#define UNIQUE_H

#include "src/BaseNode.h"
namespace ds {

class Unique : public BaseNode
{
  public:
    Unique(int _ID, float _x, float _y, string _name);
    ~Unique();
    void process();
  protected:
  private:
};

}
#endif // UNIQUE_H
