#ifndef CONNECTION_H
#define CONNECTION_H

#include "src/Pin.h"

namespace ds {

class Connection
{
  public:
    Connection(Pin * _out, Pin * _in);
    ~Connection();
    Pin * in;
    Pin * out;
    void process();
    void draw(ofEventArgs & args);
    void test(int & args);

    bool bIsInvalid;
  protected:
  private:
};

}
#endif // CONNECTION_H
