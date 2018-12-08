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
	// ADDED in from Alex S's Read file. ----------------------------------
	int nodeNum;
	int ifStatementLevel;
	bool withinElse;
	vector<string> variablesInvolved; //First variable is always the output
	//  -------------------------------------------------------------------
	int stateNum;
	vector<Edges> edges;
	int numCycles;
	string operation;
	int asapTime;
	int alapTime;
	int listRTime;
	int slack;
	int cycleCount;

public:
	// constructor
	Nodes();
	Nodes(int newStateNum, Edges newEdges, int newNumCycles, string op);

	//setters
	// ADDED in from Alex S's Read file. ----------------
	void setNodeNum(int newStateNum);
	void setIfStatementLevel(int level);
	void setVariablesInvolved(vector<string> vbs);
	void setWithinElse(bool b);
	//  -------------------------------------------------
	void setStateNum(int newStateNum);
	void setEdges(Edges newEdges);
	void setNumCycles(int newNumCycles);
	void setOperation(string op);
	void setSlack(int num);
	void setCycleCount(int num);
	void setASAP(int time);
	void setALAP(int time);
	void setListR(int time);
	void init();

	//getters
	// ADDED in from Alex S's Read file. ----------------
	int getNodeNum();
	int getIfStatementLevel();
	vector<string> getVariablesInvolved();
	string getOutputVariable();
	bool getWithinElse();
	//  -------------------------------------------------
	int getStateNum();
	vector<Edges> getEdges();
	int getNumCycles();
	string getOperation();
	int getSlack();
	int getCycleCount();
	int getALAP();
	int getASAP();
	int getListR();

	//Methods
	// ADDED in from Alex S's Read file. ----------------
	void printNode();
	bool hasConditionalEdge();
	bool hasElseEdge();
	//  -------------------------------------------------
	void addEdge(Edges newEdge);		// Modified with Alex S's code.
	void calculateSlack(int alapTime, int currCycle);

};

#endif	// !NODES_H