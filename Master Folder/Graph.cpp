#include "Graph.h"

#include <iostream>
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

void Graph::setEdge(Edges newEdges)
{
	this->edges.push_back(newEdges);
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

vector<Edges> Graph::getEdges()
{
	return vector<Edges>();
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

// latency constrained, considers minimum resource
void Graph::createListRSchedule(int latency)
{
	//vector<int>::iterator it;
	vector<Nodes> tempList = nodes;
	int tempSlack;
	Nodes tempNode;
	int tempInt;
	vector<int> dependencyList;
	int index = -1;
	int nodeIndex = -1;
	bool flag = false;
	bool exit = false;
	int currASAP;
	int count = 0;
	for (int cycle = 1; cycle < (latency + 1); cycle++) {
		
		cout << endl << "Time Cycle: " << cycle << endl << endl;
		tempSlack = 999;
		// set slack time for current cycle for the remaining nodes
		cout << "Set slack time" << endl << endl;
		for (unsigned int j = 0; j < nodes.size(); j++) {
			if (nodes.at(j).getSlack() != 99) {
				int alapTime = nodes.at(j).getALAP();
				int slack = nodes.at(j).calculateSlack(alapTime, cycle);
				nodes.at(j).setSlack(slack);
			}
		}
		for (unsigned int i = 0; i < nodes.size(); i++) {
			cout << "Node: " << nodes.at(i).getNodeNum() << "\tSlack: " << nodes.at(i).getSlack() << endl;
		}
		cout << endl;

		// update cycle count
		cout << "Update cycle count" << endl;
		if (S.empty()) {
				
		}
		else {
			for (unsigned int i = 0; i < S.size(); i++) {
				tempInt = S.at(i);
				tempNode = returnNode(tempInt);
				nodeIndex = returnNodeIndex(tempInt);
				nodes.at(nodeIndex).setCycleCount(-1);
			}
		}

		for (unsigned int i = 0; i < nodes.size(); i++) {
			cout << "Node: " << nodes.at(i).getNodeNum() << "\tCycle count: " << nodes.at(i).getCycleCount() << endl;
		}
		cout << endl;

		// update scheduled list
		cout << "Update scheduled list" << endl;
		for (unsigned int i = 0; i < nodes.size(); i++) {
			if (nodes.at(i).getCycleCount() == 0) {
				for (unsigned int j = 0; j < S.size(); j++) {
					if (nodes.at(i).getNodeNum() == S.at(j)) {
						nodes.at(i).setSlack(99);
						S.erase(S.begin() + j);
					}
				}
			}
		}
		cout << "Updated Scheduled List: " << endl;
		for (int i : S) {
			cout << "Node: " << i << endl;
		}
		cout << endl;

		// adding nodes to list Unscheduled
		cout << "Add nodes to unscheduled list" << endl;
		// checks for nodes with no previous dependencies
		// In Time Cycle 1
		if (cycle == 1) {
			for (unsigned int i = 0; i < nodes.size(); i++) {
				if (nodes.at(i).getASAP() == 1) {
					tempInt = nodes.at(i).getNodeNum();
					tempNode = returnNode(tempInt);
					nodeIndex = returnNodeIndex(tempInt);
					if (nodes.at(nodeIndex).getChecked() == false) {
						U.push_back(tempInt);
						nodes.at(nodeIndex).setChecked(true);
					}
				}
			}
		}
		else { // not in Time Cycle 1
			for (unsigned int j = 0; j < nodes.size(); j++) {
				flag = false; // reset flag
				// checks if node has been checked
				if (nodes.at(j).getChecked() == false) {
					if (nodes.at(j).getASAP() == cycle) {
						tempInt = nodes.at(j).getNodeNum();
						nodeIndex = returnNodeIndex(tempInt);
						U.push_back(tempInt);
						nodes.at(nodeIndex).setChecked(true);
					}
				}
			}
		}
		cout << "Unscheduled List: " << endl;
		for (int i : U) {
			cout << "Node: " << i << endl;
		}
		cout << endl;

		// checks if list scheduled is empty
		cout << "Add unscheduled nodes to scheduled list" << endl;
		if (S.empty() && !(U.empty())) {
			for (unsigned int i = 0; i < U.size(); i++) {
				tempNode = returnNode(U.at(i));
				nodeIndex = returnNodeIndex(U.at(i));
				if (nodes.at(nodeIndex).getChecked() == true) {
					if (countResource() == 1) {
						if (nodes.at(nodeIndex).getNumCycles() == 2) {
							S.push_back(U.at(i));
							nodes.at(nodeIndex).setListR(cycle);
							nodes.at(nodeIndex).setCycleCount(3);
							nodes.at(nodeIndex).setSlack(99);
						}
					}
					else if (nodes.at(nodeIndex).getNumCycles() == 1) {
						if (countResource() != 1) {
							S.push_back(U.at(i));
							nodes.at(nodeIndex).setListR(cycle);
							nodes.at(nodeIndex).setCycleCount(2);
							nodes.at(nodeIndex).setSlack(99);
						}
					}
				}
			}
			// scheduled list is not empty
		}
		else if (!(S.empty()) && !(U.empty())) {
			if (countResource() < 3) {
				if (countResource() == 2) {
					//for (unsigned int i = 0; i < U.size(); i++) {
						tempNode = findLowestSlack(1);
						tempInt = tempNode.getNodeNum();
						nodeIndex = returnNodeIndex(tempInt);
						if (nodeIndex != -1 && foundDependency(tempInt) == false) {
							S.push_back(tempInt);
							nodes.at(nodeIndex).setListR(cycle);
							nodes.at(nodeIndex).setCycleCount(2);
							nodes.at(nodeIndex).setSlack(99);
						}
					//}
				}
				else {
					//for (unsigned int i = 0; i < U.size(); i++) {
						tempNode = findLowestSlack(2);
						tempInt = tempNode.getNodeNum();
						nodeIndex = returnNodeIndex(tempInt);
						if (nodeIndex != -1 && foundDependency(tempInt) == false) {
							S.push_back(tempInt);
							nodes.at(nodeIndex).setListR(cycle);
							nodes.at(nodeIndex).setCycleCount(3);
							nodes.at(nodeIndex).setSlack(99);
						}
					//}
				}
			}
		}
		cout << "Scheduled List: " << endl;
		for (int i : S) {
			cout << "Node: " << i << endl;
		}
		cout << endl;

		// update unscheduled list
		for (unsigned int i = 0; i < U.size(); i++) {
			for (unsigned int j = 0; j < S.size(); j++) {
				if (S.at(j) == U.at(i)) {
					U.erase(U.begin() + i);
				}
			}
		}
			
		cout << "Updated Unscheduled List: " << endl;
		for (int i : U) {
			cout << "Node: " << i << endl;
		}
		cout << endl;

		cout << "Cycle counts" << endl;
		for (unsigned int i = 0; i < nodes.size(); i++) {
			cout << "Node: " << nodes.at(i).getNodeNum() << "\tCycle count: " << nodes.at(i).getCycleCount() << endl;
		}
		cout << endl;
		
		// checks if all nodes has been visited and listR has been set
		int count = 0;
		for (Nodes n : nodes) {
			if (n.getListR() != -1) {
				count++;
			}
		}
		if (count == nodes.size()) {
			break;
		}

	} // end: for loop (cycle)

		cout << "List_R List: " << endl;
		for (unsigned int i = 0; i < nodes.size(); i++) {
		cout << "Node: " << nodes.at(i).getNodeNum() << "\tListR time = " << nodes.at(i).getListR() << endl;
	}
		cout << endl;
}//gitpush _ 12/6 8:11PM

bool Graph::foundDependency(int nodeNum) {
	bool flag = false;
	for (unsigned int i = 0; i < S.size(); i++) {
		for (unsigned int j = 0; j < edges.size(); j++) {
			if (edges.at(j).getPrevNode() == S.at(i)) {
				if (edges.at(j).getNextNode() == nodeNum) {
					flag = true;
					break;
				}
			}
		}
	}
	return flag;
}

int Graph::countResource() {
	int count = 0;
	
	for (unsigned int i = 0; i < S.size(); i++) {
		int tempInt = S.at(i);
		Nodes tempNode = returnNode(tempInt);
		int nodeIndex = returnNodeIndex(tempInt);
		count += nodes.at(nodeIndex).getNumCycles();
	}
	return count;
}

Nodes Graph::findLowestSlack(int numCycle) {
	int lowestSlack = 999;
	Nodes tempNode;
	for (unsigned int i = 0; i < nodes.size(); i++) {
		for (unsigned int j = 0; j < U.size(); j++) {
			if (nodes.at(i).getChecked() == true && nodes.at(i).getNumCycles() == numCycle && nodes.at(i).getNodeNum() == U.at(j)) {
				if (nodes.at(i).getSlack() < lowestSlack) {
					lowestSlack = nodes.at(i).getSlack();
					tempNode = nodes.at(i);
					break;
				}
			}
		}
	}
	return tempNode;
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

			if (numCycles > 2) {
				lat = lat - 2;
			}
			else if (numCycles > 1) {
				lat = lat - 1;
			}
			
			if (this->nodes.at(index).getALAP() < 0) {
				// How we schedule.
				this->nodes.at(index).setALAP(lat);					// Set ALAP to be the current lat value.
				numSchedNode++;										// Increment the number of scheduled nodes.
			}
			else if (this->nodes.at(index).getALAP() < lat) {
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

} // end: createALAPSchedule

void Graph::addNode(Nodes newNode) {
	nodes.push_back(newNode);
}

void Graph::addEdges(Edges newEdge)
{
	this->edges.push_back(newEdge);
}

Nodes Graph::returnNode(int num) 
{
	Nodes n;
	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		if (nodes.at(i).getNodeNum() == num) {
			n = nodes.at(i);
			break;
		}
	}
	return n;
}

int Graph::returnNodeIndex(int num) {
	int index = -1;
	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		if (nodes.at(i).getNodeNum() == num) {
			index = i;
			break;
		}
	}
	return index;
}

//void Graph::calculateWeights(Operations &op)
//{
//	int tempWeight = -1;
//
//	// Calculate weight by determining type of operation
//
//	this->weight = tempWeight;
//}
