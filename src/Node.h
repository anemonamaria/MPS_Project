//
// Created by Bogdan on 03-Dec-22.
//

#ifndef MPS_PROJECT_NODE_H
#define MPS_PROJECT_NODE_H

#include "Functions.h"
#include <ctime>

class Node {
public:
    Node *leftParent;
    Node *rightParent;
    double value;
    Function function;

    Node();

    Node(Node *leftParent, Node *rightParent);

    // Constructor for leafs
    Node(double value);
};


#endif //MPS_PROJECT_NODE_H
