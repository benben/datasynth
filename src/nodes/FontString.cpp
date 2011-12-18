#include "FontString.h"
using namespace ds;

FontString::FontString(int _ID, float _x, float _y, string _name)
{
    ID = _ID;
    value = "";
    bValueIsSaveable = true;
    x = _x;
    y = _y;
    name = _name;
    width = 200;
    color.r = 0;
    color.g = 186;
    color.b = 255;
    FileChooserPtr f(new FileChooser(&x, &y, name, &value, &bIsActive, "ttf"));
    filechooser = f;
    ofAddListener(filechooser->fileEvent, this, &FontString::parseFile);

    Spread x(new SpreadStruct);
    x->name = "X";
    input.push_back(new Pin(x, color, 1));
    Spread y(new SpreadStruct);
    y->name = "Y";
    input.push_back(new Pin(y, color, 1));
    Spread str(new SpreadStruct);
    str->name = "str";
    input.push_back(new Pin(str, color, 1));
    Spread c(new SpreadStruct);
    c->name = "color";
    input.push_back(new Pin(c, color, 1));

    Spread s(new SpreadStruct);
    s->name = "size";
    input.push_back(new Pin(s, color, 1));

    winId = ofxFensterManager::get()->getLastCreatedWindow()->id;
    ofAddListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &FontString::drawString);
}

FontString::~FontString()
{
    ofRemoveListener(filechooser->fileEvent, this, &FontString::parseFile);
    ofRemoveListener(ofxFensterManager::get()->getWindowById(winId)->events.draw, this, &FontString::drawString);
    input.clear();
}

string FontString::getValueAsString()
{
    return ofToString(value);
}

void FontString::setValueFromString(string _val)
{
    value = _val;
}

void FontString::init()
{
    if(value != "")
    {
        filechooser->setValue(value);
        filechooser->bFileIsSet = true;
        parseFile(value);
    }
}

void FontString::parseFile(string & args)
{
    cout << "parsing " << args << "..." << endl;
    myFont.loadFont(args, 1, true, true);
}

void FontString::process()
{
    if(!bProcessed)
    {
        parseFile(value);
        bProcessed = true;
    }
    //cout << "process from FontString()\n";
    //cout << "output pin: " << output[0]->value << endl;
}

void FontString::draw()
{
    ofSetColor(0,0,0,255);
    ofDrawBitmapString(name, x+2, y+12);
    filechooser->draw();
}

void FontString::drawString(ofEventArgs & args)
{
    int size0 = input[0]->value->data.size();
    int size1 = input[1]->value->data.size();
    int size2 = input[2]->value->data.size();
    int size3 = input[3]->value->data.size();
    int size4 = input[4]->value->data.size();
    if(size0 > 0 && size1 > 0 && size2 > 0 && size3 > 0 && size4 > 0)
    {
        int it = 0;
        int max = maxSliceCount();
        while(it < max)
        {
            ofColor c = boost::get<ofColor>(input[3]->value->data[it % size3]);
            ofSetColor(c);
            float x = (int)boost::get<float>(input[0]->value->data[it % size0]);
            float y = (int)boost::get<float>(input[1]->value->data[it % size1]);
            string str;
            try
            {
                str = boost::get<string>(input[2]->value->data[it % size2]);
            }
            catch(...)
            {
                str = ofToString(boost::get<float>(input[2]->value->data[it % size2]));
            }
            subsChars(str);
            myFont.drawString(str,x,y);
            it++;
        }
    }
}

void FontString::subsChars(string& origString) {
	charSubstitution chars[]= {{"ß","\xDF"},
		{"à","\xE0"}, {"á","\xE1"}, {"â","\xE2"}, {"ã","\xE3"}, {"ä","\xE4"}, {"æ","\xE6"},
		{"ò","\xF2"}, {"ó","\xF3"} ,{"ô","\xF4"}, {"õ","\xF5"}, {"ö","\xF6"},
		{"ù","\xF9"}, {"ú","\xFA"}, {"û","\xFB"}, {"ü","\xFC"},
		{"è","\xE8"}, {"é","\xE9"}, {"ê","\xEA"}, {"ë","\xEB"},
		{"ì","\xEC"}, {"í","\xED"}, {"î","\xEE"}, {"ï","\xEF"},
		{"ç","\xE7"}, {"Ç","\xC7"}, {"\n", "|"}
    };

	for(int i=0; i<26; i++) {
		while(origString.find(chars[i].character)!=string::npos) {
			origString = origString.substr(0,origString.find(chars[i].character)) + chars[i].code + origString.substr(origString.find(chars[i].character)+2);
		}
	};
}
