#include "Connection.h"
using namespace ds;

Connection::Connection(Pin * _out, Pin * _in)
{
    cout << "creating connection..." << endl;
    in = _in;
    out = _out;
    in->addConnection();
    out->addConnection();
    ofAddListener(in->deleteEvent, this, &Connection::setInvalid);
    ofAddListener(out->deleteEvent, this, &Connection::setInvalid);
    ofAddListener(ofEvents.draw, this, &Connection::draw);
    bIsInvalid = false;
}

void Connection::setInvalid(int & args)
{
    cout << "setting bIsInvalid to true..." << endl;
    bIsInvalid = true;
}

Connection::~Connection()
{
    cout << "removing connection" << endl;
    in->removeConnection();
    out->removeConnection();
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
