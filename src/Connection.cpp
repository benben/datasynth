#include "Connection.h"
using namespace ds;

Connection::Connection(Pin * _out, Pin * _in)
{
    cout << "creating connection..." << endl;
    ofAddListener(ofEvents.draw, this, &Connection::draw);
    in = _in;
    out = _out;
    bIsInvalid = false;
}

Connection::~Connection()
{
    cout << "removing connection" << endl;
    ofRemoveListener(ofEvents.draw, this, &Connection::draw);
}

void Connection::process()
{
    memcpy(&in->value,&out->value,sizeof(in->value));
}

void Connection::draw(ofEventArgs & args)
{
    ofSetColor(255,255,255,255);
    ofLine(out->x+7, out->y+7, in->x+7, in->y+7);
}
