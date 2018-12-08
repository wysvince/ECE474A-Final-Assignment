#include "Nodes.h"
 
using namespace std; 
#define underline "\033[4m"
 
// constructors
Nodes::Nodes() {} // default constructor

Nodes::Nodes(int newStateNum, Edges newEdges, int newNumCycles, string op) {
	this->nodeNum = newStateNum;
	this->edges.push_back(newEdges);
	this->numCycles = newNumCycles;
	this->operation = op;
	withinElse = false;
}

// setters
void Nodes::setNodeNum(int newStateNum) {
	this->nodeNum = newStateNum;
}	

void Nodes::setAsapTime(int newTime) {
	this->asapTime = newTime;
}

void Nodes::setAlapTime(int newTime) {
	this->alapTime = newTime;
}

void Nodes::setIfStatementLevel(int level) {
	this->ifStatementLevel = level;
}

void Nodes::setEdges(Edges newEdges) {
	this->edges.push_back(newEdges);
}

void Nodes::setNumCycles(int newNumCycles) {
	this->numCycles = newNumCycles;
}

void Nodes::setOperation(string op) {
	this->operation = op;
}

void Nodes::setVariablesInvolved(vector<string> vbs) {
	variablesInvolved = vbs;
}

void Nodes::setWithinElse(bool b) {
	withinElse = b;
}

// getters
int Nodes::getNodeNum() {
	return this->nodeNum;
}

int Nodes::getAsapTime() {
	return asapTime;
}

int Nodes::getAlapTime() {
	return alapTime;
}

int Nodes::getIfStatementLevel() {
	return ifStatementLevel;
}

vector<Edges> Nodes::getEdges() {
	return this->edges;
}

int Nodes::getNumCycles() {
	return this->numCycles;
}

string Nodes::getOperation() {
	return this->operation;
}

vector<string> Nodes::getVariablesInvolved() {
	return variablesInvolved;
}

string Nodes::getOutputVariable() {
	return variablesInvolved.at(0);
}

bool Nodes::getWithinElse() {
	return withinElse;
}

//Methods

void Nodes::addEdge(Edges newEdge) {
	for (Edges edge : edges) {
		if (edge.getNextNode() == newEdge.getNextNode()) {
			if (edge.getConditionalOperation().empty() && !newEdge.getConditionalOperation().empty()) {
				edge.setCondtionalOperation(newEdge.getConditionalOperation());
			}
			return;
		}
	}

	edges.push_back(newEdge);
}

bool Nodes::hasConditionalEdge() {
	for (Edges edge : edges) {
		if (!edge.getConditionalOperation().empty()) {//if edge condition is not empty
			return true;
		}
	}
	return false;
}

bool Nodes::hasElseEdge() {
	for (Edges edge : edges) {
		if (!edge.getConditionalOperation().empty()) {//if edge condition is not empty
			if (edge.getConditionalOperation().find("else {") != string::npos) { //token.find("if") != string::npos
				return true;
			}
		}
	}
	return false;
}


void Nodes::printNode() {
	int i = 1;
	cout << "****************************************" << endl;
	cout << "Node: " << nodeNum << endl;
	cout << "Operation: " << operation << endl;
	cout << "ASAP: " << asapTime << endl;
	cout << "\tEdges\t" << endl;
	cout << "\t------------------------\t" << endl;
	if (edges.size() > 0) {
		for (Edges edge : edges) {
			cout << i << "." << endl;
			edge.printEdge();
			i++;
		}
	}
	else {
		cout << "\tNo Edges" << endl;
	}
}
