#ifndef OUTBOX_H
#define OUTBOX_H

#include "src/Object.h"

namespace ds {

class OutBox : public Object
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
