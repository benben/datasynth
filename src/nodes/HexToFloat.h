#ifndef HEXTOFLOAT_H
#define HEXTOFLOAT_H

#include "src/BaseNode.h"
namespace ds {

class HexToFloat : public BaseNode
{
  public:
    HexToFloat(int _ID, float _x, float _y, string _name);
    ~HexToFloat();
    void process();
  protected:
  private:
};

}
#endif // HEXTOFLOAT_H
