#pragma once
#ifndef GRAPH_H
#define GRAPH_H

class Edges;
class Nodes;

#include "Edges.h"
#include "Nodes.h"
#include "Operations.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Graph {

private:
	vector<Nodes> nodes;
	vector<Edges> edges;						// Change from Alex's Read file.
	int weight;
	vector<int> alapSchedule;

	// List R Scheduling:
	vector<Nodes> listRSchedule;
	vector<Nodes> U; // candidate operations (Node's index)
	vector<Nodes> S; // scheduled nodes

public:
	// constructors
	Graph();
	//Graph(Nodes newNodes, Edges newEdges, int newWeight);
	Graph(Nodes newNodes, int newWeight);

	//setters
	void setNodes(Nodes newNodes);
	void setEdges(Edges newEdges);				// Change from Alex's Read file.
	void setWeight(int newWeight);
	void setAlapSchedule(int num);
	void setListRSchedule(Nodes node);

	//getters
	vector<Nodes> getNodes();
	vector<Edges> getEdges();					// Change from Alex's Read file. 
	unsigned int getNumNodes();					// Change from Alex's Read file.
	int getWeight();
	vector<int> getAlapSchedule();
	vector<Nodes> getListRSchedule();

	//methods
	// void generateALAPTimeTable(); // unsure where to place this yet
	// void generateList_RSchedule(); // unsure where to plae this yet
	//void calculateWeights(Operations &op);
	void createListRSchedule(int latency);
	void updateU(Nodes node);
	void updateS();
	bool checkConstraint(Nodes node);
	void createUnscheduledList();
	void createALAPSchedule(int latency);
	void checkALAP(int latency);
	void addNode(Nodes newNode, int ifStatementLevel, vector<string> conditionVariables);				// Change from Alex's Read file.
	void Schedule();
};

#endif // !GRAPH_H