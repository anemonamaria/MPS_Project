//
// Created by Bogdan on 03-Dec-22.
//

#include <random>
#include "Node.h"

Node::Node(Node *leftParent, Node *rightParent) {
    this->leftParent = leftParent;
    this->rightParent = rightParent;

    // Creates random number generator for extracting random function
    Functions functions;

    int functionIndex = rand() % functions.array.size();
    function = functions.array[functionIndex];
    functionName = functions.names[functionIndex];
    identifier = "";

    if (leftParent != nullptr && rightParent != nullptr) {
        threshold = function(leftParent->threshold, rightParent->threshold);
    }
}

Node::Node() : Node(nullptr, nullptr) {}

Node::Node(double value) : Node(nullptr, nullptr) {
    this->threshold = value;
}

// 1/ (1/(....)
// harmonicMean(harmonicMean).....)