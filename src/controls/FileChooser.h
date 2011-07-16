#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include "src/BaseNode.h"

namespace ds
{

struct fileentry
{
    string name;
    string type;
    string path;
    bool isFile;
    ofRectangle box;
};

class FileChooser
{
    public:
        FileChooser(float* _x, float* _y, string _name, string* _value,  bool* _bIsNodeActive);
        ~FileChooser();
        void draw();
        void setValue(string _val);
        virtual void mouseMoved(ofMouseEventArgs & args);
        virtual void mousePressed(ofMouseEventArgs & args);
        virtual void mouseDragged(ofMouseEventArgs & args);
        virtual void mouseReleased(ofMouseEventArgs & args);

        string name;
        string* value;
        float* x, * y;
        ofRectangle b;

        bool bIsActive;
        bool* bIsNodeActive;

        ofDirectory dir;
        bool bShow, bFileIsSet;

        void loadEntries(string _dir);
        vector<fileentry> entries;

        int mouseX, mouseY;

        string acceptedFileExtension;

        ofEvent<string> fileEvent;
    protected:
    private:
};

}

#endif // FILECHOOSER_H
