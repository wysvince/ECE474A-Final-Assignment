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
	int numMultipliers = 1;
	int usedMultipliers = 0;
	int numAdders = 1;
	int usedAdders = 0;
	int numLogicals = 1;
	int usedLogicals = 0;

	int currentTime = 0;
	int nodesLeftToSchedule = this->nodes.size();
	vector<Nodes*> candidateNodes;

	while (nodesLeftToSchedule > 0) {
		candidateNodes.clear();
		usedMultipliers = 0;
		usedAdders = 0;
		usedLogicals = 0;
		for (int i = 0; i < nodes.size(); ++i) {		//Determine candidate Nodes
			if (nodes.at(i).getASAP() <= currentTime && !nodes.at(i).getChecked()) {	//detected by ASAP time and !checked-(means not already scheduled in this case)
				candidateNodes.push_back(&nodes.at(i));
				nodes.at(i).setSlack(currentTime - nodes.at(i).getALAP()); //set slack at current time
			}
		}
		//REMOVE DEPENDENT NODES
		for (int i = 0; i < candidateNodes.size(); ++i) {
			for (Edges edges : candidateNodes.at(i)->getEdges()) {
				for (int j = 0; j < candidateNodes.size(); ++j) {
					if (edges.getNextNode() == candidateNodes.at(j)->getNodeNum()) {
						candidateNodes.erase(candidateNodes.begin() + j);
						if (j < i) {
							i--; //make sure i follows the shift of the vector
						}
						--j;
					}
				}
			}
		}

		for (int i = 0; i < candidateNodes.size(); ++i) {	//Schedules all nodes with 0 slack first
			if (candidateNodes.at(i)->getSlack() == 0) {
				--nodesLeftToSchedule;
				candidateNodes.at(i)->setListR(currentTime);
				candidateNodes.at(i)->setChecked(true);
				if (candidateNodes.at(i)->getResourceType() == "Logic") {
					++usedLogicals;
					if (usedLogicals > numLogicals) {
						++numLogicals;
					}
				}
				else if (candidateNodes.at(i)->getResourceType() == "Adder") {
					++usedAdders;
					if (usedAdders > numAdders) {
						++numAdders;
					}
				}
				else if (candidateNodes.at(i)->getResourceType() == "Mult") {
					++usedMultipliers;
					if (usedMultipliers > numMultipliers) {
						++numMultipliers;
					}
				}
			}
		}
		//Check if we have left over resources
		while (usedLogicals < numLogicals) {
			int lowestSlackTime = 10000;
			int lowestSlackIndex = -1;
			for (int i = 0; i < candidateNodes.size(); ++i) {
				if (!candidateNodes.at(i)->getChecked() && candidateNodes.at(i)->getResourceType() == "Logic") {	//node has not been scheduled yet
					if (candidateNodes.at(i)->getSlack() < lowestSlackTime) {
						lowestSlackTime = candidateNodes.at(i)->getSlack();
						lowestSlackIndex = i;
					}
				}
			}
			if (lowestSlackIndex == -1) {	//No nodes to schedule
				break;
			}
			else {
				candidateNodes.at(lowestSlackIndex)->setChecked(true);
				candidateNodes.at(lowestSlackIndex)->setListR(currentTime);
				--nodesLeftToSchedule;
				++usedLogicals;
			}
		}
		while (usedAdders < numAdders) {
			int lowestSlackTime = 10000;
			int lowestSlackIndex = -1;
			for (int i = 0; i < candidateNodes.size(); ++i) {
				if (!candidateNodes.at(i)->getChecked() && candidateNodes.at(i)->getResourceType() == "Adder") {	//node has not been scheduled yet
					if (candidateNodes.at(i)->getSlack() < lowestSlackTime) {
						lowestSlackTime = candidateNodes.at(i)->getSlack();
						lowestSlackIndex = i;
					}
				}
			}
			if (lowestSlackIndex == -1) {	//No nodes to schedule
				break;
			}
			else {
				candidateNodes.at(lowestSlackIndex)->setChecked(true);
				candidateNodes.at(lowestSlackIndex)->setListR(currentTime);
				--nodesLeftToSchedule;
				++usedAdders;
			}
		}
		while (usedMultipliers < numMultipliers) {
			int lowestSlackTime = 10000;
			int lowestSlackIndex = -1;
			for (int i = 0; i < candidateNodes.size(); ++i) {
				if (!candidateNodes.at(i)->getChecked() && candidateNodes.at(i)->getResourceType() == "Mult") {	//node has not been scheduled yet
					if (candidateNodes.at(i)->getSlack() < lowestSlackTime) {
						lowestSlackTime = candidateNodes.at(i)->getSlack();
						lowestSlackIndex = i;
					}
				}
			}
			if (lowestSlackIndex == -1) {	//No nodes to schedule
				break;
			}
			else {
				candidateNodes.at(lowestSlackIndex)->setChecked(true);
				candidateNodes.at(lowestSlackIndex)->setListR(currentTime);
				--nodesLeftToSchedule;
				++usedMultipliers;
			}
		}

		++currentTime;
	}
	
}//END LIST_R

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
							edges.push_back(newEdge);
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
