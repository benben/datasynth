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
    ofxFensterManager::get()->getPrimaryWindow()->addListener(this);
    ofBackground(80);
    //ofSetFrameRate(30);
    XMLObjects.loadFile("objects.xml");
    XMLObjects.pushTag("OBJECTS", 0);
    ofAddListener(Menu::Get()->menuEvent, this, &Core::handleMenuEvent);
    bLoad = false;
    cout << "setup finished" << endl;
    load();
}
//--------------------------------------------------------------
void Core::update()
{
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
            }
        } else {
            BOOST_FOREACH(ConnectionPtr connection, connections)
                connection->process();
            BOOST_FOREACH(NodePtr node, nodes)
                node->process();
        }
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
}
//--------------------------------------------------------------
void Core::draw()
{
    ofSetColor(255,255,255,255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);

    BOOST_FOREACH(NodePtr node, nodes)
    {
        if(!node->bIsInvalid)
        {
            node->basedraw();
            node->draw();
        }
    }
    BOOST_FOREACH(ConnectionPtr connection, connections)
        if(!connection->bIsInvalid)
        {
            connection->draw();
        }
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
        if(nodes[i]->bValueIsSaveable && nodes[i]->getValueAsString() != "")
        {
            cout << "node is saveable" << endl;
            saveXml.pushTag("NODE", i);
            saveXml.addTag("VALUE");
            saveXml.setValue("VALUE", nodes[i]->getValueAsString(), 0);
            saveXml.popTag();
        }
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
    loadXml.loadFile("default.xml");
    for(int i = 0; i < loadXml.getNumTags("NODE"); i++)
    {
        NodePtr temp = factory(loadXml.getAttribute("NODE","TYPE", "", i).c_str(), ofToFloat(loadXml.getAttribute("NODE","X", "", i).c_str()), ofToFloat(loadXml.getAttribute("NODE","Y", "", i).c_str()), loadXml.getAttribute("NODE","NAME", "", i).c_str());
        temp->type = loadXml.getAttribute("NODE","TYPE", "", i).c_str();
        //TODO *********** setValue of Controls?!
        loadXml.pushTag("NODE", i);
        if(loadXml.getNumTags("VALUE") > 0)
        {
            temp->setValueFromString(ofToString(loadXml.getValue("VALUE", "", 0).c_str()));
        }
        temp->init();
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
    loadXml.clear();
    bLoad = false;
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
void Core::keyPressed(int key, ofxFenster* win)
{
}
//--------------------------------------------------------------
void Core::keyReleased(int key, ofxFenster* win)
{
    if (key == ' ')
    {

    }
}
//--------------------------------------------------------------
void Core::mouseMoved(int x, int y, ofxFenster* win)
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

            if(button == 2 && nodes[i]->bIsActive)
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
