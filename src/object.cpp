#include "object.h"

object::object()
{
    //ctor
    name = "";
    type = "";
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
