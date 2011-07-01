#pragma once

#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "src/Menu.h"
#include "src/Connection.h"
#include "src/Nodes.h"

//typedef boost::variant<ds::Constant, ds::Multiply> ObjectType;
typedef boost::shared_ptr<ds::Object> ObjectPtr;

struct bad_type_exception : std::exception {
    char const * what() const throw() { return "No such class!"; }
};

struct Factory {

    typedef std::map<std::string, boost::function<ObjectPtr()> > FactoryMap;
    FactoryMap f;

    Factory() {
        using boost::phoenix::new_;
        using boost::phoenix::construct;
        f["Constant"] = construct<ObjectPtr>(new_<ds::Constant>());
        f["Multiply"] = construct<ObjectPtr>(new_<ds::Multiply>());
        f["OutBox"] = construct<ObjectPtr>(new_<ds::OutBox>());
        // ...
    }

    ObjectPtr operator()(std::string const & type) const {
        FactoryMap::const_iterator it = f.find(type);
        if (it == f.end()) throw bad_type_exception();
        return it->second();
    }
};

namespace ds {

class Core : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void createObject(entry & args);

        Factory factory;

        vector <ObjectPtr> objects;
        ofxXmlSettings XMLObjects;
};

}
