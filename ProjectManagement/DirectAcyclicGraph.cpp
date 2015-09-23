//
//  DirectAcyclicGraph.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 10/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

/***************************************************************************************************
 PURPOSE:   Data Structure with analysis methods for determining relationships, duration,
            and shortest/critical path.
 
 This is the heart of the Microsoft Project application that allows users to determine what tasks 
 require higher precedence in order for project completion.
 
 ***************************************************************************************************/

#include "DirectAcyclicGraph.h"

using namespace std;

// CONSTANTS
const bool DirectAcyclicGraph::DEBUG_CONSTRUCTORS = false;
const bool DirectAcyclicGraph::DEBUG_EE = true;
const bool DirectAcyclicGraph::DEBUG_EL = true;


// CONSTRUCTORS
DirectAcyclicGraph::DirectAcyclicGraph() {
    mAdjacencyList = nullptr;
}

DirectAcyclicGraph::DirectAcyclicGraph(vector<Event*> *eventVector, vector<Activity*> *activityVector) {
    // Use the vectors to construct the AdjacencyList Object
    mAdjacencyList = new AdjacencyList(eventVector, activityVector);
    
    // Used to monitor edge counts while calculating EE and EL
    mForwardEdgeCount = new vector<int>(eventVector->size());
    mBackwardEdgeCount = new vector<int>(eventVector->size());
    
    if (DEBUG_CONSTRUCTORS) {
        cout << "mForwardEdgeCount.size: " << mForwardEdgeCount->size() << endl;
        cout << "mBackwardEdgeCount.size: " << mBackwardEdgeCount->size() << endl;
    }
    
    //
    generateEdgeCountVector(eventVector, activityVector);
    
    // Store the original vectors
    mEvents = eventVector;
    mActivities = activityVector;
    
    if (DEBUG_CONSTRUCTORS) {
        cout << "DIRECT ACYCLIC GRAPH OBJECT" << endl;
        cout << mAdjacencyList->toString() << endl;
        printVector(mForwardEdgeCount, "Forward Edge Count");
        printVector(mBackwardEdgeCount, "Backward Edge Count");
        cout << endl;
    }
}

// CONVENIENCE METHODS
void DirectAcyclicGraph::run() {
    // Calculates and Prints Final Results
    // Calculate the Earliest Event Times
    vector<int>* ee = calculateEE();
    
    // Get the latest event time
    int latestEventTime = ee->at(ee->size() - 1);
    
    // Calculate the Latest Event Times
    vector<int>* el = calculateEL(latestEventTime);
    
    // Output Label
    cout << reportOpenLabelString() << endl;
    
    // Update the times for each Activity
    for (int i = 0; i < mActivities->size(); i++) {
        // Update Time
        mActivities->at(i)->updateTime(ee, el);
        // Print Report
        cout << mActivities->at(i)->reportString() << endl;
    }
    
    // Output Label
    cout << reportCloseLabelString() << endl;
    
    // Clean Memory
    delete ee;
    delete el;
}

string DirectAcyclicGraph::reportOpenLabelString() {
    string output;
    
    output += " _______________________________________________________________________________ \n";
    output += "|               |               |               |               |               |\n";
    output += "|\tActivity\t";
    output += "|\tEarly Time\t";
    output += "|\tLate Time\t";
    output += "|\t  Slack\t\t";
    output += "|\tCritical\t|";
    output += "\n";
    
    // Buffer
    output += "|_______________|_______________|_______________|_______________|_______________|\n";
    output += "|               |               |               |               |               |";
    
    
    return output;
}

string DirectAcyclicGraph::reportCloseLabelString() {
    string output = "|_______________________________________________________________________________|";
    return output;
}

