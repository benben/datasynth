#ifndef CIRCLE_H
#define CIRCLE_H

#include "src/BaseNode.h"
#include "boost/shared_ptr.hpp"

namespace ds {

class Circle : public BaseNode
{
  public:
    Circle(int _ID, float _x, float _y, string _name);
    ~Circle();
    void process();
    void drawMe(ofEventArgs & args);
    int winId;
  protected:
  private:
};

}
#endif // CIRCLE_H
