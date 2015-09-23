//
//  TestUnit.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 17/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include "TestUnit.h"

// DEBUG
const bool TestUnit::VERBOSE_TESTING = true;

// CONSTANTS
const string TestUnit::PATH_TO_XML_DIRECTORY = "/Users/Admin/Desktop/";

/*
 void run() {
 // Get the Activities (Edges) and Events (Vertices)
 XMLReader *activitiesXML = new XMLReader("/Users/Admin/Desktop/testActivities.xml");
 XMLReader *eventsXML = new XMLReader(PATH_TO_XML_DIRECTORY + "testEvents.xml");
 
 if ( VERBOSE_TESTING ) {
 // Log Readers
 cout << activitiesXML->toString() << endl;
 cout << eventsXML->toString() << endl;
 }
 
 // Get a vector of the necessary Children
 vector<XMLNode*> activityNodes = activitiesXML->getRoot()->getChildren()->at("Activity");
 vector<XMLNode*> eventNodes = eventsXML->getRoot()->getChildren()->at("Event");
 
 // Convert the ActivitiesXML to a Vector of Activity objects
 vector<Activity*> *activities = new vector<Activity*>();
 vector<Event*> *events = new vector<Event*>();
 
 // Fill the vectors
 for (int i = 0; i < activityNodes.size(); i++) {
 // Construct a new Activity and add it to the Activity Vector
 activities->push_back(new Activity(*activityNodes.at(i)));
 }
 for (int i = 0; i < eventNodes.size(); i++) {
 // Construct a new Event and add it to the Event Vector
 events->push_back(new Event(*eventNodes.at(i)));
 }
 
 if ( VERBOSE_TESTING ) {
 cout << "Number of Activity objects in the vector<Activity*>: " << to_string(activities->size()) << endl;
 cout << "Number of Event objects in the vector<Event*>: " << to_string(events->size()) << endl;
 
 // Fill the vectors
 cout << "Activities: " << endl;
 for (int i = 0; i < activityNodes.size(); i++) {
 // Construct a new Activity and add it to the Activity Vector
 cout << activities->at(i)->toString() << endl;
 }
 cout << "Events: " << endl;
 for (int i = 0; i < eventNodes.size(); i++) {
 // Construct a new Event and add it to the Event Vector
 cout << events->at(i)->toString() << endl;
 }
 }
 }
 */

// CONVENIENCE METHODS
// ACTIVITY
List<Activity*>* TestUnit::xmlActivitiesToLinkedList(string absPathToXML) {
    if (VERBOSE_TESTING) { cout << "Enter List<Activity*>* xmlActivitiesToLinkedList(string absPathToXML)" << endl; }
    // Read in the Activities from an XML File
    XMLReader *activitiesXML = new XMLReader(absPathToXML);
    
    // Get a vector of the list Activities
    vector<XMLNode*> *activityNodes = new vector<XMLNode*>();
    
    // Get the List of XMLNodes for "Activity" from the XML
    activityNodes = &activitiesXML->getRoot()->getChildren()->at("Activity");
    
    // Create new LinkedList
    List<Activity*> *activityList = new List<Activity*>();
    
    // TO LIST FROM XMLNodes VECTOR
    for (int i = 0; i < activityNodes->size(); i++) {
        activityList->push_back(new Activity(*activityNodes->at(i)));
    }
    
    if ( VERBOSE_TESTING ) {
        // Print the list
        cout << "START -- List<Activity*> activityList:" << endl;
        for (List<Activity*>::iterator iter = activityList->begin();
             iter != activityList->end(); ++iter)
        {
            cout << (*iter)->toString() << endl;
        }
        cout << "END -- List<Activity*> activityList:" << endl;
    }
    
    if (VERBOSE_TESTING) { cout << "Exit List<Activity*>* xmlActivitiesToLinkedList(string absPathToXML)" << endl; }
    return activityList;
}

vector<Activity*>* TestUnit::xmlActivitiesToVector(string absPathToXML) {
    if (VERBOSE_TESTING) { cout << "Enter vector<Activity*>* xmlActivitiesToVector(string absPathToXML)" << endl; }
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
    
    if ( VERBOSE_TESTING ) {
        // Print the list
        cout << "START -- Vector<Activity*> activityList:" << endl;
        for (int i = 0; i < activityVector->size(); i++) {
            cout << activityVector->at(i)->toString() << endl;
        }
        cout << "END -- Vector<Activity*> activityList:" << endl;
    }
    
    if (VERBOSE_TESTING) { cout << "Exit vector<Activity*>* xmlActivitiesToVector(string absPathToXML)" << endl; }
    return activityVector;
}

