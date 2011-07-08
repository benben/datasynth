#include "TextFile.h"
using namespace ds;

TextFile::TextFile(float _x, float _y, string _name)
{
    //output.push_back(new Pin(0.0));
    x = _x;
    y = _y;
    name = _name;
    inputFile.open("screenformats.csv");
    buffer = inputFile.readToBuffer();
    str = buffer.getText();
    cout << str << endl;
}

TextFile::~TextFile()
{
}

void TextFile::process()
{
    //cout << "process from TextFile()\n";
    //cout << "output pin: " << output[0]->value << endl;
}

void TextFile::draw(ofEventArgs & args)
{
    //leave this if you wanna draw the basic shapes
    basedraw();
}
