//
//  ProjectManagementCommandLine.h
//  ProjectManagement
//
//  Created by Matthew Valli on 18/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__CommandLine__
#define __ProjectManagement__CommandLine__

#include <iostream>
#include <string>

using namespace std;

class CommandLine {
private:
    // MEMBERS
    string mResponse;
    
public:
    CommandLine();
    ~CommandLine();
    
    
    //
    string promptMessage(string message);
    string getResponse();
};

#endif /* defined(__ProjectManagement__ProjectManagementCommandLine__) */
