#ifndef PROGRAMPARAMS_H
#define PROGRAMPARAMS_H

#include <boost/program_options.hpp>
namespace po=boost::program_options;

class ProgramParams
{

    po::variables_map vm;

    public:
        ProgramParams(int argc, char *argv[]);
        virtual ~ProgramParams();

        bool hasOption(std::string option);

    protected:
    private:
};

#endif // PROGRAMPARAMS_H

