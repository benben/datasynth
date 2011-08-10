#ifndef TEXTSCALE_H
#define TEXTSCALE_H

#include "src/BaseNode.h"

namespace ds {

class TextScale : public BaseNode
{
  public:
    TextScale(int _ID, float _x, float _y, string _name);
    ~TextScale();
    void process();
    void drawTextScale(ofEventArgs & args);

    int winId;
  protected:
  private:
};

}
#endif // TEXTSCALE_H
