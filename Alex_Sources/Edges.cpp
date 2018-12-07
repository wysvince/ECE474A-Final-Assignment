#include "Edges.h"
  
#include <string>
 
using namespace std;

Edges::Edges() {} // default constructor

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

//Methods
void Edges::printEdge() {
	//cout << "\tPrevious: Node-" << prevNode->getStateNum() << endl;
	cout << "\tNext Node:    Node " << nextNode << endl;
	if (!conditionalOperation.empty()) {
		cout << "\t    Condition:    " << conditionalOperation << endl;
	}
}
