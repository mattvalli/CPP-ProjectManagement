//
//  main.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 9/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <iostream>
#include "ProjectManagementViewController.h"

using namespace std;


// FUNCTION PROTOTYPES
    // APP
    void run();
string projectCredits(vector<string> &authors, int marginTop = 0, int tabToCenter = 0);


int main(int argc, const char * argv[]) {
    // Log Entry
    cout << "\t\tMatValSoft Project - Direct Acyclic Graphs - Activity on Edge\n";
    
    // TESTING
    //test();
    
    // APP
    run();
    
    // Apply Credits
    vector<string> *authors = new vector<string>();
    authors->push_back("Matthew Valli");
    
    cout << projectCredits(*authors, 3, 6);
    
    return 0;
}

void run() {
    // Create an instance of the ProjectManagementViewController
    ProjectManagementViewController *controller = new ProjectManagementViewController();
    
    // Run the ViewController
    controller->run();
}

string projectCredits(vector<string> &authors, int marginTop, int tabToCenter) {
    string output = "";
    string centeringTabs = "";
    
    // Buffer of tabs for centering text
    for (int i = 0; i < tabToCenter; i++) centeringTabs += "\t";
    
    // Add Top Margin
    for (int i = 0; i < marginTop; i++) output+= "\n";
    
    
    // Credit Label
    output += centeringTabs + "This project was developed by:\n\n";
    
    // Loop through Authors
    for (int j = 0; j < authors.size(); j++) {
        output += centeringTabs + "\t\t " + authors.at(j) + "\n";
    }
    
    // Add Top Margin
    for (int i = 0; i < marginTop; i++) output+= "\n";
    
    return output;
}
