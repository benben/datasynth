#ifndef EMPTYNODE_H
#define EMPTYNODE_H

#include "src/Object.h"

namespace ds {

class EmptyNode : public Object
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
