//
//  ProjectManagementViewController.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 17/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

/***************************************************************************************************
 PURPOSE:   Manages the interaction between the User and the Application. The ViewController acts as
            an interface for manipulating data in the model.
 
 ***************************************************************************************************/

#include "ProjectManagementViewController.h"
#include <unistd.h>

using namespace std;

// DEBUG
const bool ProjectManagementViewController::TESTING = false;
const bool ProjectManagementViewController::VERBOSE_TESTING = true;
const bool ProjectManagementViewController::DEBUG_CLI = false;
const bool ProjectManagementViewController::DEBUG_XML_ACT_LIST = false;
const bool ProjectManagementViewController::DEBUG_XML_ACT_VECTOR = false;
const bool ProjectManagementViewController::DEBUG_XML_EVT_LIST = false;
const bool ProjectManagementViewController::DEBUG_XML_EVT_VECTOR = false;

// CONSTANTS
const string ProjectManagementViewController::PATH_TO_XML = "/Users/Admin/Desktop/src_projectManagement/testDirectory/";

// MEMBERS


// CONSTRUCTORS
/* Creates a ProjectManagementViewController Object for the Command Line Interface
 */
ProjectManagementViewController::ProjectManagementViewController() {
    // Command Line Interface
    mInterface = new CommandLine();
    
    // Initialization
    mEvents = nullptr;
    mActivities = nullptr;
    //mAdjacencyLists = nullptr;
}

// CONVENIENCE METHODS
/* Runs the application, printing output to console and retreiving input from console 
 */
void ProjectManagementViewController::run() {
    // Prompt the User for Vertices
    if ( TESTING ) {
        mEvents = xmlEventsToVector(PATH_TO_XML + "eventList_1.xml");
    } else {
        promptForEvents();
    }
    
    // Prompt the User for Edges
    if ( TESTING ) {
        mActivities = xmlActivitiesToVector(PATH_TO_XML + "activityList_1.xml");
    } else {
        promptForActivities();
    }
    
    // Create a DirectAcyclicGraph Object from the vectors of Events and Activities
    mGraph = new DirectAcyclicGraph(mEvents, mActivities);
    
    // Run the Calculations
    mGraph->run();
    
}

// USER INTERFACE
/* Messages user to see if they have XML files of the desired objects
 *
 * RETURNS:     TRUE    - if the user responds with 'y' for YES
 *              FALSE   - if the user responds with 'n' for NO
 */
bool ProjectManagementViewController::promptForXMLPath(string objectName) {
    string path;
    while ( true ) {
        // Ask the User if they have an XML File of Events
        cout << "Do you have an XML file for " + objectName + "? (y/n)" << endl;
        cin >> path;
        if (path.compare("y") == 0) return true;
        if (path.compare("n") == 0) return false;
        cout << "Invalid entry, try again!" << endl;
    }
}

// VIEW CONTROLLER FLOW
/* Handles prompting a User for Event Objects
 */
void ProjectManagementViewController::promptForEvents() {
    // Ask if they have an XML file of Events
    string xmlFilePath;
    int exists = -1;
    
    if (promptForXMLPath("Events") == false) {
        //cout << "Enter Manual Input Mode - EVENTS" << endl;
        // Manual Input
        //mEvents = requestEventByEvent();
        cout << "Quiting, XML file required!" << endl;
        exit(0);
    } else {
        // If the string isn't empty, we have a filepath
        while ( exists == -1 ) {
            // Continue to Prompt until valid path
            cout << "Enter a path to an XML file of Events: " << endl;
            cin >> xmlFilePath;
            if (DEBUG_CLI) { cout << "xmlFilePath: " << xmlFilePath << endl; }
            
            if ( xmlFilePath.compare("quit") == 0 ) {
                cout << "Quiting";
                exit(0);
            }
            
            // If the string isn't empty
            if ( xmlFilePath.compare("") != 0 ) {
                // check if the file exists
                exists = access( xmlFilePath.c_str(), F_OK );
                
                // Inform user if the file does not exist
                if ( exists == -1 ) {
                    cout << "The file cannot be found: " << xmlFilePath << endl;
                }
            }
        }
    
        // They have a file path
        mEvents = xmlEventsToVector(xmlFilePath);
    }

    if ( VERBOSE_TESTING ) { cout << eventVectorToString() << endl; }
}

