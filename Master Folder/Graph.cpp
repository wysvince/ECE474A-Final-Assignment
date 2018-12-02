#include "Graph.h"

using namespace std;

// constructors
Graph::Graph() {} // default constructor

Graph::Graph(Nodes newNodes, Edges newEdges, int newWeight) {
	this->nodes.push_back(newNodes);
	this->edges.push_back(newEdges);
	this->weight = newWeight;
}

// setters
void Graph::setNodes(Nodes newNodes) {
	this->nodes.push_back(newNodes);
}

void Graph::setEdges(Edges newEdges) {
	this->edges.push_back(newEdges);
}

void Graph::setWeight(int newWeight) {
	this->weight = newWeight;
}

void Graph::setUnscheduledList(int num)
{
	this->unscheduledList.push_back(num);
}

void Graph::setAlapSchedule(int num)
{
	this->alapSchedule.push_back(num);
}

void Graph::setListRSchedule(int num)
{
	this->listRSchedule.push_back(num);
}

// getters
vector<Nodes> Graph::getNodes() {
	return this->nodes;
}

vector<Edges> Graph::getEdges() {
	return this->edges;
}

int Graph::getWeight() {
	return this->weight;
}

vector<int> Graph::getUnscheduleList()
{
	return this->unscheduledList;
}

vector<int> Graph::getAlapSchedule()
{
	return this->alapSchedule;
}

vector<int> Graph::getListRSchedule()
{
	return this->listRSchedule;
}

//Methods

void Graph::createUnscheduledList(){
	for (vector<Nodes>::size_type i = nodes.size(); i != 0; i++) {
		nodes.at(i).setALAP(-1); // Set default ALAP 
	}
}

/* ALAP Schedule:
 *	Set up scheduling based on path and reset latency when path end is reached.
 */
void Graph::createALAPSchedule(int latency){
	Nodes tempNode;						// Temporary node to save nodes if needed.
	Nodes* tempPt;						// Saves the pointer to the next node.

	int lat = latency;					// Saves the current latency. (set to max latency at start)
	int numSchedNode;					// Total scheduled nodes (end condition for loop).
	int size = nodes.size();			// Size of the nodes vector
	int index = 0;						// Index of current node in nodes vector.
	int numCycles = 0;					// Number of cycles current node uses.
	int startPath = 0;
	bool foundNode = true;				// If we found the next node in the current path.
	int indEdge = 0;					// Index of the current edge.

	tempPt = &nodes.back();
	startPath = nodes.size();

	while (numSchedNode != size) {
		// Find the next Node.
		for (vector<Nodes>::size_type i = nodes.size(); i != 0; i++) {
			if (&nodes.at(i) == tempPt) {
				if (foundNode == false) {
					startPath = i;
				}
				index = i;
			}
		}

		// How we schedule.
		numCycles = nodes.at(index).getNumCycles(); // Find number of cycles.
		lat = lat - numCycles;						// Set latency based on node.
		nodes.at(index).setALAP(lat);
		numSchedNode++;

		// Couldn't find a new node.
		if (indEdge == nodes.at(index).getEdges().size()) {
			foundNode = false;
			indEdge = 0;
		}
		else {
			// Itterate through edges to find next node.
			tempPt = nodes.at(index).getEdges().at(indEdge).getPrevNode();
			indEdge++;
		}
		
		if (foundNode == false) {
			lat = latency;
			//while () {

			//}
		}
	}
}

void Graph::createListRSchedule() {

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
