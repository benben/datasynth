#ifndef POINT_H
#define POINT_H

#include "src/BaseNode.h"

namespace ds {

class Point : public BaseNode
{
  public:
    Point(float _x, float _y, string _name);
    ~Point();
    void process();
    void draw();
    void drawPoints(ofEventArgs & args);

    int winId;
  protected:
  private:
};

}
#endif // POINT_H
