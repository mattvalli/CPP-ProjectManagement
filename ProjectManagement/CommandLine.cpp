//
//  ProjectManagementCommandLine.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 18/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include "CommandLine.h"

// CONSTRUCTORS
CommandLine::CommandLine() {}
CommandLine::~CommandLine() {}


// CONVENIENCE METHODS
string CommandLine::promptMessage(string message) {
    
    // Prompt the User
    cout << message << endl;
    
    // Get the input
    cin.ignore();
    getline(cin, mResponse);
    
    cout << mResponse << endl;
    
    return mResponse;
}


// ACCESSOR METHODS
string CommandLine::getResponse() {
    return mResponse;
}