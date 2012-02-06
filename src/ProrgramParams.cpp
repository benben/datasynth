#include "ProgramParams.h"

#include <iostream>
#include <boost/program_options.hpp>


namespace po = boost::program_options;


ProgramParams::ProgramParams(int argc, char *argv[])
{
    //ctor
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "print this help message")
    ("width", po::value<int>(), "set width of start window")
    ("height", po::value<int>(), "set height of start window")
    ;


    try
    {
        po::store(po::parse_command_line(argc, argv, desc), this->vm);
        po::notify(this->vm);

        if (this->vm.count("help"))
        {
                throw desc;
        }
    }
    catch(...)
    {
        std::cout << "Check your input params" << std::endl;
    }

}

ProgramParams::~ProgramParams()
{
    //dtor
}

bool ProgramParams::hasOption(std::string option)
{
    return true;
}

