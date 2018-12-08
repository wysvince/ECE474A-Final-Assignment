#pragma once
#ifndef NODES_H
#define NODES_H
 
#include "Edges.h" 

#include <string> 
#include <vector>
#include <iostream>

using namespace std;

class Edges;

class Nodes {

private:
	int nodeNum;
	int asapTime;
	int alapTime;
	int numCycles;
	int ifStatementLevel;
	bool withinElse;
	vector<Edges> edges;
	string operation;
	vector<string> variablesInvolved; //First variable is always the output

public:
	// constructor
	Nodes();
	Nodes(int newStateNum, Edges newEdges, int newNumCycles, string op);

	//setters
	void setNodeNum(int newStateNum);
	void setAsapTime(int newTime);
	void setAlapTime(int newTime);
	void setNumCycles(int newNumCycles);
	void setIfStatementLevel(int level);
	void setEdges(Edges newEdges);
	void setOperation(string op);
	void setVariablesInvolved(vector<string> vbs);
	void setWithinElse(bool b);

	//getters
	int getNodeNum();
	int getAsapTime();
	int getAlapTime();
	int getNumCycles();
	int getIfStatementLevel();
	vector<Edges> getEdges();
	string getOperation();
	vector<string> getVariablesInvolved();
	string getOutputVariable();
	bool getWithinElse();

	//Methods
	void addEdge(Edges newEdge);
	void printNode();
	bool hasConditionalEdge();
	bool hasElseEdge();

};

#endif	// !NODES_H