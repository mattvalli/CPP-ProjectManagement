//
//  XMLReader.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 10/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

/***************************************************************************************************
 PURPOSE:   Builds a Data Structure of Objects from an XML file through recursive methods designed 
            to parse a file for XML Nodes store the values as strings
 
 
 ***************************************************************************************************/

#include "XMLReader.h"
#include <fstream>

using namespace std;

// DEBUG
const bool XMLReader::DEBUG_CONSTRUCTORS = false;

// CONSTUCTORS
XMLReader::XMLReader(string filepath) {
    mFilename = filepath;
    mRootNode = nullptr;
    
    // Get the Contents of the File at the filepath
    ifstream ifs(filepath);
    string content( (istreambuf_iterator<char>(ifs) ),
                        (istreambuf_iterator<char>()    ) );
    
    if (DEBUG_CONSTRUCTORS) {
        cout << toString() << endl;
        cout << "FILE CONTENTS:\n" << content << endl;
    }
    
    // Strip the string of newlines/tabs
    content = formatForXMLReader(content);
    
    // Create an XMLNode from the the content
    mRootNode = new XMLNode(content);
    mRootNode = mRootNode->stripTagAndContent(content);
    
    if (DEBUG_CONSTRUCTORS) {
        cout << "mRootNode - contents:\n" << mRootNode->getContents() << endl;
    }
}


// CONVENIENCE METHODS
string XMLReader::toString() {
    string output = "XMLReader Object\n";
    
    output += "mFilename: " + mFilename + "\n";
    
    if (mRootNode != nullptr) {
        output += "mRootNode: " + mRootNode->getTagName() + "\n";
    } else {
        output += "mRootNode: Null\n";
    }
   
    return output;
}

string XMLReader::toTreeString() {
    string output = "XMLReader - Xml Document as Object\n";
    
    if (mRootNode != nullptr) {
        output += mRootNode->toTreeString(0);
    } else {
        output += "mRootNode is null!";
    }
    
    return output;
}

string XMLReader::formatForXMLReader(string s) {
    // Remove all tabs and newlines
    s.erase(remove(s.begin(), s.end(), '\t'), s.end());
    s.erase(remove(s.begin(), s.end(), '\n'), s.end());
    
    return s;
}

// ACCESSOR METHODS
XMLNode* XMLReader::getRoot() {
    return mRootNode;
}

