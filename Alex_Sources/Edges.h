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
	string conditionalOperation;
	int prevNode;
	int nextNode;

public:
	// constructors
	Edges();
	Edges(string condOp, int newPrevNode, int newNextNode);

	//setters
	void setCondtionalOperation(string condOp);
	void setPrevNode(int newPrevNode);
	void setNextNode(int newNextNode);

	//getters
	string getConditionalOperation();
	int getPrevNode();
	int getNextNode();

	//Methods
	void printEdge();
};

#endif // !EDGES_H
