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
	int nodeNum;
	vector<Edges> edges;
	int numCycles;
	string operation;
	string resourceType;
	int asapTime;
	int alapTime;
	int listRTime;
	int slack;
	int cycleCount;
	bool checked;
	vector<string> variablesInvolved; //First variable is always the output
	int ifStatementLevel;
	bool withinElse;

public:
	// constructor
	Nodes();
	Nodes(int newStateNum, Edges newEdges, int newNumCycles, string op);

	//setters
	void setNodeNum(int newStateNum);
	void setEdges(Edges newEdges);
	void setNumCycles(int newNumCycles);
	void setOperation(string op);
	void setSlack(int num);
	void setCycleCount(int num);
	void setASAP(int time);
	void setALAP(int time);
	void setListR(int time);
	void init();
	void setChecked(bool);
	void setIfStatementLevel(int level);
	void setVariablesInvolved(vector<string> vbs);
	void setWithinElse(bool b);
	void setResourceType(string type);

	//getters
	int getNodeNum();
	vector<Edges> getEdges();
	int getNumCycles();
	string getOperation();
	int getSlack();
	int getCycleCount();
	int getALAP();
	int getASAP();
	int getListR();
	int getChecked();
	int getIfStatementLevel();
	vector<string> getVariablesInvolved();
	string getOutputVariable();
	bool getWithinElse();
	string getResourceType();

	//Methods
	void addEdge(Edges newEdge);
	int calculateSlack(int alapTime, int currCycle);
	void printNode();
	bool hasConditionalEdge();
	bool hasElseEdge();

};

#endif	// !NODES_H