#ifndef QUAD_H
#define QUAD_H

#include "src/BaseNode.h"

namespace ds {

class Quad : public BaseNode
{
  public:
    Quad(int _ID, float _x, float _y, string _name);
    ~Quad();
    void process();
    void drawQuad(ofEventArgs & args);

    int winId;
  protected:
  private:
};

}
#endif // QUAD_H
