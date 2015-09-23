//
//  Event.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 13/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

/***************************************************************************************************
 PURPOSE: MODEL CLASS representing an Event
 
 Records the Event Properties:
                        - Unique Id
                        - Name
 ***************************************************************************************************/

#include "Event.h"

using namespace std;

// CONSTANTS
const string Event::ID = "id";
const string Event::NAME = "name";

// CONSTRUCTORS
Event::Event() {
    Event(0,"Default Event");
}

Event::Event(long uid, string name) {
    mId = uid;
    mName = name;
    mInEdgeCount = 0;
    mOutEdgeCount = 0;
}

Event::Event(XMLNode &node) {
    // Get A list of the Children
    map<string, vector<XMLNode*>> children = *node.getChildren();
    vector<XMLNode*> id = children.at(ID);
    vector<XMLNode*> name = children.at(NAME);
    
    // Get the values from the list
    mId = stol(id.at(0)->getContents());
    mName = name.at(0)->getContents();
    mInEdgeCount = 0;
    mOutEdgeCount = 0;
}


// CONVENIENCE METHODS
string Event::toString() {
    string output = "EVENT OBJECT\n";
    output += "id: " + to_string(mId) + "\n";
    output += "name: " + mName + "\n";
    output += "inEdgeCount: " + to_string(mInEdgeCount) + "\n";
    output += "outEdgeCount: " + to_string(mOutEdgeCount) + "\n";
    
    return output;
}

// ACCESSOR METHODS
long Event::getId() {
    return mId;
}

void Event::setId(long uid) {
    mId = uid;
}

string Event::getName() {
    return mName;
}

void Event::setName(string name) {
    mName = name;
}

long Event::getInEdgeCount() {
    return mInEdgeCount;
}

void Event::setInEdgeCount(long numberOfEdges) {
    mInEdgeCount = numberOfEdges;
}

void Event::incrementInEdgeCount() {
    mInEdgeCount++;
}

long Event::getOutEdgeCount() {
    return mOutEdgeCount;
}

void Event::setOutEdgeCount(long numberOfEdges){
    mOutEdgeCount = numberOfEdges;
}

void Event::incrementOutEdgeCount() {
    mOutEdgeCount++;
}
