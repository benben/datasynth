#ifndef PIXEL_H
#define PIXEL_H

#include "src/BaseNode.h"

namespace ds {

class Pixel : public BaseNode
{
  public:
    Pixel(float _x, float _y, string _name);
    ~Pixel();
    void process();
    void drawMe(ofEventArgs & args);
    int winId;
  protected:
  private:
};

}
#endif // PIXEL_H
