#ifndef MAX_H
#define MAX_H

#include "src/BaseNode.h"
namespace ds {

class Max : public BaseNode
{
  public:
    Max(int _ID, float _x, float _y, string _name);
    ~Max();
    void process();
  protected:
  private:
};

}
#endif // MAX_H
