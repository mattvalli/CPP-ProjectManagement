//
//  XMLNode.h
//  ProjectManagement
//
//  Created by Matthew Valli on 10/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__XMLNode__
#define __ProjectManagement__XMLNode__

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class XMLNode {
private:
    // CONSTANTS
    static const int NO_CHILD;
    static const int LENGTH_OFFSET;
    // DEBUG
    static const bool DEBUG_NODES;
    static const bool DEBUG_FIND_CHILDREN;
    static const bool DEBUG_EXPLORE_CHILDREN;
    static const bool DEBUG_STRIP_CHILDREN;
    static const bool DEBUG_PROCESS_CONTENT;
    
    // MEMBERS
    string mTagName;
    string mContents;
    map<string, vector<XMLNode*>> *mChildNodes;
    //map<string, XMLNode&> *mChildNodes;
    vector<string> *mFields;
    
    // HELPER METHODS
    string getFirstTagName(string content);
    string getFirstTagContent(string content);
    static string parseTracking(string phaseTitle, long openStart, long openEnd, long closeStart, long closeEnd);
    string generateTabs(int numberOfTabs);
    
public:
    // CONSTRUCTOR
    XMLNode();
    XMLNode(string buffer);
    XMLNode(string tagName, string textToParse);
    // DESTRUCTOR
    ~XMLNode();
    
    // OVERRIDES
    string toString();
    string toTreeString(int initialTabCount);
    
    // ACCESSOR METHODS
    string getTagName();
    string getContents();
    void setContents(string newContent);
    
    // CONVENIENCE METHODS
    bool hasChildren();
    vector<string>& getFields();
    //map<string, vector<XMLNode&>> getChildren();
    map<string, vector<XMLNode*>>* getChildren();
    //map<string, XMLNode&>& getChildren();
    
    // HELPER METHODS
    void processContent(string content);
    bool findChildren(string content);
    static XMLNode* stripTagAndContent(string content);
    void exploreForChildren();
    bool containsTag(string tagName);
};

#endif /* defined(__ProjectManagement__XMLNode__) */
