//
//  DirectAcyclicGraph.h
//  ProjectManagement
//
//  Created by Matthew Valli on 10/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__DirectAcyclicGraph__
#define __ProjectManagement__DirectAcyclicGraph__

#include <iostream>
#include <stack>
#include "AdjacencyList.h"

using namespace std;

class DirectAcyclicGraph {
private:
    // DEBUG
    static const bool DEBUG_CONSTRUCTORS;
    static const bool DEBUG_EE;
    static const bool DEBUG_EL;
    
    // MEMBERS
    AdjacencyList *mAdjacencyList;
    vector<Event*>* mEvents;
    vector<Activity*>* mActivities;
    vector<int> *mForwardEdgeCount;
    vector<int> *mBackwardEdgeCount;
    
    // CONVIENCE METHODS
    string reportOpenLabelString();
    string reportCloseLabelString();
    
    // HELPER METHODS
    int min(int a, int b);
    int max(int a, int b);
    void printVector(vector<int>* v, string label);
    void printStack(stack<int>* s, string label);
    void generateEdgeCountVector(vector<Event*>* events, vector<Activity*>* activities);
    
public:
    // CONSTRUCTORS
    DirectAcyclicGraph();
    DirectAcyclicGraph(vector<Event*> *eventVector, vector<Activity*> *activityVector);
    
    // CONVENIENCE METHODS
    void run();
    
    // CALCULATIONS
    vector<int>* calculateEE();
    vector<int>* calculateEL(int latestEventTime);
    
    // ACCESSOR METHODS
    AdjacencyList* getAdjacencyList();
    void setAdjacencyList(AdjacencyList* list);
    
    
};

#endif /* defined(__ProjectManagement__DirectAcyclicGraph__) */
