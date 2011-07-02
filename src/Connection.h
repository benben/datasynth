#ifndef CONNECTION_H
#define CONNECTION_H

#include "src/Object.h"
namespace ds {

class Connection : public Object
{
  public:
    Connection(float* _outX, float* _outY, float* _inX, float* _inY, void * _in, void * _out, unsigned long _size);
    ~Connection();
    void * in;
    void * out;
    unsigned long size;
    float* outXPtr, * outYPtr, * inXPtr, * inYPtr;
    float startX, startY, endX, endY;
    void process();
    void draw(ofEventArgs & args);

    bool bIsInvalid;
  protected:
  private:
};

}
#endif // CONNECTION_H