// CALCULATIONS
vector<int>* DirectAcyclicGraph::calculateEE() {
    // Create a local stack for tracking ee path calculations
    stack<int> *topoStack = new stack<int>();
    
    // Get the number of vertices
    int numbOfVertices = (int) mAdjacencyList->getForwardAdjacencyList()->size();
    
    // Create a local vector<int>, one index for each vertices (index == id)
    vector<int> *eeTopoVector = new vector<int>(numbOfVertices);
    
    // Initialize all value to zero
    for ( int i = 0; i < numbOfVertices; i++ ) {
        // Set the current index to zero
        eeTopoVector->at(i) = 0;
    }
    
    // If testing, Print the initial state of the vector
    if ( DEBUG_EE ) {
        cout << "Initial State EE" << endl;
        printVector(mForwardEdgeCount, "Forward Edge Count");
        printVector(eeTopoVector, "EE Vector");
    }
    
    // Start at the initial Vertex and move forward
    if (mAdjacencyList->getForwardAdjacencyList() != nullptr) {
        // Get the first Vertex
        int parentVertexId = 0;
        // Initialize the stack with the first vertex
        topoStack->push(parentVertexId);
    
        // Loop through the adjacency list and calculate ee
        while (true) {
            // Break if the stack is empty
            if (topoStack->empty()) break;
            
            // Retrieve the id of the next vertex to process
            parentVertexId = topoStack->top();
            
            // Get the list for the currentVertex from the index in the stack
            List<Activity*> *currentVertexList = mAdjacencyList->getForwardAdjacencyList()->at(parentVertexId);
            
            // Remove the select index from the stack
            topoStack->pop();
            
            // If the list is null, continue
            //if (currentVertexList->isEmpty()) { continue; }
            
            // Iterate the list and set the earliest start time
            for (List<Activity*>::iterator iter = currentVertexList->begin();
                 iter != currentVertexList->end(); ++iter) {
                // The iter's endVertex is the childVertex
                int childVertexId = (int) (*iter)->getEndVertex();
                int partentToChildUnits = (int) (*iter)->getUnit();
                
                // Calculate the total units from start (partentsEE + parentToChildUnits)
                int unitsToChild = eeTopoVector->at(parentVertexId) + partentToChildUnits;
                
                // Take the max of unitsToChild or the value currently in eeTopoVector for the child
                eeTopoVector->at(childVertexId) = max(unitsToChild, eeTopoVector->at(childVertexId));
                // Decrement the Forward Edge Count
                mForwardEdgeCount->at(childVertexId)--;
                
                //
                if (mForwardEdgeCount->at(childVertexId) == 0) {
                    // Add it the to topoStack
                    topoStack->push(childVertexId);
                }
                
                // If testing, Print the mid-loop state of the vector
                if ( DEBUG_EE ) {
                    cout << endl;
                    cout << "Mid-Loop State EE" << endl;
                    printVector(mForwardEdgeCount, "Forward Edge Count");
                    printVector(eeTopoVector, "EE Vector");
                    cout << endl;
                    printStack(topoStack, "Topo Stack");
                    cout << endl;
                }
                
            }
        }
        
        
    } else {
        // No AdjacencyList, return null
        eeTopoVector = nullptr;
    }
    
    if ( DEBUG_EE ) {
        cout << "Final EE" << endl;
        printVector(mForwardEdgeCount, "Forward Edge Count");
        printVector(eeTopoVector, "EE Vector");
        cout << endl;
    }
    
    // Delete the topoStack
    delete topoStack;
    
    return eeTopoVector;
}

vector<int>* DirectAcyclicGraph::calculateEL(int latestEventTime) {
    // Create a local stack for tracking ee path calculations
    stack<int> *topoStack = new stack<int>();
    
    // Get the number of vertices
    int numbOfVertices = (int) mAdjacencyList->getBackwardAdjacencyList()->size();
    
    // Create a local vector<int>, one index for each vertices (index == id)
    vector<int> *elTopoVector = new vector<int>(numbOfVertices);
    
    // Initialize all value to latest event time
    for ( int i = 0; i < numbOfVertices; i++ ) {
        // Set the current index to latest event time
        elTopoVector->at(i) = latestEventTime;
    }
    
    // If testing, Print the initial state of the vector
    if ( DEBUG_EL ) {
        cout << "Initial State EL" << endl;
        printVector(mBackwardEdgeCount, "Backward Edge Count");
        printVector(elTopoVector, "EL Vector");
    }
    
    // Start at the initial Vertex and move forward
    if (mAdjacencyList->getBackwardAdjacencyList() != nullptr) {
        // Get the first Vertex
        int childVertexId = numbOfVertices - 1;
        // Initialize the stack with the first vertex
        topoStack->push(childVertexId);
        
        // Loop through the adjacency list and calculate ee
        while (true) {
            // Break if the stack is empty
            if (topoStack->empty()) break;
            
            // Retrieve the id of the next vertex to process
            childVertexId = topoStack->top();
            
            // Get the list for the currentVertex from the index in the stack
            List<Activity*> *currentVertexList = mAdjacencyList->getBackwardAdjacencyList()->at(childVertexId);
            
            // Remove the select index from the stack
            topoStack->pop();
            
            // Iterate the list and set the earliest start time
            for (List<Activity*>::iterator iter = currentVertexList->begin();
                 iter != currentVertexList->end(); ++iter) {
                // The iter's endVertex is the childVertex
                int parentVertexId = (int) (*iter)->getStartVertex();
                int childToParentUnits = (int) (*iter)->getUnit();
                
                // Calculate the total units from start (partentsEE + parentToChildUnits)
                int unitsToParent = elTopoVector->at(childVertexId) - childToParentUnits;
                
                // Take the max of unitsToChild or the value currently in eeTopoVector for the child
                elTopoVector->at(parentVertexId) = min(unitsToParent, elTopoVector->at(childVertexId));
                
                //
                if (mBackwardEdgeCount->at(parentVertexId) == 1) {
                    // Add it the to topoStack
                    topoStack->push(parentVertexId);
                }
                
                // Decrement the Forward Edge Count
                mBackwardEdgeCount->at(parentVertexId)--;
                
                // If testing, Print the mid-loop state of the vector
                if ( DEBUG_EL ) {
                    cout << endl;
                    cout << "Mid-Loop State EL" << endl;
                    printVector(mBackwardEdgeCount, "Backward Edge Count");
                    printVector(elTopoVector, "EL Vector");
                    cout << endl;
                    printStack(topoStack, "Topo Stack");
                    cout << endl;
                }
                
            }
        }
        
        
    } else {
        // No AdjacencyList, return null
        elTopoVector = nullptr;
    }
    
    if ( DEBUG_EL ) {
        cout << "Final EL" << endl;
        printVector(mBackwardEdgeCount, "Backward Edge Count");
        printVector(elTopoVector, "EL Vector");
        cout << endl;
    }
    
    // Delete the topoStack
    delete topoStack;
    
    return elTopoVector;
}



