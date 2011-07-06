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
    ofSetFrameRate(60);
    XMLObjects.loadFile("objects.xml");
    XMLObjects.pushTag("OBJECTS", 0);
    ofAddListener(Menu::Get()->menuEvent, this, &Core::handleMenuEvent);
    cout << "setup finished" << endl;
}
//--------------------------------------------------------------
void Core::update()
{
        /*int n = 0;
        int ip = 0;
        int op = 0;
        int c = 0;
        for(unsigned int i = 0; i < nodes.size(); i++)
        {
            n++;
            for(unsigned int j = 0; j < nodes[i]->input.size(); j++)
            {
                ip++;
            }
            for(unsigned int j = 0; j < nodes[i]->output.size(); j++)
            {
                op++;
            }

        }
        for(unsigned int i = 0; i < connections.size(); i++)
        {
            c++;
        }
        cout << "n: " << n << " ip: " << ip << " op: " << op << " c: " << c << endl;*/
        cout << "processing connections..." << endl;
        for(unsigned int i = 0; i < connections.size(); i++)
        {
            connections[i]->process();
        }
        cout << "processing nodes..." << endl;
        BOOST_FOREACH(NodePtr node, nodes)
            node->process();
        cout << "...finished!" << endl;
}
//--------------------------------------------------------------
void Core::draw()
{
    ofSetColor(255,255,255,255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
}
//--------------------------------------------------------------
void Core::save()
{
    saveXml.clear();
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        cout << "saving node..." << endl;
        saveXml.addTag("NODE");
        saveXml.addAttribute("NODE", "NAME", nodes[i]->name, i);
        saveXml.addAttribute("NODE", "TYPE", nodes[i]->type, i);
        saveXml.addAttribute("NODE", "X", nodes[i]->x, i);
        saveXml.addAttribute("NODE", "Y", nodes[i]->y, i);
        saveXml.pushTag("NODE", i);
        for(unsigned int j = 0; j < nodes[i]->output.size(); j++)
        {
            saveXml.addTag("PIN");
            saveXml.addAttribute("PIN", "VALUE", boost::get<double>(nodes[i]->output[i]->value), j);
        }
        saveXml.popTag();
    }
    saveXml.saveFile("default.xml");
}
//--------------------------------------------------------------
void Core::load()
{
    nodes.erase(nodes.begin(),nodes.end());
    loadXml.clear();
    loadXml.loadFile("default.xml");
    for(int i = 0; i < loadXml.getNumTags("NODE"); i++)
    {
        NodePtr temp = factory(loadXml.getAttribute("NODE","TYPE", "", i).c_str(), ofToFloat(loadXml.getAttribute("NODE","X", "", i).c_str()), ofToFloat(loadXml.getAttribute("NODE","Y", "", i).c_str()), loadXml.getAttribute("NODE","NAME", "", i).c_str());
        temp->type = loadXml.getAttribute("NODE","TYPE", "", i).c_str();
        temp->width = 150;
        temp->height = 30;

        nodes.push_back(temp);
    }
}
//--------------------------------------------------------------
void Core::handleMenuEvent(menuEventType & args)
{
    //cout << args.type << ": " << args.value << endl;
    if(args.handler == "CreateNode")
    {
        cout << "creating a node '"<< args.value << "' of type " << args.valueType << endl;
        //create nodes here
        NodePtr temp = factory(args.valueType, Menu::Get()->x, Menu::Get()->y, args.value);
        temp->type = args.valueType;
        temp->width = 150;
        temp->height = 30;
        nodes.push_back(temp);
    }
    else if(args.handler == "Save")
    {
        cout << "saving..." << endl;
        save();
    }
    else if(args.handler == "SaveAs")
    {
        cout << "saving as..." << endl;
    }
    else if(args.handler == "Load")
    {
        cout << "loading..." << endl;
        load();
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
