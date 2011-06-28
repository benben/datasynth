#include "Connection.h"
using namespace ds;

Connection::Connection(void * _in, void * _out, unsigned long _size)
{
  in = _in;
  out = _out;
  size = _size;
}

Connection::~Connection()
{
}

void Connection::process()
{
  cout << "process from Connection()\n";
  memcpy(out, in, size);
}
