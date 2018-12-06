#include "Edges.h"

#include <string>

using namespace std;

Edges::Edges() { this->conditionalOperation = " "; } // default constructor

Edges::Edges(string condOp, int newPrevNode, int newNextNode) {
	this->conditionalOperation = condOp;
	this->prevNode = newPrevNode;
	this->nextNode = newNextNode;
}

// setters
void Edges::setCondtionalOperation(string condOp) {
	this->conditionalOperation = condOp;
}

void Edges::setPrevNode(int newPrevNode) {
	this->prevNode = newPrevNode;
}

void Edges::setNextNode(int newNextNode) {
	this->nextNode = newNextNode;
}


void Edges::init() {
	this->conditionalOperation = "";
	this->prevNode = -1;
	this->nextNode = -1;
}

// getters
string Edges::getConditionalOperation() {
	return this->conditionalOperation;
}

int Edges::getPrevNode() {
	return this->prevNode;
}

int Edges::getNextNode() {
	return this->nextNode;
}