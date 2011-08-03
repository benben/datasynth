#ifndef LINE_H
#define LINE_H

#include "src/BaseNode.h"

namespace ds {

class Line : public BaseNode
{
  public:
    Line(int _ID, float _x, float _y, string _name);
    ~Line();
    void process();
    void drawLines(ofEventArgs & args);

    int winId;
  protected:
  private:
};

}
#endif // LINE_H
