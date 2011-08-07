#ifndef TEXT_H
#define TEXT_H

#include "src/BaseNode.h"
#include "src/controls/TextInput.h"
#include "boost/shared_ptr.hpp"

typedef boost::shared_ptr<ds::TextInput> TextInputPtr;

namespace ds {

class Text : public BaseNode
{
  public:
    Text(int _ID, float _x, float _y, string _name);
    ~Text();
    void process();
    void draw();

    TextInputPtr textinput;

    string value;

    string getValueAsString();
    void setValueFromString(string _val);
  protected:
  private:
};

}
#endif // TEXT_H