List<Activity*>* TestUnit::activityVectorToLinkedList(vector<Activity*>* v) {
    if (VERBOSE_TESTING) { cout << "Enter List<Activity*>* activityVectorToLinkedList(vector<Activity*>* v)" << endl; }
    // Create new LinkedList
    List<Activity*> *activityList = new List<Activity*>();
    
    // Add the Activities to the list
    // TO LIST FROM VECTOR
    for (int i = 0; i < v->size(); i++) {
        activityList->push_back(v->at(i));
    }
    
    if ( VERBOSE_TESTING ) {
        // Print the list
        cout << "START -- List<Activity*> activityList:" << endl;
        for (List<Activity*>::iterator iter = activityList->begin();
             iter != activityList->end(); ++iter)
        {
            cout << (*iter)->toString() << endl;
        }
        cout << "END -- List<Activity*> activityList:" << endl;
    }
    
    if (VERBOSE_TESTING) { cout << "Exit List<Activity*>* activityVectorToLinkedList(vector<Activity*>* v)" << endl; }
    return activityList;
}

vector<Activity*>* TestUnit::activityLinkedListToVector(List<Activity*>* list) {
    if (VERBOSE_TESTING) { cout << "Enter vector<Activity*>* activityLinkedListToVector(List<Activity*>* list)" << endl; }
    // Create new LinkedList
    vector<Activity*> *activityVector = new vector<Activity*>();
    
    // Add the Activities to the list
    // TO LIST FROM VECTOR
    for (List<Activity*>::iterator iter = list->begin();
         iter != list->end(); ++iter) {
        activityVector->push_back((*iter));
    }
    
    if ( VERBOSE_TESTING ) {
        // Print the list
        cout << "START -- Vector<Activity*> activityList:" << endl;
        for (int i = 0; i < activityVector->size(); i++) {
            cout << activityVector->at(i)->toString() << endl;
        }
        cout << "END -- Vector<Activity*> activityList:" << endl;
    }
    
    if (VERBOSE_TESTING) { cout << "Exit vector<Activity*>* activityLinkedListToVector(List<Activity*>* list)" << endl; }
    return activityVector;
}

// EVENT
List<Event*>* TestUnit::xmlEventsToLinkedList(string absPathToXML) {
    if (VERBOSE_TESTING) { cout << "Enter List<Event*>* xmlEventsToLinkedList(string absPathToXML)" << endl; }
    // Read in the Activities from an XML File
    XMLReader *activitiesXML = new XMLReader(absPathToXML);
    
    // Get a vector of the list Activities
    vector<XMLNode*> *eventNodes = new vector<XMLNode*>();
    
    // Get the List of XMLNodes for "Event" from the XML
    eventNodes = &activitiesXML->getRoot()->getChildren()->at("Event");
    
    // Create new LinkedList
    List<Event*> *eventList = new List<Event*>();
    
    // TO LIST FROM XMLNodes VECTOR
    for (int i = 0; i < eventNodes->size(); i++) {
        eventList->push_back(new Event(*eventNodes->at(i)));
    }
    
    if ( VERBOSE_TESTING ) {
        // Print the list
        cout << "START -- List<Event*> eventList:" << endl;
        for (List<Event*>::iterator iter = eventList->begin();
             iter != eventList->end(); ++iter)
        {
            cout << (*iter)->toString() << endl;
        }
        cout << "END -- List<Event*> eventList:" << endl;
    }
    
    if (VERBOSE_TESTING) { cout << "Exit List<Event*>* xmlEventsToLinkedList(string absPathToXML)" << endl; }
    return eventList;
}

vector<Event*>* TestUnit::xmlEventsToVector(string absPathToXML) {
    if (VERBOSE_TESTING) { cout << "Enter vector<Event*>* xmlEventsToVector(string absPathToXML)" << endl; }
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
    
    if ( VERBOSE_TESTING ) {
        // Print the list
        cout << "START -- vector<Event*> eventList:" << endl;
        for (int i = 0; i < eventVector->size(); i++) {
            cout << eventVector->at(i)->toString() << endl;
        }
        cout << "END -- vector<Event*> eventList:" << endl;
    }
    
    if (VERBOSE_TESTING) { cout << "Exit vector<Event*>* xmlEventsToVector(string absPathToXML)" << endl; }
    return eventVector;
}

List<Event*>* TestUnit::eventVectorToLinkedList(vector<Event*>* v) {
    if (VERBOSE_TESTING) { cout << "Enter List<Event*>* eventVectorToLinkedList(vector<Event*>* v)" << endl; }
    // Create new LinkedList
    List<Event*> *eventList = new List<Event*>();
    
    // Add the Activities to the list
    // TO LIST FROM VECTOR
    for (int i = 0; i < v->size(); i++) {
        eventList->push_back(v->at(i));
    }
    
    if ( VERBOSE_TESTING ) {
        // Print the list
        cout << "START -- List<Event*> eventList:" << endl;
        for (List<Event*>::iterator iter = eventList->begin();
             iter != eventList->end(); ++iter)
        {
            cout << (*iter)->toString() << endl;
        }
        cout << "END -- List<Event*> eventList:" << endl;
    }
    
    if (VERBOSE_TESTING) { cout << "Exit List<Event*>* eventVectorToLinkedList(vector<Event*>* v)" << endl; }
    return eventList;
}

