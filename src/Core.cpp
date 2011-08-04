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
    ofxFensterManager::get()->getPrimaryWindow()->setWindowTitle("datasynth");
    ofxFensterManager::get()->getPrimaryWindow()->setBackgroundColor(80);
    ofSetFrameRate(25);
    ID = 0;
    XMLObjects.loadFile("objects.xml");
    XMLObjects.pushTag("OBJECTS", 0);
    ofAddListener(Menu::Get()->menuEvent, this, &Core::handleMenuEvent);
    bLoad = false;
    isInSet = false;
    isOutSet = false;
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
    if(isInSet)
    {
        ofSetColor(255,255,255,255);
        ofLine(in->input[inPinID]->x+7,in->input[inPinID]->y+7,mouseX,mouseY);
    }
    else if(isOutSet)
    {
        ofSetColor(255,255,255,255);
        ofLine(out->output[outPinID]->x+7,out->output[outPinID]->y+7,mouseX,mouseY);
    }
    Menu::Get()->draw();
}
//--------------------------------------------------------------
void Core::save()
{
    saveXml.clear();
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        cout << "saving node..." << endl;
        saveXml.addTag("NODE");
        saveXml.addAttribute("NODE", "ID", nodes[i]->ID, i);
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
        saveXml.addAttribute("CONNECTION", "OUT_NODE_ID", connections[i]->outNode->ID, i);
        saveXml.addAttribute("CONNECTION", "OUT_PIN_ID", connections[i]->outPinID, i);
        saveXml.addAttribute("CONNECTION", "IN_NODE_ID", connections[i]->inNode->ID, i);
        saveXml.addAttribute("CONNECTION", "IN_PIN_ID", connections[i]->inPinID, i);
    }
    saveXml.saveFile("default.xml");
}
//--------------------------------------------------------------
void Core::load()
{
    cout << "really loading!" << endl;
    loadXml.loadFile("default.xml");
    ID = 0;
    for(int i = 0; i < loadXml.getNumTags("NODE"); i++)
    {
        ID = ofToInt(loadXml.getAttribute("NODE","ID", "", i).c_str()) + 1;
        NodePtr temp = factory(ofToInt(loadXml.getAttribute("NODE","ID", "", i).c_str()),loadXml.getAttribute("NODE","TYPE", "", i).c_str(), ofToFloat(loadXml.getAttribute("NODE","X", "", i).c_str()), ofToFloat(loadXml.getAttribute("NODE","Y", "", i).c_str()), loadXml.getAttribute("NODE","NAME", "", i).c_str());
        temp->type = loadXml.getAttribute("NODE","TYPE", "", i).c_str();
        //TODO *********** setValue of Controls?!
        loadXml.pushTag("NODE", i);
        if(loadXml.getNumTags("VALUE") > 0)
        {
            temp->setValueFromString(ofToString(loadXml.getValue("VALUE", "", 0).c_str()));
        }
        loadXml.popTag();
        temp->init();
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
        cout << "creating connection between Node: " <<  outNodeID << " Pin: " << outPinID << " and Node " << inNodeID << " Pin: " << inPinID << endl;
        ConnectionPtr val(new Connection(getNodeByID(outNodeID), outPinID, getNodeByID(inNodeID), inPinID));
        connections.push_back(val);
    }
    //ugly workaround, maybe we can get rid of this later :(
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->init();
    }
    loadXml.clear();
    bLoad = false;
}
//--------------------------------------------------------------
NodePtr Core::getNodeByID(int _ID)
{
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->ID == _ID)
        {
            return nodes[i];
        }
    }
}
//--------------------------------------------------------------
bool Core::checkID(int _ID)
{
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->ID == _ID)
        {
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------------
void Core::handleMenuEvent(menuEventType & args)
{
    //cout << args.type << ": " << args.value << endl;
    if(args.handler == "CreateNode")
    {
        cout << "creating a node '"<< args.value << "' of type " << args.valueType << endl;
        //create nodes here
        NodePtr temp = factory(ID++, args.valueType, Menu::Get()->x, Menu::Get()->y, args.value);
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
    bool del = true;
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        if(!isInSet)
        {
            for(unsigned int j = 0; j < nodes[i]->input.size(); j++)
            {
                if(nodes[i]->input[j]->inside(x,y) && nodes[i]->input[j]->isFree())
                {
                    in = nodes[i];
                    inPinID = j;
                    isInSet = true;
                    del = false;
                    break;
                }
            }
        }
        if(!isOutSet)
        {
            for(unsigned int j = 0; j < nodes[i]->output.size(); j++)
            {
                if(nodes[i]->output[j]->inside(x,y) && nodes[i]->output[j]->isFree())
                {
                    out = nodes[i];
                    outPinID = j;
                    isOutSet = true;
                    del = false;
                    break;
                }
            }
        }
    }

    if(isInSet && isOutSet)
    {
        cout << "creating connection between Node: " <<  out->ID << " Pin: " << outPinID << " and Node " << in->ID << " Pin: " << inPinID << endl;
        ConnectionPtr val(new Connection(out, outPinID, in, inPinID));
        connections.push_back(val);
        isInSet = false;
        isOutSet = false;
    }
    //clicked but not on any pin
    if(del)
    {
        isInSet = false;
        isOutSet = false;
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
