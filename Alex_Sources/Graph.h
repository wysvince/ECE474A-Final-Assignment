#pragma once
#ifndef GRAPH_H
#define GRAPH_H
  
class Edges; 
class Nodes;

#include "Edges.h"
#include "Nodes.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Graph {

private:
	vector<Nodes> nodes;
	vector<Edges> edges;
	int weight;

public:
	// constructors
	Graph();
	Graph(Nodes newNodes, Edges newEdges, int newWeight);

	//setters
	void setNodes(Nodes newNodes);
	void setEdges(Edges newEdges);
	void setWeight(int newWeight);

	//getters
	vector<Nodes> getNodes();
	vector<Edges> getEdges();
	int getWeight();
	unsigned int getNumNodes();

	//methods
	void addNode(Nodes newNode, int ifStatementLevel, vector<string> conditionVariables);
	

	// void generateALAPTimeTable(); // unsure where to place this yet
	// void generateList_RSchedule(); // unsure where to plae this yet
	//void calculateWeights(Operations &op);
	//void setupNodesEdges(ReadInputFile &rif);
};

#endif // !GRAPH_H