vector<Event*>* TestUnit::eventLinkedListToVector(List<Event*>* list) {
    if (VERBOSE_TESTING) { cout << "Enter vector<Event*>* eventLinkedListToVector(List<Event*>* list)" << endl; }
    // Create new LinkedList
    vector<Event*> *eventVector = new vector<Event*>();
    
    // Add the Activities to the list
    // TO LIST FROM VECTOR
    for (List<Event*>::iterator iter = list->begin();
         iter != list->end(); ++iter) {
        eventVector->push_back((*iter));
    }
    
    if ( VERBOSE_TESTING ) {
        // Print the list
        cout << "START -- Vector<Event*> eventList:" << endl;
        for (int i = 0; i < eventVector->size(); i++) {
            cout << eventVector->at(i)->toString() << endl;
        }
        cout << "END -- Vector<Event*> eventList:" << endl;
    }
    
    if (VERBOSE_TESTING) { cout << "Exit vector<Event*>* eventLinkedListToVector(List<Event*>* list)" << endl; }
    return eventVector;
}




// TESTING
void TestUnit::test() {
    //testXMLNode();
    //testActivityObject();
    //testXMLReader("/Users/Admin/Desktop/testActivities.xml");
    //testLinkedList();
    testDataConversions();
}

void TestUnit::testDataConversions() {
    testListToVectorConversion();
    testVectorToListConversion();
}
void TestUnit::testListToVectorConversion() {
    if ( VERBOSE_TESTING ) cout << "START - Testing List to Vector - Activities" << endl;
    List<Activity*> *activities = xmlActivitiesToLinkedList(PATH_TO_XML_DIRECTORY + "testActivities.xml");
    vector<Activity*> *activityList = activityLinkedListToVector(activities);
    if ( VERBOSE_TESTING ) cout << "END - Testing List to Vector - Activities" << endl << endl;
    if ( VERBOSE_TESTING ) cout << "START - Testing List to Vector - Events" << endl;
    List<Event*> *events = xmlEventsToLinkedList(PATH_TO_XML_DIRECTORY + "testEvents.xml");
    vector<Event*> *eventList = eventLinkedListToVector(events);
    if ( VERBOSE_TESTING ) {
        cout << "END - Testing List to Vector - Events" << endl << endl;
    }
    delete activityList;
    delete eventList;
}
void TestUnit::testVectorToListConversion() {
    if ( VERBOSE_TESTING ) cout << "START - Testing Vector to List - Activities" << endl;
    vector<Activity*> *activities = xmlActivitiesToVector(PATH_TO_XML_DIRECTORY + "testActivities.xml");
    List<Activity*> *activityList = activityVectorToLinkedList(activities);
    if ( VERBOSE_TESTING ) cout << "END - Testing Vector to List - Activities" << endl << endl;
    if ( VERBOSE_TESTING ) cout << "START - Testing Vector to List - Events" << endl;
    vector<Event*> *events = xmlEventsToVector(PATH_TO_XML_DIRECTORY + "testEvents.xml");
    List<Event*> *eventList = eventVectorToLinkedList(events);
    if ( VERBOSE_TESTING ) cout << "END - Testing Vector to List - Events" << endl << endl;
    delete activityList;
    delete eventList;
}

void TestUnit::testLinkedList() {
    // Read in the Activities from an XML File
    XMLReader *activitiesXML = new XMLReader( PATH_TO_XML_DIRECTORY + "testActivities.xml");
    
    // Get a vector of the list Activities
    
    vector<XMLNode*> *activityNodes = new vector<XMLNode*>();
    
    // Get the List of XMLNodes for "Activity" from the XML
    activityNodes = &activitiesXML->getRoot()->getChildren()->at("Activity");
    
    
    /* TO VECTOR
     // Create a vector of Activity
     vector<Activity*> *activities = new vector<Activity*>();
     
     // Convert the Nodes to Activities
     for (int i = 0; i < activityNodes->size(); i++) {
     // Create Activity from Node i and add it to the list
     activities->push_back(new Activity(*activityNodes->at(i)));
     }
     
     // Add the Activities to the list
     // TO LIST FROM VECTOR
     for (int i = 0; i < activities->size(); i++) {
     activityList->push_back(activities->at(i));
     }
     */
    
    // Create new LinkedList
    List<Activity*> *activityList = new List<Activity*>();
    
    // TO LIST FROM XMLNodes VECTOR
    for (int i = 0; i < activityNodes->size(); i++) {
        activityList->push_back(new Activity(*activityNodes->at(i)));
    }
    
    if ( VERBOSE_TESTING ) {
        // Print the list
        cout << "START -- List<Activity*> activityList:" << endl;
        for (List<Activity*>::iterator iter = activityList->begin();
             iter != activityList->end(); ++iter)
        {
            cout << (*iter)->toString() << endl;
        }
        cout << "END -- List<Activity*> activityList:" << endl;
    }
}

