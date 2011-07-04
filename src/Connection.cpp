#include "Connection.h"
using namespace ds;

Connection::Connection(Pin * _out, Pin * _in)
{
    cout << "creating connection..." << endl;
    in = _in;
    out = _out;
    ofAddListener(in->deleteEvent, this, &Connection::~Connection);
    ofAddListener(out->deleteEvent, this, &Connection::test);
    ofAddListener(ofEvents.draw, this, &Connection::draw);
    bIsInvalid = false;
}

void Connection::test(int & args)
{
    delete this;
}

Connection::~Connection()
{
    cout << "removing connection" << endl;
    ofRemoveListener(in->deleteEvent, this, &Connection::test);
    ofRemoveListener(out->deleteEvent, this, &Connection::test);
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
