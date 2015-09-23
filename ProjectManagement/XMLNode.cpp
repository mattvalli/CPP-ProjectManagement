//
//  XMLNode.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 10/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

/***************************************************************************************************
 PURPOSE: MODEL CLASS representing an XML Node from a File
 
 ***************************************************************************************************/

#include "XMLNode.h"

using namespace std;

// CONSTANTS
const int XMLNode::NO_CHILD = -1;
const bool XMLNode::DEBUG_NODES = false;
const bool XMLNode::DEBUG_EXPLORE_CHILDREN = false;
const bool XMLNode::DEBUG_FIND_CHILDREN = false;
const bool XMLNode::DEBUG_STRIP_CHILDREN = false;
const bool XMLNode::DEBUG_PROCESS_CONTENT = true;
const int XMLNode::LENGTH_OFFSET = -1;

// CONSTRUCTOR
XMLNode::XMLNode() {
    //XMLNode("","");
}
XMLNode::XMLNode(string buffer) {
    XMLNode("",buffer);
}
XMLNode::XMLNode(string tagName, string buffer) {
    mTagName = tagName;
    mContents = buffer;
    mChildNodes = new map<string, vector<XMLNode*> >();
    //mChildNodes = new map<string, XMLNode&>();
    mFields = new vector<string>();
    
    // Process the Buffer
    //processContent(buffer);
    // Find the Children of the Node
    exploreForChildren();
}
XMLNode::~XMLNode() {
    delete mChildNodes;
    delete mFields;
}

// OVERRIDES
string XMLNode::toString() {
    string str = "XMLNODE\n";
    str += "mTagName: " + mTagName + "\n";
    str += "mContent: " + mContents + "\n";
    /**/
    str += "Children:\n";
    if (mFields->size() == 0) str += "\tNO CHILDREN\n";
    for (int i = 0; i < mFields->size(); i++) {
        str += "\t" + mFields->at(i) + "\n";
    }
    return str;
}

string XMLNode::toTreeString(int initialTabCount) {
    //string output = "XMLNode - Tree Structure";
    // Start with the Tagname
    string output = generateTabs(initialTabCount) + " - " +  mTagName + "\n";
    // Mark Decent
    output += generateTabs(initialTabCount + 1) + "|\n";
    
    
     // If there are no children, break the loop
     if (mFields->size() == 0) {
     output += generateTabs(initialTabCount + 2) + " - No Children - Value: " + mContents + "\n";
     } else {
    
        // Output all the children
        for (int i = 0; i < mChildNodes->size(); i++) {
            
             
            // Get the vector for the current Child Node Type
            vector<XMLNode*> currentChildType = mChildNodes->at(getFields().at(i));
            
            // Ouput the Children and their tree structure recursively
            for (int j = 0; j < currentChildType.size(); j++) {
                
                // Get the next node
                XMLNode* currentChildTypeNode = currentChildType.at(j);
                // Build string of children
                output += currentChildTypeNode->toTreeString(initialTabCount + 2) + "\n";
            }
        }
     }

    return output;
}


// ACCESSOR METHODS
string XMLNode::getTagName() {
    return mTagName;
}

string XMLNode::getContents() {
    return mContents;
}

void XMLNode::setContents(string newContent) {
    mContents = newContent;
}

// CONVENIENCE METHODS
bool XMLNode::hasChildren() {
    return mChildNodes->empty();
}

vector<string>& XMLNode::getFields() {
    return *mFields;
}

