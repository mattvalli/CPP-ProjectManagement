//
//  Activity.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 11/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

/***************************************************************************************************
 PURPOSE: MODEL CLASS representing an Activity
 
 Records the Activity Properties:
                         - Unique Id
                         - Unit (Representing Distance/Duration)
                         - Start Vertix (Event Source)
                         - End Vertix   (Event Destination)
 ***************************************************************************************************/

#include "Activity.h"
#include "XMLNode.h"


using namespace std;

// CONSTANTS
const long Activity::INVALID_SLACK = -1;

// CONSTRUCTORS
Activity::Activity(long uid, long unit, long startVertex, long endVertex) {
    Activity(uid, unit, startVertex, endVertex, INVALID_SLACK);
}
Activity::Activity(long uid, long unit, long startVertex, long endVertex, long slack) {
    mId = uid;
    mUnit = unit;
    mStartVertex = unit;
    mEndVertex = endVertex;
    mSlack = slack;
}
Activity::Activity(XMLNode &node) {
    // Get A list of the Children
    map<string, vector<XMLNode*>> children = *node.getChildren();
    vector<XMLNode*> id = children.at("id");
    vector<XMLNode*> unit = children.at("units");
    vector<XMLNode*> startVertex = children.at("startVertex");
    vector<XMLNode*> endVertex = children.at("endVertex");
    
    
    // Get the values from the list
    mId = stol(id.at(0)->getContents());
    mUnit = stol(unit.at(0)->getContents());
    mStartVertex = stol(startVertex.at(0)->getContents());
    mEndVertex = stol(endVertex.at(0)->getContents());
}

// CONVENIENCE METHODS
string Activity::toString() {
    string output = "ACTIVITY OBJECT\n";
    output += "id: " + to_string(mId) + "\n";
    output += "units: " + to_string(mUnit) + "\n";
    output += "startVertex: " + to_string(mStartVertex) + "\n";
    output += "endVertex: " + to_string(mEndVertex) + "\n";
    
    return output;
}

string Activity::reportString() {
    string output;
    
    output += "|\t   A" + to_string(mId) + "\t\t";
    output += "|\t\t" + to_string(mEarlyTime) + "\t\t";
    output += "|\t\t" + to_string(mLateTime) + "\t\t";
    output += "|\t\t" + to_string(mSlack) + "\t\t";
    output += "|\t   " + criticalString(isCritical()) + "\t\t|";
    
    return output;
}

string Activity::criticalString(bool isCritical) {
    string output;
    isCritical ? output = "Yes" : output = "No";
    return output;
}

void Activity::updateTime(vector<int>* ee, vector<int>* el) {
    calculateEarlyTime(ee);
    calculateLateTime(el);
    mSlack = calculateSlack(mEarlyTime, mLateTime);
}

bool Activity::isCritical() {
    bool r;
    mSlack == 0 ? r = true : r = false;
    return r;
}

void Activity::calculateEarlyTime(vector<int>* ee) {
    mEarlyTime = ee->at(mStartVertex);
}

void Activity::calculateLateTime(vector<int>* el) {
    mLateTime = el->at(mEndVertex) - mUnit;
}


long Activity::calculateSlack(long earlyTime, long lateTime) {
    return lateTime - earlyTime;
}

// ACCESSORS
long Activity::getId() {
    return mId;
}
void Activity::setId(long uid) {
    mId = uid;
}
long Activity::getUnit() {
    return mUnit;
}
void Activity::setUnit(long unit) {
    mUnit = unit;
}
long Activity::getStartVertex() {
    return mStartVertex;
}
void Activity::setStartVertex(long startVertex) {
    mStartVertex = startVertex;
}
long Activity::getEndVertex() {
    return mEndVertex;
}
void Activity::setEndVertex(long endVertex) {
    mEndVertex = endVertex;
}
long Activity::getEarlyTime() {
    return mEarlyTime;
}
void Activity::setEarlyTime(long time) {
    mEarlyTime = time;
}
long Activity::getLateTime() {
    return mLateTime;
}
void Activity::setLateTime(long time) {
    mLateTime = time;
}
long Activity::getSlack() {
    return mSlack;
}
void Activity::setSlack(long slack) {
    mSlack = slack;
}