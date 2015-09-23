//
//  Activity.h
//  ProjectManagement
//
//  Created by Matthew Valli on 11/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__Activity__
#define __ProjectManagement__Activity__

#include <iostream>
#include "XMLNode.h"

class Activity {
private:
    long mId;
    long mUnit;
    long mStartVertex;
    long mEndVertex;
    long mEarlyTime;
    long mLateTime;
    long mSlack;
    
public:
    // CONSTANTS
    static const long INVALID_SLACK;
    // CONSTRUCTORS
    Activity(long uid, long unit, long startVertex, long endVertex);
    Activity(long uid, long unit, long startVertex, long endVertex, long slack);
    Activity(XMLNode &node);
    
    // CONVENIENCE METHODS
    string toString();
    string reportString();
    string criticalString(bool isCritical);
    void updateTime(vector<int>* ee, vector<int>* el);
    void calculateEarlyTime(vector<int>* ee);
    void calculateLateTime(vector<int>* el);
    long calculateSlack(long earlyTime, long lateTime);
    bool isCritical();
    
    // ACCESSORS
    long getId();
    void setId(long uid);
    long getUnit();
    void setUnit(long unit);
    long getStartVertex();
    void setStartVertex(long startVertex);
    long getEndVertex();
    void setEndVertex(long endVertex);
    long getEarlyTime();
    void setEarlyTime(long time);
    long getLateTime();
    void setLateTime(long time);
    long getSlack();
    void setSlack(long slack);

};

#endif /* defined(__ProjectManagement__Activity__) */
