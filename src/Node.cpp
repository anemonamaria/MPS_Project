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
    std::uniform_int_distribution<> dis(0,  functions.array.size() - 1);

    function = functions.array[dis(gen)];

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