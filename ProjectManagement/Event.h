//
//  Event.h
//  ProjectManagement
//
//  Created by Matthew Valli on 13/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__Event__
#define __ProjectManagement__Event__

#include <iostream>
#include <string>
#include <list>
#include "XMLNode.h"

using namespace std;

class Event {
private:
    // CONSTANTS
    static const string ID;
    static const string NAME;
    
    // MEMBERS
    long mId;
    string mName;
    long mInEdgeCount;
    long mOutEdgeCount;
    
public:
    // CONSTRUCTOR
    Event();
    Event(long uid, string name);
    Event(XMLNode &node);
    
    // CONVENIENCE METHODS
    string toString();
    
    // ACCESSORS
    long getId();
    void setId(long uid);
    string getName();
    void setName(string name);
    long getInEdgeCount();
    void setInEdgeCount(long numberOfEdges);
    void incrementInEdgeCount();
    long getOutEdgeCount();
    void setOutEdgeCount(long numberOfEdges);
    void incrementOutEdgeCount();
    
    
};

#endif /* defined(__ProjectManagement__Event__) */
