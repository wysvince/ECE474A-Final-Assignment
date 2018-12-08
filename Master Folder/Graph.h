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
	vector<Edges> edges;
	int weight;
	vector<int> alapSchedule;

	// List R Scheduling:
	vector<int> listRSchedule;
	vector<int> U; // candidate operations (Node's index)
	vector<int> S; // scheduled nodes

public:
	// constructors
	Graph();
	//Graph(Nodes newNodes, Edges newEdges, int newWeight);
	Graph(Nodes newNodes, int newWeight);

	//setters
	void setNodes(Nodes newNodes);
	void setEdge(Edges newEdges);
	void setWeight(int newWeight);
	void setAlapSchedule(int num);
	void setListRSchedule(int node);

	//getters
	vector<Nodes> getNodes();
	vector<Edges> getEdges();
	int getWeight();
	int getNumNodes();
	vector<int> getAlapSchedule();
	vector<int> getListRSchedule();

	//methods
	// void generateALAPTimeTable(); // unsure where to place this yet
	// void generateList_RSchedule(); // unsure where to plae this yet
	//void calculateWeights(Operations &op);
	void createListRSchedule(int latency);
	Nodes findLowestSlack(int);
	void createUnscheduledList();
	void createALAPSchedule(int latency);
	void checkALAP(int latency);
	void addNode(Nodes newNode, int ifStatementLevel, vector<string> conditionVariables);
	void addEdges(Edges newEdge);
	Nodes returnNode(int num);
	int returnNodeIndex(int num);
	int countResource();
	bool foundDependency(int);
};

#endif // !GRAPH_H