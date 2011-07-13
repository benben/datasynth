#pragma once

#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxXmlSettings.h"
#include "src/Menu.h"
#include "src/Connection.h"
#include "src/Nodes.h"

//typedef boost::variant<ds::Constant, ds::Multiply> ObjectType;
typedef boost::shared_ptr<ds::BaseNode> NodePtr;
typedef boost::shared_ptr<ds::Connection> ConnectionPtr;

struct bad_type_exception : std::exception {
    char const * what() const throw() { return "No such class!"; }
};

struct Factory {

    typedef std::map<std::string, boost::function<NodePtr(float, float, string)> > FactoryMap;
    FactoryMap f;

    Factory() {
        using boost::phoenix::new_;
        using boost::phoenix::construct;
        using namespace boost::phoenix::arg_names;
        f["Constant"] = construct<NodePtr>(new_<ds::Constant>(arg1, arg2, arg3));
        f["Multiply"] = construct<NodePtr>(new_<ds::Multiply>(arg1, arg2, arg3));
        f["OutBox"] = construct<NodePtr>(new_<ds::OutBox>(arg1, arg2, arg3));
        f["TextFile"] = construct<NodePtr>(new_<ds::TextFile>(arg1, arg2, arg3));
        // ...
    }

    NodePtr operator()(std::string const & type, float x, float y, string name) const {
        FactoryMap::const_iterator it = f.find(type);
        if (it == f.end()) throw bad_type_exception();
        return it->second(x, y, name);
    }
};

namespace ds {

class Core : public ofxFensterListener{

	public:
		void setup();
		void update();
		void draw();
        void exit();

        void save();
        ofxXmlSettings saveXml;
        void load();
        ofxXmlSettings loadXml;
        bool bLoad;

        void keyPressed(int key, ofxFenster* win);
        void keyReleased(int key, ofxFenster* win);
        void mouseMoved(int x, int y, ofxFenster* win);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

		void handleMenuEvent(menuEventType & args);

        Factory factory;

        vector <NodePtr> nodes;
        vector <ConnectionPtr> connections;
        ofxXmlSettings XMLObjects;
};

}
