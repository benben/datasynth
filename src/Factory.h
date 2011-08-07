#pragma once

#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include "src/BaseNode.h"
#include "src/Connection.h"
#include "src/Nodes.h"

//typedef boost::variant<ds::Constant, ds::Multiply> ObjectType;
typedef boost::shared_ptr<ds::BaseNode> NodePtr;
typedef boost::shared_ptr<ds::Connection> ConnectionPtr;

struct bad_type_exception : std::exception {
    char const * what() const throw() { return "No such class!"; }
};

struct Factory {

    typedef std::map<std::string, boost::function<NodePtr(int, float, float, string)> > FactoryMap;
    FactoryMap f;

    Factory() {
        using boost::phoenix::new_;
        using boost::phoenix::construct;
        using namespace boost::phoenix::arg_names;
        f["Constant"]    = construct<NodePtr>(new_<ds::Constant>(arg1, arg2, arg3, arg4));
        f["Add"]         = construct<NodePtr>(new_<ds::Add>(arg1, arg2, arg3, arg4));
        f["Substract"]   = construct<NodePtr>(new_<ds::Substract>(arg1, arg2, arg3, arg4));
        f["Multiply"]    = construct<NodePtr>(new_<ds::Multiply>(arg1, arg2, arg3, arg4));
        f["Divide"]      = construct<NodePtr>(new_<ds::Divide>(arg1, arg2, arg3, arg4));
        f["OutBox"]      = construct<NodePtr>(new_<ds::OutBox>(arg1, arg2, arg3, arg4));
        f["CSVParser"]   = construct<NodePtr>(new_<ds::CSVParser>(arg1, arg2, arg3, arg4));
        f["Render"]      = construct<NodePtr>(new_<ds::Render>(arg1, arg2, arg3, arg4));
        f["Point"]       = construct<NodePtr>(new_<ds::Point>(arg1, arg2, arg3, arg4));
        f["Line"]        = construct<NodePtr>(new_<ds::Line>(arg1, arg2, arg3, arg4));
        f["HSBColor"]    = construct<NodePtr>(new_<ds::HSBColor>(arg1, arg2, arg3, arg4));
        f["Min"]         = construct<NodePtr>(new_<ds::Min>(arg1, arg2, arg3, arg4));
        f["Max"]         = construct<NodePtr>(new_<ds::Max>(arg1, arg2, arg3, arg4));
        f["Map"]         = construct<NodePtr>(new_<ds::Map>(arg1, arg2, arg3, arg4));
        f["Modulo"]      = construct<NodePtr>(new_<ds::Modulo>(arg1, arg2, arg3, arg4));
        f["Pixel"]       = construct<NodePtr>(new_<ds::Pixel>(arg1, arg2, arg3, arg4));
        f["GreaterThan"] = construct<NodePtr>(new_<ds::GreaterThan>(arg1, arg2, arg3, arg4));
        f["LessThan"]    = construct<NodePtr>(new_<ds::LessThan>(arg1, arg2, arg3, arg4));
        f["BitmapString"]= construct<NodePtr>(new_<ds::BitmapString>(arg1, arg2, arg3, arg4));
        f["Text"]        = construct<NodePtr>(new_<ds::Text>(arg1, arg2, arg3, arg4));
        // ...
    }

    NodePtr operator()(int ID, std::string const & type, float x, float y, string name) const {
        FactoryMap::const_iterator it = f.find(type);
        if (it == f.end()) throw bad_type_exception();
        return it->second(ID, x, y, name);
    }
};
