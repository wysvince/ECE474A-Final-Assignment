#include "Nodes.h"

using namespace std;

// constructors
Nodes::Nodes() {} // default constructor

Nodes::Nodes(int newStateNum, Edges newEdges, int newNumCycles, string op) {
	this->stateNum = newStateNum;
	this->edges.push_back(newEdges);
	this->numCycles = newNumCycles;
	this->operation = op;
}

// setters
// ADDED in from Alex S's Read file. ------------------------------------------------
void Nodes::setNodeNum(int newStateNum) {
	this->nodeNum = newStateNum;
}

void Nodes::setIfStatementLevel(int level) {
	this->ifStatementLevel = level;
}

void Nodes::setVariablesInvolved(vector<string> vbs) {
	variablesInvolved = vbs;
}

void Nodes::setWithinElse(bool b) {
	withinElse = b;
}
// ----------------------------------------------------------------------------------
void Nodes::setStateNum(int newStateNum) {
	this->stateNum = newStateNum;
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

void Nodes::setSlack(int num)
{
	this->slack = num;
}

void Nodes::setCycleCount(int num)
{
	this->cycleCount += num;
}

void Nodes::setASAP(int time) {
	this->asapTime = time;
}

void Nodes::setALAP(int time) {
	this->alapTime = time;
}

void Nodes::setListR(int time) {
	this->listRTime = time;
}

void Nodes::init() {
	if (edges.size() > 0) {
		this->edges.clear();
	}
	this->stateNum   = 0;
	this->numCycles  = 0;
	this->operation	 = "";
	this->alapTime	 = -1;
	this->asapTime	 = -1;
	this->listRTime	 = -1;
	this->slack		 = 0;
	this->cycleCount = 0;
}

// getters
// ADDED in from Alex S's Read file. ------------------------------------------------
int Nodes::getNodeNum() {
	return this->nodeNum;
}

int Nodes::getIfStatementLevel() {
	return ifStatementLevel;
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
// ----------------------------------------------------------------------------------
int Nodes::getStateNum() {
	return this->stateNum;
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

int Nodes::getSlack()
{
	return this->slack;
}

int Nodes::getCycleCount()
{
	return this->cycleCount;
}

int Nodes::getALAP() {
	return this->alapTime;
}

int Nodes::getASAP() {
	return this->asapTime;
}

int Nodes::getListR() {
	return this->listRTime;
}

//Methods
// ADDED in from Alex S's Read file. ------------------------------------------------
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

/*
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
*/

// ----------------------------------------------------------------------------------

void Nodes::calculateSlack(int alapTime, int currCycle)
{
	slack = alapTime - currCycle;
	if (slack < 0) {
		slack = 0;
	}
}


