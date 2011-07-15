#include "FileChooser.h"

using namespace ds;

FileChooser::FileChooser(float* _x, float* _y, string _name, bool* _bIsNodeActive)
{
    ofRegisterMouseEvents(this);
    bIsNodeActive = _bIsNodeActive;
    name = _name;
    x = _x;
    y = _y;
    b.x = *x;
    b.y = *y;
    b.width = 197;
    b.height = 15;
    bFileIsSet = false;
    bShow = false;

    loadEntries("data/");

    acceptedFileExtension = "csv";
}

FileChooser::~FileChooser()
{
    ofUnregisterMouseEvents(this);
    dir.close();
}

void FileChooser::loadEntries(string _dir)
{
    dir.listDir(_dir);
	dir.sort();

    ofFile testfile;
	for(unsigned int i = 0; i < dir.size(); i++)
    {
        fileentry temp;
        temp.name = dir.getName(i);
        testfile.open(dir.getPath(i));
        temp.isFile = testfile.isFile();
        if(temp.isFile)
        {
            temp.type = testfile.getExtension();
            temp.path = testfile.path();
        }
        testfile.close();
        temp.box.width = 200;
        temp.box.height = 15;
        entries.push_back(temp);
    }
}

void FileChooser::draw()
{
    b.x = *x + 2;
    b.y = *y + 14;

    ofNoFill();
    ofSetColor(0,0,0,255);
    ofRect(b);
    if(bFileIsSet)
    {
        ofDrawBitmapString(value,b.x+3,b.y+12);
    }
    else
    {
        ofDrawBitmapString("right-click to choose",b.x+3,b.y+12);
    }
    ofFill();
    if(bShow)
    {
        for(unsigned int i = 0; i < entries.size(); i++)
        {
            entries[i].box.x = b.x;
            entries[i].box.y = b.y + i*16;
            if(entries[i].box.inside(mouseX,mouseY))
            {
                ofSetColor(150,150,150,255);
            }
            else
            {
                ofSetColor(50,50,50,255);
            }
            ofRect(entries[i].box);
            ofSetColor(255,255,255,255);
            ofDrawBitmapString(entries[i].name,entries[i].box.x+3,entries[i].box.y+12);
            //to be implemented.....
            if(!entries[i].isFile)
            {
                //ofDrawBitmapString(">>",entries[i].box.x+180,entries[i].box.y+12);
            }
        }
    }
}

void FileChooser::setValue(string _val)
{
    value = _val;
}

void FileChooser::mouseMoved(ofMouseEventArgs & args)
{
    mouseX = args.x;
    mouseY = args.y;
}

void FileChooser::mousePressed(ofMouseEventArgs & args)
{
    if(b.inside(args.x,args.y))
    {
        if(args.button == 2)
        {
            *bIsNodeActive = false;
            bShow = true;
        }
    }
    else
    {
        if(args.button == 0 && bShow)
        {
            for(unsigned int i = 0; i < entries.size(); i++)
            {
                if(entries[i].box.inside(args.x,args.y))
                {
                    cout << "clicked on " << entries[i].name << " type: " << entries[i].type << endl;
                    if(entries[i].type == acceptedFileExtension)
                    {
                        setValue(entries[i].path);
                        ofNotifyEvent(fileEvent,entries[i].path,this);
                        bFileIsSet = true;
                    }
                    bShow = false;
                    break;
                }
            }
        }
        bShow = false;
    }
}

void FileChooser::mouseDragged(ofMouseEventArgs & args)
{
}

void FileChooser::mouseReleased(ofMouseEventArgs & args)
{
   bIsActive = false;
}
