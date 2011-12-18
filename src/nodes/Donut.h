#ifndef DONUT_H
#define DONUT_H

#include "src/BaseNode.h"

namespace ds {

class Donut : public BaseNode
{
  public:
    Donut(int _ID, float _x, float _y, string _name);
    ~Donut();
    void process();
    void drawDonut(ofEventArgs & args);
    vector<ofVec2f> extrude(vector<ofVec2f> _path, float _width);

    int winId;
  protected:
  private:
};

}
#endif // DONUT_H
