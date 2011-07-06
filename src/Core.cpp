#include "Core.h"

bool connectionIsInvalid(ConnectionPtr val)
{
    return val->bIsInvalid;
}

using namespace ds;

//--------------------------------------------------------------
void Core::setup()
{
    cout << "setup started" << endl;
    ofBackground(80);
    XMLObjects.loadFile("objects.xml");
    XMLObjects.pushTag("OBJECTS", 0);
    ofAddListener(Menu::Get()->menuEvent, this, &Core::handleMenuEvent);
    cout << "setup finished" << endl;
}
//--------------------------------------------------------------
void Core::update()
{
        //cout << "processing connections..." << endl;
        for(unsigned int i = 0; i < connections.size(); i++)
        {
            connections[i]->process();
        }
        //cout << "processing nodes..." << endl;
        BOOST_FOREACH(NodePtr node, nodes)
            node->process();
        //cout << "...finished!" << endl;
}
//--------------------------------------------------------------
void Core::draw()
{

}
//--------------------------------------------------------------
void Core::handleMenuEvent(menuEventType & args)
{
    //cout << args.type << ": " << args.value << endl;
    if(args.type == "CreateNode")
    {
        cout << "creating a node of type " << args.value << endl;
        for(int i = 0; i < XMLObjects.getNumTags("OBJECT"); i++)
        {
            if(args.value == XMLObjects.getAttribute("OBJECT","NAME", "", i))
            {
                printf("creating %s!\n", XMLObjects.getAttribute("OBJECT","NAME", "", i).c_str());
                printf("\ttype:\t%s!\n", XMLObjects.getAttribute("OBJECT","TYPE", "", i).c_str());

                //create objects here
                NodePtr temp = factory(XMLObjects.getAttribute("OBJECT","NAME", "", i).c_str(), Menu::Get()->x, Menu::Get()->y, XMLObjects.getAttribute("OBJECT","NAME", "", i).c_str());

                temp->width = 150;
                temp->height = 30;
                nodes.push_back(temp);
                printf("\n");
            }
        }
    }
    else if(args.type == "Save")
    {
        cout << "saving..." << endl;
    }
    else if(args.type == "SaveAs")
    {
        cout << "saving as..." << endl;
    }
    else if(args.type == "Load")
    {
        cout << "loading..." << endl;
    }
}
//--------------------------------------------------------------
void Core::keyPressed(int key)
{
}
//--------------------------------------------------------------
void Core::keyReleased(int key)
{
    if (key == ' ')
    {

    }
}
//--------------------------------------------------------------
void Core::mouseMoved(int x, int y )
{
    bool temp = false;
    //TODO: do this only if the mouse is pressed
    //check if mouse is over an node
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->inside(x,y))
        {
            temp = true;
            break;
        }
        else
        {
            temp = false;
        }
    }
    for(unsigned int i = 0; i < connections.size(); i++)
    {
        if(connections[i]->mouseIsOn())
        {
            temp = true;
            break;
        }
        else
        {
            temp = false;
        }
    }
    if(temp)
    {
        Menu::Get()->bMouseIsOnNode = true;
    }
    else
    {
        Menu::Get()->bMouseIsOnNode = false;
    }
}
//--------------------------------------------------------------
void Core::mouseDragged(int x, int y, int button)
{
}
//--------------------------------------------------------------
void Core::mousePressed(int x, int y, int button)
{
    if(button == 2)
    {
        for(unsigned int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->inside(x,y))
            {
                //delete the node
                nodes.erase(nodes.begin()+i);
                break;
            }
        }
        //delete all connections to this node
        connections.erase( remove_if(connections.begin(), connections.end(),connectionIsInvalid) , connections.end() );
        for(unsigned int i = 0; i < connections.size(); i++)
        {
            if(connections[i]->mouseIsOn())
            {
                //delete the connection
                connections.erase(connections.begin()+i);
                break;
            }
        }
    }
}
//--------------------------------------------------------------
void Core::mouseReleased(int x, int y, int button)
{
    Pin* in=0;
    Pin* out=0;
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        for(unsigned int j = 0; j < nodes[i]->input.size(); j++)
        {
            if(nodes[i]->input[j]->bIsActive)
            {
                if(nodes[i]->input[j]->isFree())
                {
                    cout << "input active: " << i << " " << j << endl;
                    in = nodes[i]->input[j];
                }
                else
                {
                    cout << "too many connections on input pin: " << i << " " << j << endl;
                }
            }
        }
        for(unsigned int j = 0; j < nodes[i]->output.size(); j++)
        {
            if(nodes[i]->output[j]->bIsActive)
            {
                cout << "output active: " << i << " " << j << endl;
                out = nodes[i]->output[j];
            }
        }
    }
    if(in != NULL && out != NULL)
    {
        cout << "make connection" << endl;
        ConnectionPtr val(new Connection(out, in));
        connections.push_back(val);
    }
}
//--------------------------------------------------------------
void Core::windowResized(int w, int h)
{
}
//--------------------------------------------------------------
void Core::gotMessage(ofMessage msg)
{
}
//--------------------------------------------------------------
void Core::dragEvent(ofDragInfo dragInfo)
{
}
//--------------------------------------------------------------
void Core::exit()
{
    nodes.clear();
    connections.clear();
    ofRemoveListener(Menu::Get()->menuEvent, this, &Core::handleMenuEvent);
}
