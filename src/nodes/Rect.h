#ifndef RECT_H
#define RECT_H

#include "src/BaseNode.h"

namespace ds {

class Rect : public BaseNode
{
  public:
    Rect(int _ID, float _x, float _y, string _name);
    ~Rect();
    void process();
    void drawRect(ofEventArgs & args);

    int winId;
  protected:
  private:
};

}
#endif // RECT_H
