#pragma once
#ifndef NODES_H
#define NODES_H

#include "Edges.h" 

#include <string> 
#include <vector>

using namespace std;

class Edges;

class Nodes {

private:
	int stateNum;
	vector<Edges> edges;
	int numCycles;
	string operation;
	int alapTime;

public:
	// constructor
	Nodes();
	Nodes(int newStateNum, Edges newEdges, int newNumCycles, string op);

	//setters
	void setStateNum(int newStateNum);
	void setEdges(Edges newEdges);
	void setNumCycles(int newNumCycles);
	void setOperation(string op);
	void setALAP(int time);

	//getters
	int getStateNum();
	vector<Edges> getEdges();
	int getNumCycles();
	string getOperation();
	int getALAP();

	//Methods
	void addEdge(Edges newEdge);

};

#endif	// !NODES_H