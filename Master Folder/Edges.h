#pragma once
#ifndef EDGES_H
#define EDGES_H

#include "Nodes.h"

#include <string>
#include <iostream>

using namespace std;

class Nodes;

class Edges {

private:
	string conditionalOperation;	// Condition if it is an if/else
	int prevNode;					// Index of previous node in nodes (points to current node).
	int nextNode;					// Index of next node in nodes     (points to next node).

public:
	// constructors
	Edges();
	Edges(string condOp, int newPrevNode, int newNextNode);

	//setters
	void setCondtionalOperation(string condOp);
	void setPrevNode(int newPrevNode);
	void setNextNode(int newNextNode);
	void init();

	//getters
	string getConditionalOperation();
	int getPrevNode();
	int getNextNode();
	
	//Methods
	void printEdge();
};

#endif // !EDGES_H
