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

using namespace std;

class Graph {

private:
	vector<Nodes> nodes;
	//vector<Edges> edges;
	int weight;
	vector<int> alapSchedule;

	// List R Scheduling:
	vector<int> listRSchedule;
	vector<Nodes> U; // candidate operations (Node's index)
	vector<Nodes> S; // scheduled nodes

public:
	// constructors
	Graph();
	//Graph(Nodes newNodes, Edges newEdges, int newWeight);
	Graph(Nodes newNodes, int newWeight);

	//setters
	void setNodes(Nodes newNodes);
	void setWeight(int newWeight);
	void setAlapSchedule(int num);
	void setListRSchedule(int node);

	//getters
	vector<Nodes> getNodes();
	int getWeight();
	vector<int> getAlapSchedule();
	vector<int> getListRSchedule();

	//methods
	// void generateALAPTimeTable(); // unsure where to place this yet
	// void generateList_RSchedule(); // unsure where to plae this yet
	//void calculateWeights(Operations &op);
	void createListRSchedule(int latency);
	void createUnscheduledList();
	void createALAPSchedule(int latency);
	void addNode(Nodes newNode);
	void Schedule();
};

#endif // !GRAPH_H