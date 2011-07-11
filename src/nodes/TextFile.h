#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "src/BaseNode.h"
#include <boost/tokenizer.hpp>

typedef boost::tokenizer<boost::escaped_list_separator<char> > CSVLine;

namespace ds {

struct Spread
{
    string name;
    vector<double> data;
};

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

    vector<Spread> spreads;
  protected:
  private:
};

}
#endif // TEXTFILE_H
