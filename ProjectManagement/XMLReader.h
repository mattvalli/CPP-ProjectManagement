//
//  XMLReader.h
//  ProjectManagement
//
//  Created by Matthew Valli on 10/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__XMLReader__
#define __ProjectManagement__XMLReader__

#include <iostream>
#include "XMLNode.h"

using namespace std;

class XMLReader {
private:
    // DEBUG
    static const bool DEBUG_CONSTRUCTORS;
    
    // MEMBERS
    string mFilename;
    XMLNode *mRootNode;
    
public:
    // Constructor
    XMLReader(string filepath);
    
    // CONVENIENCE METHODS
    string toString();
    string toTreeString();
    string formatForXMLReader(string s);
    
    // Accessor Methods
    XMLNode* getRoot();
};


#endif /* defined(__ProjectManagement__XMLReader__) */
