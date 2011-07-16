#include "CSVParser.h"
using namespace ds;

bool filter(char c)
{
	return c==',';
}

CSVParser::CSVParser(float _x, float _y, string _name)
{
    value = "";
    bValueIsSaveable = true;
    x = _x;
    y = _y;
    name = _name;
    width = 200;
    color.r = 0;
    color.g = 186;
    color.b = 255;
    FileChooserPtr f(new FileChooser(&x, &y, name, &value, &bIsActive));
    filechooser = f;
    ofAddListener(filechooser->fileEvent, this, &CSVParser::parseFile);
}

CSVParser::~CSVParser()
{
    ofRemoveListener(filechooser->fileEvent, this, &CSVParser::parseFile);
    spreads.clear();
    buffer.clear();
}

string CSVParser::getValueAsString()
{
    return ofToString(value);
}

void CSVParser::setValueFromString(string _val)
{
    value = _val;
}

void CSVParser::init()
{
    if(value != "")
    {
        filechooser->setValue(value);
        filechooser->bFileIsSet = true;
        parseFile(value);
    }
}

void CSVParser::parseFile(string & args)
{
    cout << "parsing " << args << "..." << endl;
    BOOST_FOREACH(Pin* p, output)
        p->value->data.clear();
    spreads.clear();
    inputFile.open(args);
    buffer = inputFile.readToBuffer();
    str = buffer.getNextLine();
    CSVLine line(str);
    for(CSVLine::iterator l=line.begin(); l!=line.end();++l){
        Spread temp(new SpreadStruct);
        temp->name = *l;
        spreads.push_back(temp);
    }
    int i;
    while(!buffer.isLastLine())
    {
        str = buffer.getNextLine();
        CSVLine line(str);
        i = 0;
        for(CSVLine::iterator l=line.begin(); l!=line.end();++l){
            string t = *l;
            t.resize(remove_if(t.begin(), t.end(), filter) - t.begin() );
            //cout << ofToFloat(t) << " | ";
            spreads[i]->data.push_back(ofToFloat(t));
            i++;
        }
        //cout << endl;
    }
    //if spreads.size is less than out.size, then delete some outputs beginning from the end of the output vector!
    int outsize = output.size();
    for(unsigned int i = 0; i < outsize; i++)
    {
        if(i >= spreads.size())
        {
            output[outsize-i]->setInvalid();
            //cout << "killing output " << outsize-i << endl;
            output.erase(output.begin()+(outsize-i));
        }
    }
    //if there are already outputs, just update them, if not, make new ones
    int outputsize = output.size();
    for(unsigned int i = 0; i < spreads.size(); i++)
    {
        if(i >= outputsize)
        {
            output.push_back(new Pin(spreads[i], color));
        }
        else
        {
            output[i]->value = spreads[i];
        }
    }
    /*
    cout << "######################" << endl;
    BOOST_FOREACH(Spread s, spreads)
    {
        cout << s->name << endl;
        BOOST_FOREACH(double d, s->data)
            cout << d << endl;
        cout << endl;
    }*/
    inputFile.close();
    buffer.clear();
}

void CSVParser::process()
{
    //cout << "process from CSVParser()\n";
    //cout << "output pin: " << output[0]->value << endl;
}

void CSVParser::draw()
{
    ofSetColor(0,0,0,255);
    ofDrawBitmapString(name, x+2, y+12);
    filechooser->draw();
}
