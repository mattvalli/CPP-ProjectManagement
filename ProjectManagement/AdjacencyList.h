//
//  AdjacencyList.h
//  ProjectManagement
//
//  Created by Matthew Valli on 17/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__AdjacencyList__
#define __ProjectManagement__AdjacencyList__

#include <iostream>
#include <vector>
#include "List.cpp"
#include "Activity.h"
#include "Event.h"

class AdjacencyList {
private:
    // CONSTANTS
    static const string TOP_LINK_OUTPUT;
    static const string BOTTOM_LINK_OUTPUT;
    
    // MEMBERS
    vector<List<Activity*>*>* mForwardAdjacencyList;
    vector<List<Activity*>*>* mBackwardAdjacencyList;
    
    // HELPER METHODS
    string listAsString(vector<List<Activity*>*>* list, string listName);
    
    List<Activity*>* constructAdjacencyList(Event& vertex, vector<Activity*>* edges, bool constructForwardList);
    
    vector<List<Activity*>*>* compileAdjacencyLists(vector<Event*> *events, vector<Activity*> *activities, bool constructForwardList);
    
public:
    // CONSTRUCTORS
    AdjacencyList();
    AdjacencyList(vector<Event*>* vertices, vector<Activity*>* edges);
    
    // CONVENIENCE METHODS
    string toString();
    
    // ACCESSORS
    vector<List<Activity*>*>* getForwardAdjacencyList();
    void setForwardAdjacencyList(vector<List<Activity*>*>* list);
    vector<List<Activity*>*>* getBackwardAdjacencyList();
    void setBackwardAdjacencyList(vector<List<Activity*>*>* list);
    List<Activity*>* getForwardList(Event* vertex);
    void setForwardList(Event* vertex, List<Activity*>* list);
    List<Activity*>* getBackwardList(Event* vertex);
    void setBackwardList(Event* vertex, List<Activity*>* list);
};


#endif /* defined(__ProjectManagement__AdjacencyList__) */