// HELPER METHODS
int DirectAcyclicGraph::min(int a, int b) {
    // if a is greater than b, return a, else return b
    return a < b ? a : b;
}
int DirectAcyclicGraph::max(int a, int b) {
    // if a is greater than b, return a, else return b
    return a > b ? a : b;
}
void DirectAcyclicGraph::printVector(vector<int>* v, string label) {
    // Labeling
    cout << label << endl;
    cout << "Index\t";
    for ( int i = 0; i < v->size(); i++ ) {
        cout << "|\t" << to_string(i) << "\t";
    }
    
    // Jump to next line for formatting
    cout << "|" << endl;
    
    // Print values
    cout << "Value\t";
    for ( int i = 0; i < v->size(); i++ ) {
        cout << "|\t" << to_string(v->at(i)) << "\t";
    }
    
    // Jump to next line for formatting
    cout << "|" << endl;
}

void DirectAcyclicGraph::printStack(stack<int>* s, string label) {
    // Create a new temp stack
    stack<int> *temp = new stack<int>();
    int tempInt = -1;
    
    // Label
    cout << label << endl;
    cout << "vvv - Stack Top - vvv" << endl;
    
    // Pop and Print while stack is not empty
    while (!s->empty()) {
        // Load var
        tempInt = s->top();
        
        // Format
        cout << "\t\t\t";
        cout << to_string(tempInt) << endl;
        
        // Add to temp stack (in reverse order)
        temp->push(tempInt);
        
        // Remove from original stack
        s->pop();
    }
    
    // End Label
    cout << "^^^ - Stack Bottom - ^^^" << endl;
    
    // Re-Assemble the orginal stack
    while (!temp->empty()) {
        // Peek at the temp and add value back to the original stack
        s->push(temp->top());
        // Pop the value
        temp->pop();
    }
}

void DirectAcyclicGraph::generateEdgeCountVector(vector<Event*>* events, vector<Activity*>* activities) {
    // Generate the Counts of the Edges
    for (int i = 0; i < activities->size(); i++) {
        // Get the edge
        Activity* currentEdge = activities->at(i);
        
        // Increment the In and Out Edge Count respectively
            // Start Vertex == Out Edge
            events->at(currentEdge->getStartVertex())->incrementOutEdgeCount();
        mForwardEdgeCount->at(currentEdge->getEndVertex())++;
            // End Vertext == In Edge
            events->at(currentEdge->getEndVertex())->incrementInEdgeCount();
        mBackwardEdgeCount->at(currentEdge->getStartVertex())++; //= mBackwardEdgeCount->at(currentEdge->getEndVertex())++;
    }
}

// ACCESSOR METHODS
AdjacencyList* DirectAcyclicGraph::getAdjacencyList() {
    return mAdjacencyList;
}
void DirectAcyclicGraph::setAdjacencyList(AdjacencyList* list) {
    mAdjacencyList = list;
}

