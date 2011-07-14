#ifndef EMPTYNODE_H
#define EMPTYNODE_H

#include "src/BaseNode.h"

namespace ds {

class EmptyNode : public BaseNode
{
  public:
    EmptyNode(float _x, float _y, string _name);
    ~EmptyNode();
    void process();
    void draw();
  protected:
  private:
};

}
#endif // EMPTYNODE_H
