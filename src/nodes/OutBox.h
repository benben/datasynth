#ifndef OUTBOX_H
#define OUTBOX_H

#include "src/BaseNode.h"

namespace ds {

class OutBox : public BaseNode
{
  public:
    OutBox();
    ~OutBox();
    void process();
    void draw(ofEventArgs & args);
  protected:
  private:
};

}
#endif // OUTBOX_H
