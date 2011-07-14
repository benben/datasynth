#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "src/BaseNode.h"
#include "src/controls/FileChooser.h"
#include <boost/tokenizer.hpp>

typedef boost::shared_ptr<ds::FileChooser> FileChooserPtr;
typedef boost::tokenizer<boost::escaped_list_separator<char> > CSVLine;

namespace ds {

class TextFile : public BaseNode
{
  public:
    TextFile(float _x, float _y, string _name);
    ~TextFile();

    ofFile inputFile;
    ofBuffer buffer;
    string str;
    void parseFile(string & args);
    void process();
    void draw();

    vector<Spread> spreads;

    FileChooserPtr filechooser;
  protected:
  private:
};

}
#endif // TEXTFILE_H
