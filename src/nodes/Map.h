#ifndef MAP_H
#define MAP_H

#include "src/BaseNode.h"
namespace ds {

class Map : public BaseNode
{
  public:
    Map(float _x, float _y, string _name);
    ~Map();
    void process();
  protected:
  private:
};

}
#endif // MAP_H
