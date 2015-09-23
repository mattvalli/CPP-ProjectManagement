//
//  TestUnit.h
//  ProjectManagement
//
//  Created by Matthew Valli on 17/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__TestUnit__
#define __ProjectManagement__TestUnit__

#include <iostream>
#include <vector>
#include "List.cpp"
#include "XMLReader.h"
#include "Activity.h"
#include "Event.h"


class TestUnit {
private:
    // DEBUG
    static const bool VERBOSE_TESTING;
    
    // CONSTANTS
    static const string PATH_TO_XML_DIRECTORY;
    
public:
    // Testing
    void test();
    // Data Conversion
    void testDataConversions();
    void testListToVectorConversion();
    void testVectorToListConversion();
    
    // Preliminary Testing
    void testXMLNode();
    void testActivityObject();
    void testXMLReader(string path);
    void testLinkedList();
    string formatForXMLReader(string s);
    
    // CONVENIENCE METHODS
    // Activities
    // LinkedList
    List<Activity*>* xmlActivitiesToLinkedList(string absPathToXML);
    List<Activity*>* activityVectorToLinkedList(vector<Activity*>* v);
    // Vector
    vector<Activity*>* xmlActivitiesToVector(string absPathToXML);
    vector<Activity*>* activityLinkedListToVector(List<Activity*>* list);
    // Events
    // LinkedList
    List<Event*>* xmlEventsToLinkedList(string absPathToXML);
    List<Event*>* eventVectorToLinkedList(vector<Event*>* v);
    // Vector
    vector<Event*>* xmlEventsToVector(string absPathToXML);
    vector<Event*>* eventLinkedListToVector(List<Event*>* list);
};

#endif /* defined(__ProjectManagement__TestUnit__) */
