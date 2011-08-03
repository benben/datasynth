#ifndef EMPTYNODE_H
#define EMPTYNODE_H

#include "src/BaseNode.h"

namespace ds {

class EmptyNode : public BaseNode
{
  public:
    EmptyNode(int _ID, float _x, float _y, string _name);
    ~EmptyNode();
    void process();
  protected:
  private:
};

}
#endif // EMPTYNODE_H
