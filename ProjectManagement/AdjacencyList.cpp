//
//  AdjacencyList.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 17/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

/***************************************************************************************************
 PURPOSE: Creates an Adjacency List of Activities that:
                                                - Lead to an Event
                                                - Originate from an Event
 
 This List is used to tell which Activities must be completed before an Event has been reached.
 ***************************************************************************************************/

#include "AdjacencyList.h"

// CONSTATNS
const string AdjacencyList::TOP_LINK_OUTPUT = "\t\t|\n";
const string AdjacencyList::BOTTOM_LINK_OUTPUT = "\t\tv\n";

// CONSTRUCTORS
AdjacencyList::AdjacencyList() {
    mForwardAdjacencyList = nullptr;
    mBackwardAdjacencyList = nullptr;
}

AdjacencyList::AdjacencyList(vector<Event*>* vertices, vector<Activity*>* edges) {
    // Compile the AdjacencyLists
    mForwardAdjacencyList = compileAdjacencyLists(vertices, edges, true);
    mBackwardAdjacencyList = compileAdjacencyLists(vertices, edges, false);
}

// CONVENIENCE METHODS
string AdjacencyList::toString() {
    string output = "ADJACENCY LIST\n";
    
    output += listAsString(mForwardAdjacencyList, "FORWARD");
    output += "\n";
    output += listAsString(mBackwardAdjacencyList, "BACKWARD");
    
    return output;
}

// HELPER METHODS
string AdjacencyList::listAsString(vector<List<Activity*>*>* list, string listName) {
    string output = "START - " + listName + " Adjacency List\n";
    // Loop through list
    for (int i = 0; i < list->size(); i++) {
        // Get the next list
        List<Activity*>* currentList = list->at(i);
        
        // Label Start of Vertex
        output += "START - Vertex " + to_string(i) + "\n";
        // Iterate through the currentList
        for (List<Activity*>::iterator iter = currentList->begin();
             iter != currentList->end(); ++iter) {
            // Add animated arrow
            output += TOP_LINK_OUTPUT;
            output += BOTTOM_LINK_OUTPUT;
            // Add the object as string
            output += (*iter)->toString();
        }
        
        // Add animated arrow
        output += TOP_LINK_OUTPUT;
        output += BOTTOM_LINK_OUTPUT;
        
        // Label End of Vertex
        output += "END - Vertex " + to_string(i) + "\n\n";
    }
    output += "END - " + listName + " Adjacency List\n";
    
    return output;
}

vector<List<Activity*>*>* AdjacencyList::compileAdjacencyLists(vector<Event*> *vertices, vector<Activity*> *edges, bool constructForwardList) {
    // Create a Vector of Adjacency Lists
    vector<List<Activity*>*>* vectorAdjacencyList = new vector<List<Activity*>*>();
    
    // Create an AdjacencyList for each Event
    for (int i = 0; i < vertices->size(); i++) {
        // Construct an AdjacencyList
        List<Activity*> *tempList = constructAdjacencyList(*vertices->at(i), edges, constructForwardList);
        
        // Add the list to the vector of lists
        vectorAdjacencyList->push_back(tempList);
    }
    
    return vectorAdjacencyList;
}

List<Activity*>* AdjacencyList::constructAdjacencyList(Event& vertex, vector<Activity*>* edges, bool constructForwardList) {
    // Create a new list
    List<Activity*> *list = new List<Activity*>();
    
    // Get the id of the current vertex
    long vertexId = vertex.getId();
    
    // Loop through all the Activities in the vector
    for (int i = 0; i < edges->size(); i++) {
        // Get the current edge
        Activity *currentEdge = edges->at(i);
        
        // If the vertex id exists within the Activity
        // Insert it into list if appropriate direction
        if (constructForwardList) {
            if ( currentEdge->getStartVertex() == vertexId ) {
                // Insert the current edge
                list->push_back(currentEdge);
                // Increment the value of Forward OutEdgeCount
                vertex.incrementOutEdgeCount();
            }
        } else {
            // Construct Backward List
            if ( currentEdge->getEndVertex() == vertexId ) {
                list->push_back(currentEdge);
                // Increment the Backward - InEdgeCount
                vertex.incrementInEdgeCount();
            }
        }
    }
    
    return list;
}

// ACCESSORS
vector<List<Activity*>*>* AdjacencyList::getForwardAdjacencyList() {
    return mForwardAdjacencyList;
}
void AdjacencyList::setForwardAdjacencyList(vector<List<Activity*>*>* list) {
    mForwardAdjacencyList = list;
}
vector<List<Activity*>*>* AdjacencyList::getBackwardAdjacencyList() {
    return mBackwardAdjacencyList;
}
void AdjacencyList::setBackwardAdjacencyList(vector<List<Activity*>*>* list) {
    mBackwardAdjacencyList = list;
}
List<Activity*>* AdjacencyList::getForwardList(Event* vertex) {
    return mForwardAdjacencyList->at(vertex->getId());
}
void AdjacencyList::setForwardList(Event* vertex, List<Activity*>* list) {
    mForwardAdjacencyList->at(vertex->getId()) = list;
}
List<Activity*>* AdjacencyList::getBackwardList(Event* vertex) {
    return mBackwardAdjacencyList->at(vertex->getId());
}
void AdjacencyList::setBackwardList(Event* vertex, List<Activity*>* list) {
    mBackwardAdjacencyList->at(vertex->getId()) = list;
}