//map<string, vector<XMLNode&>> XMLNode::getChildren() {
//map<string, vector<XMLNode&>>& XMLNode::getChildren() {
map<string, vector<XMLNode*>>* XMLNode::getChildren(){
    return mChildNodes;
}
/*
map<string, XMLNode&>& XMLNode::getChildren() {
    return *mChildNodes;
}
*/
bool XMLNode::findChildren(string content) {
    // Initialize return value
    bool hasChildren = false;
    
    if (DEBUG_FIND_CHILDREN) cout << "content.length(): " << content.length() << endl;
    
    // Begin Search
    long openTag_startPos = content.find("<");
    
    while (openTag_startPos != string::npos) {
        // Initialize Search Vars
        long openTag_endPos = 0;
        long closeTag_startPos = 0;
        long closeTag_endPos = 0;
        
        // Begin Search
        openTag_startPos = content.find("<");
        
        if (openTag_startPos != string::npos) {
            // THERE IS A MATCH
            hasChildren = true;
            // Find the closing tag
            openTag_endPos = content.find(">");
            
            if (DEBUG_FIND_CHILDREN) {
                string output = "PHASE 1\n";
                output += "openTag_startPos: " + to_string(openTag_startPos) + "\n";
                output += "openTag_endPos: " + to_string(openTag_endPos) + "\n";
                //output += "closeTag_startPos: " + to_string(closeTag_startPos) + "\n";
                //output += "closeTag_endPos: " + to_string(closeTag_endPos) + "\n";
                output += "content: " + content + "\n";
                
                cout << output;
            }
            
            // Get the TagName
            string tagName = content.substr(openTag_startPos + 1, openTag_endPos + LENGTH_OFFSET);
            if (DEBUG_FIND_CHILDREN) {
                string output = "PHASE 2\n";
                    output +="tagName: " + tagName + "\n";
                    output += "openTag_startPos: " + to_string(openTag_startPos) + "\n";
                    output += "openTag_endPos: " + to_string(openTag_endPos) + "\n";
                    output += "closeTag_startPos: " + to_string(closeTag_startPos) + "\n";
                    output += "closeTag_endPos: " + to_string(closeTag_endPos) + "\n";
            
                cout << output;
            }
            
            
            // Add the TagName to the mFields
            //mFields->push_back(tagName);
            
            // Shift the Contents
            if (DEBUG_FIND_CHILDREN) {
                string output;
                if (openTag_endPos > (content.length() - LENGTH_OFFSET)) {
                    output = to_string(openTag_endPos) + " > " + to_string(content.length()) + " - Out of range!\n";
                } else {
                    output = to_string(openTag_endPos) + " > " + to_string(content.length()) + " - In range!";
                }
            }
            
            
            // Reset the content
            //content = content.substr(openTag_endPos + 1, closeTag_startPos -1);
            
            
            // Finish Search
            string endTag = "</" + tagName + ">";
            closeTag_startPos = content.find(endTag) - endTag.length() + 2;
            closeTag_endPos = content.find(endTag);
            
            
            
            // Select the content using substring and set the content and tagContent to the value of the substring
            string tagContent = content.substr(openTag_endPos + 1, closeTag_startPos - 1);
            if (DEBUG_FIND_CHILDREN) {
                string output = "PHASE 3\n";
                output += "tagName: " + tagName + "\n";
                output += "openTag_startPos: " + to_string(openTag_startPos) + "\n";
                output += "openTag_endPos: " + to_string(openTag_endPos) + "\n";
                output += "closeTag_startPos: " + to_string(closeTag_startPos) + "\n";
                output += "closeTag_endPos: " + to_string(closeTag_endPos) + "\n";
                output += "tagContent: " + tagContent + "\n";
                
                cout << output;
            }
            
            //if (DEBUG_FIND_CHILDREN) { cout << "GOT HERE" << endl; }
            
            // Construct the ChildNode from the Current vars
            XMLNode *newNode = new XMLNode(tagName, tagContent);
            cout << newNode->toString() << endl;
            //newNode->setContents(tagContent);
            
            // Add the newNode to the hashMap
            //mChildNodes->insert(pair<string, XMLNode&>(tagName, *newNode));
            
            // Find next tag
            if (closeTag_endPos + 1 < content.length()) {
                // Set the first character of content to be after the previous closing tag
                content = content.substr(closeTag_startPos + 2);
                // Search for a new tag
                openTag_startPos = content.find("<");
            } else {
                // We have run the whole string
                break;
            }
        }
    }
    return hasChildren;
}

