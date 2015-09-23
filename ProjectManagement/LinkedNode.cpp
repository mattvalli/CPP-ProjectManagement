//
//  LinkedNode.cpp
//  ProjectManagement
//
//  Created by Matthew Valli on 16/03/2015.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef __ProjectManagement__LinkedNode__
#define __ProjectManagement__LinkedNode__

#include <iostream>



template <typename T>
class LinkedNode {
private:
    T *mDataObject;
    LinkedNode<T> *mNextNode;
    
public:
    typedef T value_type;
    // CONSTRUCTORS
    LinkedNode(T *dataObject, LinkedNode *nextNode) : mDataObject(dataObject), mNextNode(nextNode) {}
    LinkedNode(T *dataObject) : mDataObject(dataObject), mNextNode(nullptr) {}
    LinkedNode() : mDataObject(nullptr), mNextNode(nullptr) {}
    
    
    // ACCESSOR METHODS
    T* getData() {
        return mDataObject;
    }
    void setData(T *dataObj) {
        mDataObject = dataObj;
    }
    LinkedNode<T>* getNext() {
        return mNextNode;
    }
    void setNext(LinkedNode<T> *nextNode) {
        mNextNode = nextNode;
    }
	
    
};

#endif /* defined(__ProjectManagement__LinkedNode__) */