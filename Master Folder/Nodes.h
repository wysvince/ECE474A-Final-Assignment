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
	int asapTime;
	int alapTime;
	int listRTime;
	int slack;
	int cycleCount;
	bool checked;

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

	//Methods
	void addEdge(Edges newEdge);
	int calculateSlack(int alapTime, int currCycle);

};

#endif	// !NODES_H