void XMLNode::exploreForChildren() {
    
    if (DEBUG_NODES) { cout << "ENTER exploreForChildren()" << endl; }
    // Initialize for Children
    string contentCopy = mContents;
    if (DEBUG_EXPLORE_CHILDREN) { cout << "contentCopy: " << contentCopy << endl; }
    
    // Use loop and a half to break
    while (true) {
        
        // Find the Next Node
        XMLNode* nextNode = stripTagAndContent(contentCopy);
        
        // Only Continue if there is a Node to process
        if (nextNode == nullptr) {
            return;
        } else {
            string tag = nextNode->getTagName();
            if (DEBUG_EXPLORE_CHILDREN) { cout << tag << " pre-loop: " << contentCopy << endl; }
            //cout << "tag: " << tag << endl;
            
            /**/
            if (!containsTag(tag)) {
                // Create a new vector of XMLNode references
                vector<XMLNode*> *nextRefVector = new vector<XMLNode*>();
                
                // Add the Node Reference to the map
                mChildNodes->insert(map<string,vector<XMLNode*>>::value_type(nextNode->getTagName(), *nextRefVector));
                
                // Add the Node TagName to the list of Fields
                mFields->push_back(nextNode->getTagName());
            }
            
            // Add the XMLNode to the Vector of XMLNodes defined by a tagName
            mChildNodes->at(tag).push_back(nextNode);
            
            
            /*
            // Add the XMLNode to the Vector of XMLNodes defined by a tagName
            mChildNodes->insert(pair<string,XMLNode&>(tag, nextNode));
            
            // Add the Node TagName to the list of Fields
            mFields->push_back(nextNode->getTagName());
             */
            
            // TRAVERSE TO NEXT CHILD
            // Remove nextNode from content string
            if (DEBUG_EXPLORE_CHILDREN) { cout << "nextNode - " << tag << " - Content: " << nextNode->getContents() << endl; }
            string closeTag = "</" + nextNode->getTagName() + ">";
            long endOfNextNode = contentCopy.find(closeTag) ;
            long endPos =  endOfNextNode + closeTag.length();
            
            // Exit via Loop-and-a-Half if greater than the length of the content
            if (endPos >= contentCopy.length() - 1) break;
            
            contentCopy = contentCopy.substr(endPos);
            if (DEBUG_EXPLORE_CHILDREN) { cout << tag << " - post-loop: " << contentCopy << endl; }
        }
    }
    if (DEBUG_NODES) { cout << "EXIT exploreForChildren()" << endl; }
}

XMLNode* XMLNode::stripTagAndContent(string content) {
    if (DEBUG_NODES) { cout << "ENTER strinpTagAndContent(string content)" << endl; }
    
    
    // Initialize return value
    XMLNode *newNode = nullptr;
    
    if (DEBUG_STRIP_CHILDREN) cout << "content.length(): " << content.length() << endl;
    
    // Begin Search
    long openTag_startPos = content.find("<");
    
    // Initialize Search Vars
    long openTag_endPos = 0;
    long closeTag_startPos = 0;
    long closeTag_endPos = 0;
    
    // Begin Search
    openTag_startPos = content.find("<");
    
    if (openTag_startPos == string::npos) { return nullptr; }
    if (openTag_startPos != string::npos) {
        // Find the closing tag
        openTag_endPos = content.find(">");
        
        if (DEBUG_STRIP_CHILDREN) {
            string output = parseTracking("PHASE 1", openTag_startPos, openTag_endPos, closeTag_startPos, closeTag_startPos);
            output += "content: " + content + "\n";
            cout << output << endl;
        }
        
        // Get the TagName
        string tagName = content.substr(openTag_startPos + 1, openTag_endPos + LENGTH_OFFSET);
        
        
        if (DEBUG_STRIP_CHILDREN) {
            string output = parseTracking("PHASE 2", openTag_startPos, openTag_endPos, closeTag_startPos, closeTag_startPos);
            cout << output << endl;
        }
        
        
        // Finish Search
        string endTag = "</" + tagName + ">";
        closeTag_startPos = content.find(endTag) - endTag.length() + 2;
        closeTag_endPos = content.find(endTag);
        
        
        // Select the content using substring and set the content and tagContent to the value of the substring
        string tagContent = content.substr(openTag_endPos + 1, closeTag_startPos - 1);
        
        
        if (DEBUG_STRIP_CHILDREN) {
            string output = parseTracking("PHASE 3", openTag_startPos, openTag_endPos, closeTag_startPos, closeTag_startPos);
            output += "tagName: " + tagName + "\n";
            output += "tagContent: " + tagContent + "\n";
            cout << output << endl;
        }
        
        // Construct the ChildNode from the Current vars
        newNode =  new XMLNode(tagName, tagContent);
        if (DEBUG_STRIP_CHILDREN) { cout << newNode->toString() << endl; }
    }
    
    
    if (DEBUG_NODES) { cout << "EXIT strinpTagAndContent(string content)" << endl; }
    return newNode;
}


