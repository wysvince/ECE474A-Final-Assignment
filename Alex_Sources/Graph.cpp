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

unsigned int Graph::getNumNodes() {
	return nodes.size();
}

//Methods

void Graph::addNode(Nodes newNode, int ifStatementLevel, vector<string> conditionVariables) {
	vector<string> newNodeVars;
	string recentConditionVar;
	bool foundConditionalOp = false;
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
			foundConditionalOp = false;
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
							((nodes.at(i).getOutputVariable() == recentConditionVar) && !foundConditionalOp)) && //Check if difference in "if" condition dependency	
							!(nodes.at(i).getIfStatementLevel() > ifStatementLevel && newNode.getWithinElse())) {
							Edges newEdge;
							newEdge.setNextNode(nodes.at(nodes.size() - 1).getNodeNum());
							newEdge.setPrevNode(nodes.at(i).getNodeNum());
							curCondition = -1; //breaks from inner most loop (no need to iterate again on this node)
							//calculate asapTime
							if ((nodes.at(i).getAsapTime() + nodes.at(i).getNumCycles()) >= asapTime) {
								asapTime = nodes.at(i).getAsapTime() + nodes.at(i).getNumCycles();	//AsapTime is higher than preceding Node by the number of cycles the preceding node takes
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
									if (conditionVariables.at(y).find("!") != string::npos) {	//else conditions don't increment ifstatement level, therefore we need to decrement our limit to account for this
										limit--;
										if (limit < 0) {
											break;
										}
									}
									x++;
								}
								edgeCondition += ") {";
								newEdge.setCondtionalOperation(edgeCondition);
								//foundConditionalOp = true;
							}
							if (nodes.at(i).getWithinElse()) {
								//foundConditionalOp = true;
								//stayWithinElse = true;
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
	}
	nodes.at(nodes.size() - 1).setAsapTime(asapTime);
	
}

//void Graph::calculateWeights(Operations &op)
//{
//	int tempWeight = -1;
//
//	// Calculate weight by determining type of operation
//
//	this->weight = tempWeight;
//}

//void Graph::setupNodesEdges(ReadInputFile &rif)
//{	
//	int tempStateNum = 0;
//	int tempNumCycles = 0;
//	string tempOperation = "\0";
//	for (Operations op : rif.operationList) {
//		this->nodes.
//	}
//}
