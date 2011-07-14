#ifndef OUTBOX_H
#define OUTBOX_H

#include "src/BaseNode.h"

namespace ds {

class OutBox : public BaseNode
{
  public:
    OutBox(float _x, float _y, string _name);
    ~OutBox();
    void process();
    void draw();
  protected:
  private:
};

}
#endif // OUTBOX_H
