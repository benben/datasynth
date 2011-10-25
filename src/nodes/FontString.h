#ifndef FONTSTRING_H
#define FONTSTRING_H

#include "src/BaseNode.h"
#include "src/controls/FileChooser.h"

namespace ds {

typedef boost::shared_ptr<ds::FileChooser> FileChooserPtr;

typedef struct {
	string character;
	string code;
} charSubstitution;

class FontString : public BaseNode
{
  public:
    FontString(int _ID, float _x, float _y, string _name);
    ~FontString();
    void init();

    ofTrueTypeFont myFont;

    void parseFile(string & args);
    void process();
    void draw();
    void drawString(ofEventArgs & args);

    FileChooserPtr filechooser;

    string value;
    string getValueAsString();
    void setValueFromString(string _val);

    void subsChars(string& origString);

    int winId;
  protected:
  private:
};

}
#endif // FONTSTRING_H
