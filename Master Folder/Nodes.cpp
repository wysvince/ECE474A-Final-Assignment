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

// getters
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

//Methods

void Nodes::addEdge(Edges newEdge) {
	edges.push_back(newEdge);
}

void Nodes::calculateSlack(int alapTime, int currCycle)
{
	slack = alapTime - currCycle;
	if (slack < 0) {
		slack = 0;
	}
}


