#ifndef CONNECTION_H
#define CONNECTION_H

#include "src/Object.h"
namespace ds {

class Connection : public Object
{
  public:
    Connection(void * _in, void * _out, unsigned long _size);
    ~Connection();
    void * in;
    void * out;
    unsigned long size;
    void process();
  protected:
  private:
};

}
#endif // CONNECTION_H
