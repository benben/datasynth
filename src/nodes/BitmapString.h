#ifndef BITMAPSTRING_H
#define BITMAPSTRING_H

#include "src/BaseNode.h"

namespace ds {

class BitmapString : public BaseNode
{
  public:
    BitmapString(int _ID, float _x, float _y, string _name);
    ~BitmapString();
    void process();
    void drawBitmapString(ofEventArgs & args);

    int winId;
  protected:
  private:
};

}
#endif // BITMAPSTRING_H
