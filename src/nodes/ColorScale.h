#ifndef COLORSCALE_H
#define COLORSCALE_H

#include "src/BaseNode.h"

namespace ds {

class ColorScale : public BaseNode
{
  public:
    ColorScale(int _ID, float _x, float _y, string _name);
    ~ColorScale();
    void process();
    void drawColorScale(ofEventArgs & args);

    int winId;
  protected:
  private:
};

}
#endif // COLORSCALE_H