void XMLNode::processContent(string content) {
    if (DEBUG_NODES || DEBUG_PROCESS_CONTENT) { cout << "ENTER processContent(string content)" << endl; }
    
    if (DEBUG_PROCESS_CONTENT) cout << "content.length(): " << content.length() << endl;
    
    // Begin Search
    long openTag_startPos = content.find("<");
    
        // Initialize Search Vars
        long openTag_endPos = 0;
        long closeTag_startPos = 0;
        long closeTag_endPos = 0;
        
        // Begin Search
        openTag_startPos = content.find("<");
    
    //if (openTag_startPos == string::npos) { return; }
        if (openTag_startPos != string::npos) {
            // Find the closing tag
            openTag_endPos = content.find(">");
            
            if (DEBUG_PROCESS_CONTENT) {
                string output = parseTracking("PHASE 1", openTag_startPos, openTag_endPos, closeTag_startPos, closeTag_startPos);
                output += "content: " + content + "\n";
                cout << output << endl;
            }
            
            // Get the TagName
            mTagName = content.substr(openTag_startPos + 1, openTag_endPos + LENGTH_OFFSET);
            if (DEBUG_PROCESS_CONTENT) { cout << mTagName << endl; }
            
            if (DEBUG_PROCESS_CONTENT) {
                string output = parseTracking("PHASE 2", openTag_startPos, openTag_endPos, closeTag_startPos, closeTag_startPos);
                cout << output << endl;
            }
            
            
            // Finish Search
            string endTag = "</" + mTagName + ">";
            closeTag_startPos = content.find(endTag) - endTag.length() + 2;
            closeTag_endPos = content.find(endTag);
            
            
            // Select the content using substring and set the content and tagContent to the value of the substring
            mContents = content.substr(openTag_endPos + 1, closeTag_startPos - 1);
            if (DEBUG_PROCESS_CONTENT) { cout << mContents << endl; }
            
            if (DEBUG_PROCESS_CONTENT) {
                string output = parseTracking("PHASE 3", openTag_startPos, openTag_endPos, closeTag_startPos, closeTag_startPos);
                output += "tagName: " + mTagName + "\n";
                output += "tagContent: " + mContents + "\n";
                cout << output << endl;
            }
            
        }
    
    if (DEBUG_NODES || DEBUG_PROCESS_CONTENT) { cout << "EXIT processContent(string content)" << endl; }
}



// PRIVATE - HELPER METHODS
string XMLNode::getFirstTagName(string content) {
    string tagName;
    
    // Begin Search
    long openTag_startPos = content.find("<");
    
    // Initialize Search Vars
    long openTag_endPos = 0;
    
    // Begin Search
    openTag_startPos = content.find("<");
    
    //if (openTag_startPos == string::npos) { return; }
    if (openTag_startPos != string::npos) {
        // Find the closing tag
        openTag_endPos = content.find(">");
    }
        
    // Get the TagName
    tagName = content.substr(openTag_startPos + 1, openTag_endPos + LENGTH_OFFSET);
    
    
    return tagName;

}

string XMLNode::getFirstTagContent(string content) {
    string tagContent;
    
    return tagContent;
}

bool XMLNode::containsTag(string tagName) {
    bool val = false;
    (mChildNodes->count(tagName) == 1) ? val = true : val = false;
    return val;
}

string XMLNode::parseTracking(string phaseTitle, long openStart, long openEnd, long closeStart, long closeEnd) {
    
    string output = phaseTitle + "\n";
    output += "openTag_startPos: " + to_string(openStart) + "\n";
    output += "openTag_endPos: " + to_string(openEnd) + "\n";
    output += "closeTag_startPos: " + to_string(closeStart) + "\n";
    output += "closeTag_endPos: " + to_string(closeEnd) + "\n";
    
    return output;
}

string XMLNode::generateTabs(int numberOfTabs) {
    string output = "";
    for (int i = 0; i < numberOfTabs; i++) {
        output += "\t";
    }
    return output;
}

