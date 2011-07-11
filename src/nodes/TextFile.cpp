#include "TextFile.h"
using namespace ds;

bool filter(char c)
{
	return c==',';
}

TextFile::TextFile(float _x, float _y, string _name)
{
    //output.push_back(new Pin(0.0));
    x = _x;
    y = _y;
    name = _name;
    inputFile.open("screenformats.csv");
    buffer = inputFile.readToBuffer();
    str = buffer.getNextLine();
    CSVLine line(str);
    for(CSVLine::iterator l=line.begin(); l!=line.end();++l){
        cout << *l << " | ";
        Spread temp;
        temp.name = *l;
        spreads.push_back(temp);
    }
    cout << endl;
    int i;
    while(!buffer.isLastLine())
    {
        str = buffer.getNextLine();
        CSVLine line(str);
        i = 0;
        for(CSVLine::iterator l=line.begin(); l!=line.end();++l){
            string t = *l;
            t.resize( std::remove_if(t.begin(), t.end(), filter) - t.begin() );
            cout << ofToFloat(t) << " | ";
            spreads[i].data.push_back(ofToFloat(t));
            i++;
        }
        cout << endl;
    }
    cout << "######################" << endl;
    BOOST_FOREACH(Spread s, spreads)
    {
        cout << s.name << endl;
        BOOST_FOREACH(double d, s.data)
            cout << d << endl;
        cout << endl;
    }
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
