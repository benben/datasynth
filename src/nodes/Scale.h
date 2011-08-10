#ifndef SCALE_H
#define SCALE_H

#include "src/BaseNode.h"

namespace ds {

class Scale : public BaseNode
{
  public:
    Scale(int _ID, float _x, float _y, string _name);
    ~Scale();
    void process();
    void drawScale(ofEventArgs & args);

    int winId;
  protected:
  private:
};

}
#endif // SCALE_H
