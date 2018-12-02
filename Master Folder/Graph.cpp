#include "Graph.h"

using namespace std;

// constructors
Graph::Graph() {} // default constructor

//Graph::Graph(Nodes newNodes, Edges newEdges, int newWeight) {
Graph::Graph(Nodes newNodes, int newWeight) {
	this->nodes.push_back(newNodes);
	//this->edges.push_back(newEdges);
	this->weight = newWeight;
}

// setters
void Graph::setNodes(Nodes newNodes) {
	this->nodes.push_back(newNodes);
}

//void Graph::setEdges(Edges newEdges) {
//	this->edges.push_back(newEdges);
//}

void Graph::setWeight(int newWeight) {
	this->weight = newWeight;
}

void Graph::setAlapSchedule(int num)
{
	this->alapSchedule.push_back(num);
}

void Graph::setListRSchedule(Nodes node)
{
	this->listRSchedule.push_back(node);
}

// getters
vector<Nodes> Graph::getNodes() {
	return this->nodes;
}

//vector<Edges> Graph::getEdges() {
//	return this->edges;
//}

int Graph::getWeight() {
	return this->weight;
}


vector<int> Graph::getAlapSchedule()
{
	return this->alapSchedule;
}

vector<Nodes> Graph::getListRSchedule()
{
	return this->listRSchedule;
}

//Methods

void Graph::createALAPSchedule(int latency)
{
}

void Graph::createListRSchedule(int latency)
{
	vector<int>::iterator it;
	vector<Nodes> tempList = nodes;

	// latency constrained, considers minimum resource
	for (int cycle = 1; cycle < (latency + 1); cycle++) {
		for (unsigned int n = 0; n < nodes.size(); n++) {
			
		}
	}
}

// update unscheduled nodes
// Criteria: unscheduled nodes needs to have dependency resolved
void Graph::updateU(Nodes node) {
	for (unsigned int i = 0; i < U.size(); i++) {
		Nodes u = U.at(i);
		// update all unscheduled Nodes
		if (checkConstraint(u) == false) {
			///////////////////////////////PICK UP FROM HERE//////////
		}
	}
}

// update scheduled nodes
void Graph::updateS() {
	for (unsigned int i = 0; i < S.size(); i++) {
		Nodes s = S.at(i);
		// update all scheduled Nodes cycle count
		if (s.getCycleCount() != 0) {
			s.setCycleCount(-1);
		}
		else {
			// Move completed node to listR Schedule
			S.erase(S.begin() + i);
			this->listRSchedule.push_back(s);
		}
	}
}

// Criteria: scheduled nodes needs to check the Node's cycle 
bool Graph::checkConstraint(Nodes node) {
	bool flag = false;
	// node is a mult operation type
	// check if schedule list contains existing mult operation
	if (node.getNumCycles() == 2) {
		for (Nodes s : S) {
			if (s.getNumCycles() == 2 && s.getCycleCount() != 0) {
				flag = true;
			}
		}
	}
	else {
		// check for dependencies in scheduled nodes
		for (Nodes s : S) {
			for (Edges e : s.getEdges()) {
				if (e.getNextNode() == &node) {
					flag = true; // found dependency
				}
			}
		}
	}
	return flag;
}




void Graph::addNode(Nodes newNode) {
	nodes.push_back(newNode);
}

//void Graph::calculateWeights(Operations &op)
//{
//	int tempWeight = -1;
//
//	// Calculate weight by determining type of operation
//
//	this->weight = tempWeight;
//}
