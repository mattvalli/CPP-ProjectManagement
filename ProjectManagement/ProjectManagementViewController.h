//
//  ProjectManagementViewController.h
//  ProjectManagement
//
//  Created by Matthew Valli on 17/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__ProjectManagementViewController__
#define __ProjectManagement__ProjectManagementViewController__

#include <iostream>
#include <vector>
#include "CommandLine.h"
#include "XMLReader.h"
#include "Activity.h"
#include "Event.h"
#include "AdjacencyList.h"
#include "DirectAcyclicGraph.h"

using namespace std;

class ProjectManagementViewController {
private:
    // DEBUG
    static const bool TESTING;
    static const bool VERBOSE_TESTING;
    static const bool DEBUG_CLI;
    static const bool DEBUG_XML_ACT_LIST;
    static const bool DEBUG_XML_ACT_VECTOR;
    static const bool DEBUG_XML_EVT_LIST;
    static const bool DEBUG_XML_EVT_VECTOR;
    
    
    // CONSTANTS
    static const string PATH_TO_XML;
    // MEMBERS
    // Initialization
    vector<Event*> *mEvents;
    vector<Activity*> *mActivities;
    AdjacencyList *mAdjacencyLists;
    DirectAcyclicGraph *mGraph;
    
    // COMMAND LINE INTERFACE
    CommandLine *mInterface;
    
    // HELPER METHODS
    string eventVectorToString();
    string activityVectorToString();
    
public:
    // CONSTRUCTORS
    ProjectManagementViewController();
    
    // CONVENIENCE METHODS
    void run();
    
    // USER INTERFACE
    bool promptForXMLPath(string objectName);
    
    // VIEW CONTROLLER FLOW
    void promptForEvents();
    vector<Event*>* requestEventByEvent();
    void promptForActivities();
    vector<Activity*>* requestActivityByActivity();
    void constructAdjacencyLists();
    
        // Activity
        List<Activity*>* xmlActivitiesToLinkedList(string absPathToXML);
        vector<Activity*>* xmlActivitiesToVector(string absPathToXML);
        List<Activity*>* activityVectorToLinkedList(vector<Activity*>* v);
        vector<Activity*>* activityLinkedListToVector(List<Activity*>* list);
        // Event
        List<Event*>* xmlEventsToLinkedList(string absPathToXML);
        vector<Event*>* xmlEventsToVector(string absPathToXML);
        List<Event*>* eventVectorToLinkedList(vector<Event*>* v);
        vector<Event*>* eventLinkedListToVector(List<Event*>* list);
    
    // ACCESSOR METHODS
    
};

#endif /* defined(__ProjectManagement__ProjectManagementViewController__) */
