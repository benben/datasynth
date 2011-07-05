#ifndef EMPTYNODE_H
#define EMPTYNODE_H

#include "src/BaseNode.h"

namespace ds {

class EmptyNode : public BaseNode
{
  public:
    EmptyNode();
    ~EmptyNode();
    void process();
    void draw(ofEventArgs & args);
  protected:
  private:
};

}
#endif // EMPTYNODE_H
