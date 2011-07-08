#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "src/BaseNode.h"

namespace ds {

class TextFile : public BaseNode
{
  public:
    TextFile(float _x, float _y, string _name);
    ~TextFile();

    ofFile inputFile;
    ofBuffer buffer;
    string str;
    void process();
    void draw(ofEventArgs & args);
  protected:
  private:
};

}
#endif // TEXTFILE_H
