#include "object.h"

object::object()
{
    //ctor
}

object::~object()
{
    //dtor
}

void object::draw()
{
    ofRect(x,y,width,height);
}

void object::process()
{
    //STUB
}
