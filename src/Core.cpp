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
    ofSetFrameRate(30);
    XMLObjects.loadFile("objects.xml");
    XMLObjects.pushTag("OBJECTS", 0);
    ofAddListener(Menu::Get()->menuEvent, this, &Core::handleMenuEvent);
    bLoad = false;
    cout << "setup finished" << endl;
    //load();
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
        //cout << "processing connections..." << endl;
        for(unsigned int i = 0; i < connections.size(); i++)
        {
            if(connections[i]->bIsInvalid)
            {
                connections.erase(connections.begin()+i);
            }
        }
        //cout << "processing nodes..." << endl;
        for(unsigned int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->bIsInvalid)
            {
                nodes.erase(nodes.begin()+i);
            }
        }
        //cout << "...finished!" << endl;
        if(bLoad)
        {
            //remove connections immediately...
            connections.clear();
            //...and set nodes only to invalid
            BOOST_FOREACH(NodePtr node, nodes)
                node->setInvalid();
            if(nodes.size() == 0 && connections.size() == 0)
            {
                load();
                bLoad = false;
            }
        } else {
            BOOST_FOREACH(ConnectionPtr connection, connections)
                connection->process();
            BOOST_FOREACH(NodePtr node, nodes)
                node->process();
        }
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
            saveXml.addAttribute("PIN", "VALUE", nodes[i]->output[j]->value->data[0], j);
        }
        saveXml.popTag();
    }
    for(unsigned int i = 0; i < connections.size(); i++)
    {
        saveXml.addTag("CONNECTION");
        saveXml.addAttribute("CONNECTION", "OUT_NODE_ID", connections[i]->outNodeID, i);
        saveXml.addAttribute("CONNECTION", "OUT_PIN_ID", connections[i]->outPinID, i);
        saveXml.addAttribute("CONNECTION", "IN_NODE_ID", connections[i]->inNodeID, i);
        saveXml.addAttribute("CONNECTION", "IN_PIN_ID", connections[i]->inPinID, i);
    }
    saveXml.saveFile("default.xml");
}
//--------------------------------------------------------------
void Core::load()
{
    cout << "really loading!" << endl;
    loadXml.clear();
    loadXml.loadFile("default.xml");
    for(int i = 0; i < loadXml.getNumTags("NODE"); i++)
    {
        NodePtr temp = factory(loadXml.getAttribute("NODE","TYPE", "", i).c_str(), ofToFloat(loadXml.getAttribute("NODE","X", "", i).c_str()), ofToFloat(loadXml.getAttribute("NODE","Y", "", i).c_str()), loadXml.getAttribute("NODE","NAME", "", i).c_str());
        temp->type = loadXml.getAttribute("NODE","TYPE", "", i).c_str();
        temp->width = 150;
        temp->height = 30;
        loadXml.pushTag("NODE", i);
        for(int j = 0; j < loadXml.getNumTags("PIN"); j++)
        {
            temp->output[j]->value->data[0] = ofToFloat(loadXml.getAttribute("PIN","VALUE", "", j).c_str());
            temp->init();
        }
        loadXml.popTag();
        nodes.push_back(temp);
    }
    for(int i = 0; i < loadXml.getNumTags("CONNECTION"); i++)
    {
        int outNodeID = ofToInt(loadXml.getAttribute("CONNECTION","OUT_NODE_ID", "", i).c_str());
        int outPinID = ofToInt(loadXml.getAttribute("CONNECTION","OUT_PIN_ID", "", i).c_str());
        int inNodeID = ofToInt(loadXml.getAttribute("CONNECTION","IN_NODE_ID", "", i).c_str());
        int inPinID = ofToInt(loadXml.getAttribute("CONNECTION","IN_PIN_ID", "", i).c_str());
        /*
        cout << outNodeID << endl;
        cout << outPinID << endl;
        cout << inNodeID << endl;
        cout << inPinID << endl;
        */
        ConnectionPtr val(new Connection(nodes[outNodeID]->output[outPinID], outNodeID, outPinID, nodes[inNodeID]->input[inPinID], inNodeID, inPinID));
        connections.push_back(val);
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
        bLoad = true;
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
}
//--------------------------------------------------------------
void Core::mouseDragged(int x, int y, int button)
{
}
//--------------------------------------------------------------
void Core::mousePressed(int x, int y, int button)
{
    bool temp = false;

    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->inside(x,y))
        {

            if(button == 2)
            {
                //set node to invalid
                nodes[i]->setInvalid();
            }
            temp = true;
            break;
        }
    }
    for(unsigned int i = 0; i < connections.size(); i++)
    {
        if(connections[i]->mouseIsOn())
        {
            if(button == 2)
            {
                //set connection to invalid
                connections[i]->bIsInvalid = true;
            }
            temp = true;
            break;
        }
    }

    Menu::Get()->bMouseIsOnNode = temp;
}
//--------------------------------------------------------------
void Core::mouseReleased(int x, int y, int button)
{
    Pin* in=0;
    Pin* out=0;
    int outNodeID;
    int outPinID;
    int inNodeID;
    int inPinID;

    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        for(unsigned int j = 0; j < nodes[i]->input.size(); j++)
        {
            if(nodes[i]->input[j]->bIsActive)
            {
                if(nodes[i]->input[j]->isFree())
                {
                    cout << "input active: " << i << " " << j << endl;
                    inNodeID = i;
                    inPinID = j;
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
                outNodeID = i;
                outPinID = j;
                out = nodes[i]->output[j];
            }
        }
    }
    if(in != NULL && out != NULL)
    {
        cout << "make connection" << endl;
        ConnectionPtr val(new Connection(out, outNodeID, outPinID, in, inNodeID, inPinID));
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
    connections.clear();
    nodes.clear();
    bLoad = false;
    ofRemoveListener(Menu::Get()->menuEvent, this, &Core::handleMenuEvent);
}
