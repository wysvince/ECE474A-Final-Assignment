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

int Graph::getNumNodes() {
	return nodes.size();
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
	/*  Not actually working commenting out for now.
	int numALU = 1;						// Number of ALUs
	int numMUL = 1;						// Number of Multipliers
	int numLog = 1;						// Number of logic units

	int schALU = 0;
	int schMUL = 0;
	int schLog = 0;

	// Graph variables.
	Edges tempEdge;						// Temporary Edge.
	Nodes tempNode;						// Temporary node to save nodes if needed.
	int size = this->nodes.size();		// Size of the nodes vector

	int curALAP;						// Current ALAP value.
	int curASAP;						// Current ASAP value.
	int tempSlack;

	bool isALU = false;					// If it's a Arithmetic unit
	bool isMUL = false;					// If it's a Multiplier
	bool isLog = false;					// If it's a logic unit

	// Indicies variables.
	vector <int> U;						// Holds all indicies to be checked.
	vector <int> L;						// Holds all slacks to be checked.
	vector <int> S;						// Holds all nodes to be scheduled.
	int index = 0;						// Index of current node in nodes vector.
	int endOfPath = 0;					// Last index in the path, will keep setting it until -1 to find the full path. 

	// Number of iterated edges:
	int numItEdge = 0;					// Increments when we find an edge to make sure we hit every edge in the graph, otherwise we have errors with our timing in specific situations.
	int tempInd = 0;
	int curTime = 0;

	// Cycle variables.
	int lat = latency;					// Saves the current latency. (set to max latency at start)
	int numCycles = 0;					// Number of cycles current node uses.

	// End condition.
	int numSchedNode = 0;				// Total scheduled nodes (end condition for loop).

	while (numSchedNode < size) {
		// Find members of U.
		for (vector<Nodes>::size_type u = 0; u < this->nodes.size(); u++) {
			curASAP = nodes.at(u).getASAP();
			if (curASAP == 0) {
				U.push_back(u);
			}
			else if(curASAP == curTime){
				U.push_back(u);
			}
		}

		// Find slack of U memebers.
		for (vector<int>::size_type l = 0; l < U.size(); l++) {
			curALAP = nodes.at(U.at(l)).getALAP();
			L.push_back(curALAP - curTime);
		}

		tempSlack = 99;

		// Find scheduled nodes.
		for (vector<int>::size_type s = 0; s < U.size(); s++) {
			tempNode = nodes.at(U.at(s));

			// Get the type of operation.
			if (tempNode.getOperation().find("+-")) {
				bool isALU = true;
				bool isMUL = false;
				bool isLog = false;
			}
			else if (tempNode.getOperation().find("*")) {
				bool isALU = false;
				bool isMUL = true;
				bool isLog = false;
			}
			else {
				bool isALU = false;
				bool isMUL = false;
				bool isLog = true;
			}

			if (L.at(s) == 0) {
				S.push_back(U.at(s));
				if (isALU) {
					numALU++;
				}
				else if (isMUL) {
					numMUL++;
				}
				else if (isLog) {
					numLog++;
				}
			}
			else if (isALU && schALU < numALU) {
				S.push_back(U.at(s));
				U.erase(U.begin() + s);
				L.erase(U.begin() + s);
				schALU++;
			}
			else if (isMUL && schMUL < numMUL) {
				S.push_back(U.at(s));
				U.erase(U.begin() + s);
				L.erase(U.begin() + s);
				schMUL++;
			}
			else if (isLog && schLog < numLog) {
				S.push_back(U.at(s));
				U.erase(U.begin() + s);
				L.erase(U.begin() + s);
				schLog++;
			}
		}

		// Now Schedule 
		for (vector<int>::size_type ind = 0; ind < S.size(); ind++) {
			nodes.at(S.at(ind)).setListR(curTime);
			numSchedNode++;
		}

		S.clear();
		curTime++;
	}
	*/

// Trying Something:
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
				if (nodes.at(i).getASAP() == 0) {
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
	for (vector<Nodes>::size_type i = 0; i < nodes.size(); i++) {
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
	
	// Number of iterated edges:
	int numItEdge = 0;					// Increments when we find an edge to make sure we hit every edge in the graph, otherwise we have errors with our timing in specific situations.
	int tempInd = 0;

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
			tempEdge.init();
			if (tempNode.getEdges().empty() == true) {
				endOfPath = -1;
			}
			else {
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

			// Set it to 0 to make sure it triggers for each node.
			numItEdge = 0;
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
			else if (this->nodes.at(index).getALAP() > lat) {		// Check if the current ALAP value is larger than current lat value (found new dependency) and change it.
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

	// Check the ALAP before we exit
	this->checkALAP(latency);

} //end createALAPSchedule()

/* Goes through ALAP once to make sure no parent nodes are taking the same time slot as one of thier child nodes.
 * Kind of like putting a bandaid on it but it would take to long to fix the createALAPSchedule( ... ) function.
 */
void Graph::checkALAP(int latency) {

	// Graph variables.
	Edges tempEdge;						// Temporary Edge.
	Nodes tempNode;						// Temporary node to save nodes if needed.
	int size = this->nodes.size();		// Size of the nodes vector

	int curALAP;						// Current ALAP value.

	// Indicies variables.
	vector <int> indicies;				// Holds all indicies of our current path.
	int index = 0;						// Index of current node in nodes vector.

	// Number of iterated edges:
	int numItEdge = 0;					// Increments when we find an edge to make sure we hit every edge in the graph, otherwise we have errors with our timing in specific situations.
	int tempInd = 0;

	// Cycle variables.
	int nextNode;						// Saves the current latency. (set to max latency at start)
	int numCycles = 0;					// Number of cycles current node uses.

	// End condition.
	int numSchedNode = 0;				// Total scheduled nodes (end condition for loop).

	bool change = true;					// Checks if there was a change, if so loop through again. If we can loop through all nodes without change then there are no conflicts.
	int currNodeALAP = 0;				// Saves the current node's ALAP value.
	int nextNodeALAP = 0;				// Saves the next node's ALAP.

	while (change == true) {
		/* Find a node, look at it's edges and the nodes at the end. Compare the ALAP of each parent node to each child node. If there is a conflict push the parent node up.
		 * Iterate through the nodes vector to find the first uncheduled node in a path.
		 */
		for (vector<Nodes>::size_type i = 0; i < this->nodes.size(); i++) {
			tempNode = this->nodes.at(i);

			// Iterate through the node's edge vector to find the next node and schedule the path.
			for (vector<Edges>::size_type j = 0; j < tempNode.getEdges().size(); j++) {
				// Establish node values we're using
				tempEdge = tempNode.getEdges().at(j); // Set a temp edge for ease of reading and programming.
				nextNode = tempEdge.getNextNode();

				// Save ALAP values
				if (nextNode >= 0) {										// Check if the index is >= 0 so we dont try and pull a negative index.
					nextNodeALAP = nodes.at(nextNode).getALAP();
				}
				else {													// If the index < 0 then we need to prevent the code below from exicuting.
					nextNodeALAP = -1;
				}
				curALAP = this->nodes.at(i).getALAP();

				if ((nextNodeALAP < curALAP) && (nextNodeALAP > 0)) {
					nodes.at(i).setALAP(curALAP - (curALAP + 1 - nextNodeALAP));
					change = true;

					// Exit for-loops to loop again.
					i = this->nodes.size() + 1;
					j = tempNode.getEdges().size() + 1;
				}
				else if (nextNodeALAP == curALAP) {
					nodes.at(i).setALAP(curALAP - 1);
					change = true;

					// Exit for-loops to loop again.
					i = this->nodes.size() + 1;
					j = tempNode.getEdges().size() + 1;
				}
				else {
					change = false;
				}
			}

			// Initialize variables.
			tempNode.init();
			tempEdge.init();
		}
	}
	
} //end checkALAP

void Graph::addNode(Nodes newNode, int ifStatementLevel, vector<string> conditionVariables) {
	vector<string> newNodeVars;
	string recentConditionVar;
	bool insideOuterElse = false;
	bool exitedElse = false;
	int elseLevel = 0;
	int asapTime = 0;

	if (!conditionVariables.empty()) {
		recentConditionVar = conditionVariables.back();
	}
	else {
		recentConditionVar = "";
	}

	newNodeVars = newNode.getVariablesInvolved();
	if (newNodeVars.size() == 0) {
		cout << "Error (Graph.addNode): newNode has 0 variables" << endl;
		return;
	}
	newNode.setIfStatementLevel(ifStatementLevel);
	nodes.push_back(newNode);
	cout << newNode.getOperation() << endl;	//Prints all operations for Debugging
	if (nodes.size() > 1) {
		for (int j = 0; j < newNodeVars.size(); ++j) {
			insideOuterElse = false;
			exitedElse = false;
			for (int i = nodes.size() - 2; i >= 0; i--) {
				for (int conditionCounter = conditionVariables.size(); conditionCounter >= 0; --conditionCounter) {	//Check dependencies for if statement's condition variables and update inner nodes' asap time
					string curCondition = "";
					if (conditionVariables.size() > 0 && conditionCounter > 0) {
						curCondition = conditionVariables.at(conditionCounter - 1);
					}

					if (nodes.at(i).getIfStatementLevel() < ifStatementLevel && nodes.at(i).getWithinElse() && !insideOuterElse) {	//reverse iterated to an outer else statement
						insideOuterElse = true;
						elseLevel = nodes.at(i).getIfStatementLevel();
					}
					if (insideOuterElse) {
						if (!nodes.at(i).getWithinElse()) { //iterated backwards until no longer within else statement
							exitedElse = true;
						}
					}
					if (!(exitedElse && nodes.at(i).getIfStatementLevel() > elseLevel)) { //Make sure we haven't gone back into an "if" thats in parallel with the "else" we're within
						if (((nodes.at(i).getOutputVariable() == newNodeVars.at(j) || (nodes.at(i).getOutputVariable() == curCondition)) ||	//Checks if using same var, BUT either both within or both not within an else statement
							((nodes.at(i).getOutputVariable() == recentConditionVar))) && //Check if difference in "if" condition dependency	
							!(nodes.at(i).getIfStatementLevel() > ifStatementLevel && newNode.getWithinElse())) {
							Edges newEdge;
							newEdge.setNextNode(nodes.at(nodes.size() - 1).getNodeNum());
							newEdge.setPrevNode(nodes.at(i).getNodeNum());
							curCondition = -1; //breaks from inner most loop (no need to iterate again on this node)
							//calculate asapTime
							if ((nodes.at(i).getASAP() + nodes.at(i).getNumCycles()) >= asapTime) {
								asapTime = nodes.at(i).getASAP() + nodes.at(i).getNumCycles();	//AsapTime is higher than preceding Node by the number of cycles the preceding node takes
							}
							if ((nodes.at(i).getIfStatementLevel() < ifStatementLevel) || (nodes.at(i).getIfStatementLevel() == ifStatementLevel && newNode.getWithinElse() && !nodes.at(i).getWithinElse()) ) {		//Sets edge conditional if needed
								string edgeCondition = "if (";
								/*if (nodes.at(i).hasConditionalEdge()) {	//if edge condition already exists, may need else if
									for (Edges curEdge : nodes.at(i).getEdges()) {
										if (!curEdge.getConditionalOperation().empty()) {
											if (nodes.at(curEdge.getNextNode()).getAsapTime() == asapTime) {	//Find if edge has same conditionalOperation, there must be if (not an else if)
												edgeCondition = "if (";
												break;
											}
											else {
												edgeCondition = "else if (";
												break;
											}
										}
									}
								}
								else {
									edgeCondition = "if (";
								}*/

								int x = 0;
								int limit = conditionVariables.size() - (ifStatementLevel - nodes.at(i).getIfStatementLevel());
								if (newNode.getWithinElse()) {
									limit--;
								}

								for (int y = conditionVariables.size() - 1; y >= limit; --y) {
									if (x > 0) {
										edgeCondition += " && " + conditionVariables.at(y);
									}
									else {
										edgeCondition += conditionVariables.at(y);
									}
									if (conditionVariables.at(y).find("!") != string::npos && y != (conditionVariables.size() - 1)) {	//else conditions don't increment ifstatement level, therefore we need to decrement our limit to account for this
										limit--;
										if (limit < 0) {
											break;
										}
									}
									x++;
								}
								edgeCondition += ") {";
								newEdge.setCondtionalOperation(edgeCondition);
							}
							nodes.at(i).addEdge(newEdge); //adds edge to node pointing to newNode				//FIXME AVOID DUPLICATE EDGES (override edge ==)
							//break;
						}
					}
				}
			}
		}
		//Check if else is needed 
		//if (nodes.at(nodes.size() - 2).getIfStatementLevel() > ifStatementLevel/* && !newNode.getWithinElse()*/) {
		/*	for (int i = nodes.size() - 2; i >= 0; i--) {
				if (nodes.at(i).getIfStatementLevel() == ifStatementLevel && newNode.getWithinElse()) {
					if (nodes.at(i).hasConditionalEdge()) {
						if (nodes.at(i).hasElseEdge()) {
							break;
						}
						Edges newEdge;
						newEdge.setNextNode(nodes.at(nodes.size() - 1).getNodeNum());
						newEdge.setPrevNode(nodes.at(i).getNodeNum());
						newEdge.setCondtionalOperation("else {");
						edges.push_back(newEdge);
						nodes.at(i).addEdge(newEdge);
						break;
					}
				}
				if (nodes.at(i).getIfStatementLevel() < ifStatementLevel) {	//exited current if level without needing an else
					break;
				}
			}	*/
		//}
	}//End of adding node/edges

	if (conditionVariables.size() > 0 && asapTime == 0) {	//If nodes have conditions but an asap of 0, then add edge to graph itself
		Edges newEdge;
		newEdge.setNextNode(newNode.getNodeNum());
		newEdge.setPrevNode(-1);
		
		string conditionOp = "if (";
		bool multipleConditions = false;
		for (string cond : conditionVariables) {
			if (multipleConditions) {
				conditionOp += " && " + cond;
			}
			else {
				conditionOp += cond;
				multipleConditions = true;
			}
		}
		conditionOp += ") {";
		newEdge.setCondtionalOperation(conditionOp);
		edges.push_back(newEdge);
	}

	nodes.at(nodes.size() - 1).setASAP(asapTime);
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
