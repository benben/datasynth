#ifndef CONNECTION_H
#define CONNECTION_H

#include "src/Object.h"
namespace ds {

class Connection : public Object
{
  public:
    Connection(Pin * _out, Pin * _in);
    ~Connection();
    Pin * in;
    Pin * out;
    void process();
    void draw(ofEventArgs & args);

    bool bIsInvalid;
  protected:
  private:
};

}
#endif // CONNECTION_H
