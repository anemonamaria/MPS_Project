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
    time_t timeVar;
    srand((unsigned) time(&timeVar));

    // c++11 random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, functions.array.size() - 1);

    int functionIndex = dis(gen);
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