/* NOT REQUIRED - MORE IMPLEMENTATION NECESSARY
 * Handles prompting the user for an Event via Manual Input through the Console
vector<Event*>* ProjectManagementViewController::requestEventByEvent() {
    // Create a new vector for Events
    vector<Event*>* v = new vector<Event*>();
    
    // Event Properties
    long id = 0;
    string name;
    
    // Prompt the user for events until they are finished
    while (true)
    {
        cout << "Creating NEW EVENT!" << endl;
        name = mInterface->promptMessage("Enter Event Name: ");
        
        // Construct a new Event
        Event* currentEvent = new Event(id, name);
        
        // Add the Event to the Vector
        v->push_back(currentEvent);
        
        string add = mInterface->promptMessage("Would you like to add another event? (y/n)");
        if (add.compare("n") == 0) { break; }
        
        // Increment the id
        id++;
    }
    return v;
}
 */

/* Handles prompting a User for Activity Objects
 */
void ProjectManagementViewController::promptForActivities() {
    string xmlFilePath;
    int exists = -1;
    
    // Ask if they have an XML file of Events
    if (promptForXMLPath("Activity") == false ) {
        //cout << "Enter Manual Input Mode - ACTIVITIES" << endl;
        // Manual Input
        //mActivities = requestActivityByActivity();
        cout << "Quiting, XML file required!" << endl;
        exit(0);
    } else {
            // If the string isn't empty, we have a filepath
            while ( exists == -1 ) {
                // Continue to Prompt until valid path
                cout << "Enter a path to an XML file of Activities: " << endl;
                cin >> xmlFilePath;
                if (DEBUG_CLI) { cout << "xmlFilePath: " << xmlFilePath << endl; }
                
                if ( xmlFilePath.compare("quit") == 0 ) {
                    cout << "Quiting";
                    exit(0);
                }
                
                // If the string isn't empty
                if ( xmlFilePath.compare("") != 0 ) {
                    // check if the file exists
                    exists = access( xmlFilePath.c_str(), F_OK );
                    
                    // Inform user if the file does not exist
                    if ( exists == -1 ) {
                        cout << "The file cannot be found: " << xmlFilePath << endl;
                    }
                }
            }
            
            // They have a file path
            mActivities = xmlActivitiesToVector(xmlFilePath);
        }
    
    if ( VERBOSE_TESTING ) { cout << eventVectorToString() << endl; }
}

/* NOT REQUIRED - MORE IMPLEMENTATION NECESSARY
 * Handles prompting the user for an Activity via Manual Input through the Console
vector<Activity*>* ProjectManagementViewController::requestActivityByActivity() {
    // Create a new vector for Events
    vector<Activity*>* v = new vector<Activity*>();
    
    // Event Properties
    string temp;
    long id = 0;
    long units = 0;
    long startVertex = 0;
    long endVertex = 0;
    
    // Prompt the user for events until they are finished
    while (true)
    {
        cout << "Creating NEW ACTIVITY!" << endl;
        temp = mInterface->promptMessage("Enter the units required for completion: ");
        units = stol(temp);
        cout << "units: " << units << endl;
        startVertex = stol(mInterface->promptMessage("Enter the origin Event ID:"));
        endVertex = stol(mInterface->promptMessage("Enter the destination Event ID:"));
        
        // Construct a new Event
        Activity* currentActivity = new Activity(id, units, startVertex, endVertex);
        
        // Add the Event to the Vector
        v->push_back(currentActivity);
        
        string add = mInterface->promptMessage("Would you like to add another Activity? (y/n)");
        if (add.compare("n") == 0) { break; }
        
        // Increment the id
        id++;
    }
    return v;
}
 */


/* Converts an XML File of Activity Nodes into a Vector<Activity*>
 */
