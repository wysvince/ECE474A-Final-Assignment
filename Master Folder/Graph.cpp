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
	Nodes tempNode;						// Temporary node to save nodes if needed.
	Nodes* tempPt;						// Saves the pointer to the next node.
	vector <Nodes> tempVector;			// Temporarily store a path to set values later.

	int lat = latency;					// Saves the current latency. (set to max latency at start)
  
	int numSchedNode = 0;					// Total scheduled nodes (end condition for loop).
	int size = nodes.size();			// Size of the nodes vector
	int index = 0;						// Index of current node in nodes vector.
	int numCycles = 0;					// Number of cycles current node uses.
	int startPath = 0;
	bool foundNode = true;				// If we found the next node in the current path.
	int indEdge = 0;					// Index of the current edge.

	// test
	string teststr1;
	string teststr2;
	int testint;

	tempPt = &(nodes.back());
	startPath = nodes.size();

	while (numSchedNode != size) {
			// Find the path.
		  for (vector<Nodes>::size_type i = nodes.size() - 1; i != 0; i--) {
        if (nodes.at(i).getOperation().compare((*tempPt).getOperation()) == 0) {
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
