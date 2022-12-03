//
// Created by Bogdan on 03-Dec-22.
//

#include "Node.h"

Node::Node(Node *leftParent, Node *rightParent) {
    this->leftParent = leftParent;
    this->rightParent = rightParent;

    // Creates random number generator for extracting random function
    Functions functions;
    time_t timeVar;
    srand((unsigned) time(&timeVar));
    function = functions.array[rand() % functions.array.size()];

    if (leftParent != nullptr && rightParent != nullptr) {
        value = function(leftParent->value, rightParent->value);
    }
}

Node::Node() : Node(nullptr, nullptr) {}

Node::Node(double value) {
    this->value = value;
    leftParent = nullptr;
    rightParent = nullptr;

}

// 1/ (1/(....)
// harmonicMean(harmonicMean).....)