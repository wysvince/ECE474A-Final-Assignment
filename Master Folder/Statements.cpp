#include "Statements.h"

using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Constructors
Statements::Statements() {} // default constructor

Statements::Statements(string cond, string type) {
	this->cond = cond;
	if (type.compare("if") == true) {
		this->isIf = true;
	}
	else {
		this->isIf = false;
	}
	this->isClosed = false;
	this->hasElse = false;
}


void Statements::setCondition(string cond) {
	this->cond = cond;
}

void Statements::setOperation(Operations op) {
	this->operations.push_back(op);
}

void Statements::setConectState(Statements conState) {
	this->conState = conState;
}

void Statements::setNestState(Statements nestState) {
	this->nestStates.push_back(nestState);
}

void Statements::setClose(bool closed) {
	this->isClosed = closed;
}

void Statements::hasElse() {
	this->hasElse = true;
}

string Statements::getCondition() {
	return this->cond;
}
Statements* Statements::getConectState() {
	return this->conState;
}
Statements Statements::getNestState(vector<Statements>::size_type index){
	return this->nestStates.at(index);
}
bool Statements::getClose() {
	return this->isClosed;
}
bool Statements::getElse() {
	return this->hasElse;
}