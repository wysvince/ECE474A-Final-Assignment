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
			for (int i = nodes.size() - 2; i >= 0; i--) {
				if (( nodes.at(i).getOutputVariable() == newNodeVars.at(j) && (nodes.at(i).getWithinElse() == newNode.getWithinElse()) ) ||	//Checks if using same var, BUT either both within or both not within an else statement
					((nodes.at(i).getIfStatementLevel() < ifStatementLevel || nodes.at(i).getOutputVariable() == recentConditionVar) && !newNode.getWithinElse() && !foundConditionalOp)) {	//Check if difference in "ifLevel" and condition dependency				
					Edges newEdge;
					newEdge.setNextNode(nodes.at(nodes.size() - 1).getNodeNum());
					newEdge.setPrevNode(nodes.at(i).getNodeNum());
					//calculate asapTime
					if (nodes.at(i).getAsapTime() >= asapTime) {
						asapTime = nodes.at(i).getAsapTime() + 1;	//AsapTime is 1 higher than preceding Node
					}
					if (nodes.at(i).getIfStatementLevel() < ifStatementLevel && !newNode.getWithinElse()) {		//Sets edge conditional if needed
						string edgeCondition;
						if (nodes.at(i).hasConditionalEdge()) {	//if edge condition already exists, may need else if
							for (Edges curEdge : nodes.at(i).getEdges()) {
								if (!curEdge.getConditionalOperation().empty()) {
									if (nodes.at(curEdge.getNextNode()).getAsapTime() == asapTime) {	//Find if edge has same conditionalOperation, there must be if (not an else if)
										edgeCondition = "if {";
										break;
									}
									else {
										edgeCondition = "else if {";
										break;
									}
								}
							}
						}
						else {
							edgeCondition = "if (";
						}

						int x = 0;
						for (int y = ifStatementLevel - 1; y >= (ifStatementLevel - (ifStatementLevel - nodes.at(i).getIfStatementLevel())); y--) {
							if (x > 0) {
								edgeCondition += " && " + conditionVariables.at(y);
							}
							else {
								edgeCondition += conditionVariables.at(y);
							}
							x++;
						}
						edgeCondition += ") {";
						newEdge.setCondtionalOperation(edgeCondition);
						foundConditionalOp = true;
					}
					edges.push_back(newEdge);
					nodes.at(i).addEdge(newEdge); //adds edge to node pointing to newNode				//FIXME AVOID DUPLICATE EDGES (override edge ==)
					//break;
				}
			}
		}
		//Check if else is needed
		Nodes* tempNodePtr = NULL;
		//if (nodes.at(nodes.size() - 2).getIfStatementLevel() > ifStatementLevel/* && !newNode.getWithinElse()*/) {
			for (int i = nodes.size() - 2; i >= 0; i--) {
				if (nodes.at(i).getIfStatementLevel() > ifStatementLevel) {
					tempNodePtr = &nodes.at(i);
				}
				if (nodes.at(i).getIfStatementLevel() == ifStatementLevel && nodes.at(i).getAsapTime() < asapTime) {
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
			}
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
