#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "src/BaseNode.h"
#include "src/controls/FileChooser.h"
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

typedef boost::shared_ptr<ds::FileChooser> FileChooserPtr;
typedef boost::tokenizer<boost::escaped_list_separator<char> > CSVLine;

namespace ds {

class CSVParser : public BaseNode
{
  public:
    CSVParser(float _x, float _y, string _name);
    ~CSVParser();
    void init();

    ofFile inputFile;
    ofBuffer buffer;
    string str;
    void parseFile(string & args);
    void process();
    void draw();

    vector<Spread> spreads;

    FileChooserPtr filechooser;

    string value;
    string getValueAsString();
    void setValueFromString(string _val);
  protected:
  private:
};

}
#endif // CSVPARSER_H
