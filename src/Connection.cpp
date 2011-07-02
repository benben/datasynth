#include "Connection.h"
using namespace ds;

Connection::Connection(float* _outX, float* _outY, float* _inX, float* _inY, void * _in, void * _out, unsigned long _size)
{
    cout << "creating connection..." << endl;
    ofAddListener(ofEvents.draw, this, &Connection::draw);
    in = _in;
    out = _out;
    size = _size;
    outXPtr = _outX;
    outYPtr = _outY;
    inXPtr = _inX;
    inYPtr = _inY;
    bIsInvalid = false;
}

Connection::~Connection()
{
    cout << "removing connection" << endl;
    ofRemoveListener(ofEvents.draw, this, &Connection::draw);
}

void Connection::process()
{
    memcpy(out,in,size);
    //cout << "processing from connection..." << endl;
}

void Connection::draw(ofEventArgs & args)
{
    startX = *outXPtr;
    startY = *outYPtr;
    endX = *inXPtr;
    endY = *inYPtr;
    ofSetColor(255,255,255,255);
    ofLine(startX+7, startY+7, endX+7, endY+7);
}
