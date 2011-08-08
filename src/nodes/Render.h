#ifndef RENDER_H
#define RENDER_H

#include "src/BaseNode.h"

namespace ds {

class RenderWindow: public ofxFensterListener {
public:
	void setup(){
	}
	void draw(){
	    ofBackground(80);
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
  protected:
  private:
};

}
#endif // RENDER_H