vector<Activity*>* ProjectManagementViewController::xmlActivitiesToVector(string absPathToXML) {
    if (VERBOSE_TESTING && DEBUG_XML_ACT_VECTOR ) { cout << "Enter vector<Activity*>* xmlActivitiesToVector(string absPathToXML)" << endl; }
    // Read in the Activities from an XML File
    XMLReader *activitiesXML = new XMLReader(absPathToXML);
    
    // Get a vector of the list Activities
    vector<XMLNode*> *activityNodes = new vector<XMLNode*>();
    
    // Get the List of XMLNodes for "Activity" from the XML
    activityNodes = &activitiesXML->getRoot()->getChildren()->at("Activity");
    
    // Create a vector of Activity
    vector<Activity*> *activityVector = new vector<Activity*>();
    
    // Convert the Nodes to Activities
    for (int i = 0; i < activityNodes->size(); i++) {
        // Create Activity from Node i and add it to the list
        activityVector->push_back(new Activity(*activityNodes->at(i)));
    }
    
    if ( VERBOSE_TESTING && DEBUG_XML_ACT_VECTOR) {
        // Print the list
        cout << "START -- Vector<Activity*> activityList:" << endl;
        for (int i = 0; i < activityVector->size(); i++) {
            cout << activityVector->at(i)->toString() << endl;
        }
        cout << "END -- Vector<Activity*> activityList:" << endl;
    }
    
    if (VERBOSE_TESTING && DEBUG_XML_ACT_VECTOR) { cout << "Exit vector<Activity*>* xmlActivitiesToVector(string absPathToXML)" << endl; }
    return activityVector;
}

/* Converts an XML File of Event Nodes into a Vector<Event*>
 */
vector<Event*>* ProjectManagementViewController::xmlEventsToVector(string absPathToXML) {
    if (VERBOSE_TESTING && DEBUG_XML_EVT_VECTOR) { cout << "Enter vector<Event*>* xmlEventsToVector(string absPathToXML)" << endl; }
    // Read in the Activities from an XML File
    XMLReader *eventXML = new XMLReader(absPathToXML);
    
    // Get a vector of the list Activities
    vector<XMLNode*> *eventNodes = new vector<XMLNode*>();
    
    // Get the List of XMLNodes for "Activity" from the XML
    eventNodes = &eventXML->getRoot()->getChildren()->at("Event");
    
    // Create a vector of Activity
    vector<Event*> *eventVector = new vector<Event*>();
    
    // Convert the Nodes to Activities
    for (int i = 0; i < eventNodes->size(); i++) {
        // Create Activity from Node i and add it to the list
        eventVector->push_back(new Event(*eventNodes->at(i)));
    }
    
    if ( VERBOSE_TESTING && DEBUG_XML_EVT_VECTOR ) {
        // Print the list
        cout << "START -- vector<Event*> eventList:" << endl;
        for (int i = 0; i < eventVector->size(); i++) {
            cout << eventVector->at(i)->toString() << endl;
        }
        cout << "END -- vector<Event*> eventList:" << endl;
    }
    
    if (VERBOSE_TESTING && DEBUG_XML_EVT_VECTOR) { cout << "Exit vector<Event*>* xmlEventsToVector(string absPathToXML)" << endl; }
    return eventVector;
}


// HELPER METHODS
/* Creates a string object representing a vector of Events
 */
string ProjectManagementViewController::eventVectorToString() {
    if (mEvents == nullptr) { return "ProjectManagementViewController - mEvents: NULL\n"; }
    string output = "START - ProjectManagementViewController - mEvents\n";
    output += "Number of Event objects in the vector<Event*>: " + to_string(mEvents->size()) + "\n";
    
    for (int i = 0; i < mEvents->size(); i++) {
        output += mEvents->at(i)->toString() + "\n";
    }
    
    output += "END - ProjectManagementViewController - mEvents";
    return output;
}

/* Creats a string object representing a vector of Activities
 */
string ProjectManagementViewController::activityVectorToString() {
    if (mActivities == nullptr) { return "ProjectManagementViewController - mActivities: NULL\n"; }
    string output = "START - ProjectManagementViewController - mActivities\n";
    output += "Number of Activity objects in the vector<Activity*>: " + to_string(mActivities->size())  + "\n";
    
    for (int i = 0; i < mActivities->size(); i++) {
        output += mActivities->at(i)->toString() + "\n";
    }
    
    output += "END - ProjectManagementViewController - mActivities";
    return output;
}
