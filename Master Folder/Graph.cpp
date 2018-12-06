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

void Graph::setListRSchedule(int node)
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

vector<int> Graph::getListRSchedule()
{
	return this->listRSchedule;
}

//Methods
void Graph::createListRSchedule(int latency)
{
	//vector<int>::iterator it;
	vector<Nodes> tempList = nodes;
	int tempSlack = 999;
	Nodes tempNode;
	vector<Nodes> noDepenciesNodesList;
	int index = -1;

	// latency constrained, considers minimum resource
	for (int cycle = 1; cycle < (latency + 1); cycle++) {
		tempSlack = 999;
		// set slack time for current cycle for the remaining nodes
		for (unsigned int j = 0; j < tempList.size(); j++) {
			int alapTime = nodes.at(j).getALAP();
			int slack = nodes.at(j).calculateSlack(alapTime, cycle);
			nodes.at(j).setSlack(slack);
		}

		// add nodes without previous dependencies to unscheduled list
		for (unsigned int k = 0; k < tempList.size(); k++) {
			for (unsigned int l = 0; l < tempList.at(k).getEdges().size(); l++) {
				if (tempList.at(k).getEdges().at(l).getPrevNode() == NULL) {
					U.push_back(tempList.at(k));
					// remove added nodes from tempList
					tempList.erase(tempList.begin() + k);
				}
			}
		}

		// add unscheduled nodes to scheduled list
		if (S.empty() && !(U.empty())) {	// scheduled list is empty
			// find unscheduled nodes with lowest slack
			for (unsigned int i = 0; i < U.size(); i++) {
				// find node with lowest slack
				if (U.at(i).getSlack() < tempSlack) {
					tempSlack = U.at(i).getSlack();
					index = i;
				}
				S.push_back(U.at(index));
				U.erase(U.begin() + index);
				// when unscheduled list is not empty
				if (S.at(index).getNumCycles() == 2 && !(U.empty())) {
					for (unsigned j = 0; j < U.size(); j++) {
						if (U.at(j).getNumCycles() == 1) {
							// find node with lowest slack
							if (U.at(j).getSlack() < tempSlack) {
								tempSlack = U.at(j).getSlack();
								index = j;
							}
						}
						else {
							if (U.at(j).getSlack() < tempSlack) {
								tempSlack = U.at(j).getSlack();
								index = j;
							}
						}
					}
				}
				S.push_back(U.at(index));
				U.erase(U.begin() + index);
			}
		}
		// when scheduled list is not empty
		// needs to check constraints before adding unscheduled nodes:
		//	1.	Unscheduled node should not have dependency with current scheduled nodes
		//	2.	If unscheduled node is a multiplier operation, check that if there are any
		//		scheduled node whose operation is also a multiplier (2 cycles)
		//	3.	Current cycle means the previous cycle has ended, so there is room for a new add operation node
		else {	
			// check Constraint 1:
			for (unsigned int i = 0; i < S.size(); i++) {

			}
		}

		for (unsigned int i = 0; i < nodes.size(); i++) {				

				/* Needs to check for scheduled nodes dependencies, nodes without
				 depencies can be added to scheduled or unscheduled list */
				

				// update unscheduled list does not need to check for constraints
				/* empty unscheduled list */
				if (U.empty()) {	
					U.push_back(tempNode);
				}
				/* non-empty unscheduled list*/
				else {

				}
				if (i == nodes.size()) { // no more nodes to schedule, breaks out of loop
					cycle = latency + 1;
					break;
				}
			
		}
		
	}
}


void Graph::createUnscheduledList(){
	for (vector<Nodes>::size_type i = nodes.size(); i != 0; i++) {
		nodes.at(i).setALAP(-1); // Set default ALAP 
	}
}

/* ALAP Schedule:
 *	Set up scheduling based on path and reset latency when path end is reached.
 *	New Plan:
 *		- Use a searching algorithm (DFS) to find ordering of nodes, maybe by path.
 *		- Start at bottom of a path and iterate through each node in each path setting
 *		  the ALAP time as we go.
 *		- We continue this until all nodes have a ALAP time so need a while loop that 
 *		  keeps track of that.
 *		- We are planning on changing the edges from pointers to nodes to the node index
 *		  in it's nodes vector.
 */
void Graph::createALAPSchedule(int latency){  

	// Graph variables.
	Edges tempEdge;						// Temporary Edge.
	Nodes tempNode;						// Temporary node to save nodes if needed.
	int size = this->nodes.size();		// Size of the nodes vector


	int curALAP;						// Current ALAP value.

	// Indicies variables.
	vector <int> indicies;				// Holds all indicies of our current path.
	int index = 0;						// Index of current node in nodes vector.
	int endOfPath = 0;					// Last index in the path, will keep setting it until -1 to find the full path. 


	// Cycle variables.
	int lat = latency;					// Saves the current latency. (set to max latency at start)
	int numCycles = 0;					// Number of cycles current node uses.

	// End condition.
	int numSchedNode = 0;				// Total scheduled nodes (end condition for loop).

	while (numSchedNode < size) {
		/* Find the first node in path.
		 *	Iterate through the nodes vector to find the first uncheduled node in a path.
		 */
		for (vector<Nodes>::size_type i = 0; i < this->nodes.size(); i++) {
			curALAP = this->nodes.at(i).getALAP();
			if (curALAP < 0) {
				indicies.push_back(i);
				i = this->nodes.size();
			}
		}

		// Find the Path.
		endOfPath = indicies.back(); // Set endOfPath to the start of the path, then we iterate through til it is -1 (the actual end).
		while (endOfPath >= 0) {
			// Find the Edge
			tempNode = this->nodes.at(endOfPath);
			// Iterate through the node's edge vector to find the next node and schedule the path.
			for (vector<Edges>::size_type j = 0; j < tempNode.getEdges().size(); j++) {
				tempEdge = tempNode.getEdges().at(j); // Set a temp edge for ease of reading and programming.
				endOfPath = tempEdge.getNextNode();
				if (endOfPath >= 0) {
						// Found next part of our path.
						indicies.push_back(endOfPath); // add it to our path vector.
						j = tempNode.getEdges().size(); // set search index to exit parameter (size of the edge vector in our node). Basically, exit the loop.	
				}
				else {
					// End of path found.
					j = tempNode.getEdges().size(); // set search index to exit parameter (size of the edge vector in our node). Basically, exit the loop.				
				}
			}
		}

		// Now that we have path, we need to iterate through it backwards.
		for (vector<Edges>::size_type k = indicies.size() - 1; k < 100; k--) {
			// Find index.
			index = indicies.at(k);
			numCycles = this->nodes.at(index).getNumCycles();	// Find number of cycles.
			if (numCycles == 2) {
				lat = lat - 1;
			}
			else if (numCycles == 3) {
				lat = lat = 2;
			}
			if (this->nodes.at(index).getALAP() < 0) {
				// How we schedule.
				this->nodes.at(index).setALAP(lat);					// Set ALAP to be the current lat value.
				numSchedNode++;										// Increment the number of scheduled nodes.
			}
			lat = lat - 1;								// Set latency based on node.
		}

		// Set the temp latency back to our max for the next path.
		lat = latency;

		// Reset the indicies vector.
		indicies.clear();
	}

}

void Graph::Schedule() {

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