void TestUnit::testXMLReader(string path) {
    // Create an XMLReader from the path
    XMLReader *test = new XMLReader(path);
    
    // Output the XMLReader
    cout << test->toString() << endl;
    
    cout << "test root tagname: " << test->getRoot()->getTagName() << endl;
}

void TestUnit::testActivityObject() {
    
    // Parse String
    string activitiesXMLBuffer3 = "<Activities><Activity><id>1</id><units>6</units><startVertex>0</startVertex><endVertex>1</endVertex></Activity><Activity><id>2</id><units>3</units><startVertex>0</startVertex><endVertex>4</endVertex></Activity></Activities>";
    
    string activitiesXMLBuffer4 = "<Activities>\n\t<Activity>\n\t\t<id>1</id>\n\t\t<units>6</units>\n\t\t<startVertex>0</startVertex>\n\t\t<endVertex>1</endVertex>\n\t</Activity>\n\t<Activity>\n\t\t<id>2</id>\n\t\t<units>3</units>\n\t\t<startVertex>0</startVertex>\n\t\t<endVertex>4</endVertex>\n\t</Activity>\n</Activities>";
    
    //cout << formatForXMLReader(activitiesXMLBuffer4) << endl;
    
    // Parse String for activity nodes
    XMLNode *activitiesNode = new XMLNode(activitiesXMLBuffer3);
    activitiesNode = activitiesNode->stripTagAndContent(activitiesXMLBuffer3);
    
    // Get the vector of Activity nodes
    vector<XMLNode*> activityNodes = activitiesNode->getChildren()->at("Activity");
    
    // Get an activityNode
    XMLNode *actNode = activityNodes.at(0);
    
    // Create an activity from actNode
    Activity *activityObject = new Activity(*actNode);
    
    // Output the activity to the console
    cout << activityObject->toString() << endl;
    
    // Output Tree Structure
    cout << activitiesNode->toTreeString(0) << endl;
    
}

void TestUnit::testXMLNode() {
    // activitiesXML Find Children
    string activitiesXMLBuffer1 = "<Activities></Activities>";
    string activitiesXMLBuffer2 = "<Activities><Activity><id><val>1</val></id><units>6</units><startVertex>0</startVertex><endVertex>1</endVertex></Activity></Activities>";
    string activitiesXMLBuffer3 = "<Activities><Activity><id><val>1</val></id><units>6</units><startVertex>0</startVertex><endVertex>1</endVertex></Activity><Activity><id><val>1</val></id><units>6</units><startVertex>0</startVertex><endVertex>1</endVertex></Activity></Activities>";
    
    // Create a node from Buffered Input
    XMLNode *activitiesXML = new XMLNode("Activities", activitiesXMLBuffer3);
    
    //XMLNode *activitiesXML = new XMLNode("Activities");
    activitiesXML = activitiesXML->stripTagAndContent(activitiesXMLBuffer3);
    cout << activitiesXML->toString() << endl;
    
    /* SINGLE XMLNode*
     XMLNode &activityNode = activitiesXML->getChildren().at("Activity");
     cout << "activityNode: " << activityNode.toString() << endl;
     
     cout << activityNode.toString() << endl;
     
     for (int i = 0; i < activityNode.getChildren().size(); i++) {
     XMLNode node = activityNode.getChildren().at(activityNode.getFields().at(i));
     cout << node.getTagName() << ": " << endl << node.toString() << endl;
     }
     */
    
    
    // Get the vector of Acivity
    vector<XMLNode*> activities = activitiesXML->getChildren()->at("Activity");
    cout << "vector<XMLNode*> activities.size: " << activities.size() << endl;
    for (int i = 0; i < activities.size(); i++) {
        // Get the next Activity
        XMLNode *n = activities.at(i);
        cout << n->getTagName() << ":: " << endl << n->toString() << endl;
        
    }
    
}
/*
 string TestUnit::formatForXMLReader(string s) {
 // Remove all tabs and newlines
 s.erase(remove(s.begin(), s.end(), '\t'), s.end());
 s.erase(remove(s.begin(), s.end(), '\n'), s.end());
 
 return s;
 }
 */