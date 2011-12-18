#ifndef RENDER_H
#define RENDER_H

#include "src/BaseNode.h"
#include "ofxTileSaver.h"

namespace ds {

class RenderWindow: public ofxFensterListener {
public:
	void setup(){
	}
	void draw(){
	    //ofBackground(0);
	}
};

class Render : public BaseNode
{
  public:
    Render(int _ID, float _x, float _y, string _name);
    ~Render();
    void process();

    ofxFenster* win;
    RenderWindow* renderWin;

    string getValueAsString();
    void setValueFromString(string _val);

    void start(ofEventArgs & args);
    void stop(ofEventArgs & args);

    void keyReleased(ofKeyEventArgs & args);

    ofxTileSaver saver;
  protected:
  private:
};

}
#endif // RENDER_H
