#include "ReadInputFile.h"

using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

// constructor
ReadInputFile::ReadInputFile(){} // default constructor

//methods

// All empty lines should be ignored
// The netlist file can be assumed to be fully space/tab delimited, i.e. one or more space or tab characters should appear between each token 
// that needs to be parsed, including colons.
// Circuit inputs and outputs can be declared on a line using the formats:
//	# input dataType inputName1, inputName2
//	# output dataType outputName1, outputName2
//	# variable dataType regName1, regName2
// Perform following error checks while fetching variables from input file:
// 1. All names for inputs, outputs, and internal variables should be unique
// 2. All names for inputs, outputs, and internal variables are case sensitive and can consists of any number of
//    letters or digits.
// 3. Input, output, variable declarations should come before component instantiations.
void ReadInputFile::fetchVariables(ifstream &file, Variables &var) {
	string line;	// store single input string
	string token;	// string temp or word temp
	string token2;
	Operations op;  // for the break.

	char lastChar;	// use for checking last character of a line or word

	while (!file.eof()) {
		getline(file, line);
		istringstream streamLine(line);
		// cout << line << endl;	// Remove this; debugging only
		
		if (this->checkStatementLine(line) == true) {

			break;
		}
		else if (this->checkOperationLine(line) == true) {	// checks if line is an operation
			op.setOperation(line);
			this->operationList.push_back(op); // put the first op on list, then break.

			break;
		}
		else {
			if (line.find("input") != string::npos) {	// found inputs
				streamLine >> token;			// skip first word
				streamLine >> token;			// get data type
				streamLine >> token2;			// get first variable

				// remove any unnecessary ',' in a variable
				lastChar = token2.back();		// get last char of word
				while (lastChar == ',') {
					token2.pop_back();
					for (int i = 0; i < token2.length(); i++) {
						if (token2.at(i) == ' ' || token2.at(i) == '\t') {
							token2.erase(i, 1);
							i--;
						}
					}
					var.setName(token2);
					setWidthAndSign(var, token);
					this->inputList.push_back(var);
					streamLine >> token2;		// get subsequent or last variable
					lastChar = token2.back();
				}
				// last variable
				for (int i = 0; i < token2.length(); i++) {
					if (token2.at(i) == ' ' || token2.at(i) == '\t') {
						token2.erase(i, 1);
						i--;
					}
				}
				var.setName(token2);
				setWidthAndSign(var, token);
				this->inputList.push_back(var);
			}
			else if (line.find("output") != string::npos) {	// found inputs
				streamLine >> token;			// skip first word
				streamLine >> token;			// get data type
				streamLine >> token2;			// get first variable

				// remove any unnecessary ',' in a variable
				lastChar = token2.back();		// get last char of word
				while (lastChar == ',') {
					token2.pop_back();
					for (int i = 0; i < token2.length(); i++) {
						if (token2.at(i) == ' ' || token2.at(i) == '\t') {
							token2.erase(i, 1);
							i--;
						}
					}
					var.setName(token2);
					setWidthAndSign(var, token);
					this->outputList.push_back(var);
					streamLine >> token2;		// get subsequent or last variable
					lastChar = token2.back();
				}
				// last variable
				for (int i = 0; i < token2.length(); i++) {
					if (token2.at(i) == ' ' || token2.at(i) == '\t') {
						token2.erase(i, 1);
						i--;
					}
				}
				var.setName(token2);
				setWidthAndSign(var, token);
				this->outputList.push_back(var);
			}
			else if (line.find("variable") != string::npos) {	// found inputs
				streamLine >> token;			// skip first word
				streamLine >> token;			// get data type
				streamLine >> token2;			// get first variable

				// remove any unnecessary ',' in a variable
				lastChar = token2.back();		// get last char of word
				while (lastChar == ',') {
					token2.pop_back();
					for (int i = 0; i < token2.length(); i++) {
						if (token2.at(i) == ' ' || token2.at(i) == '\t') {
							token2.erase(i, 1);
							i--;
						}
					}
					var.setName(token2);
					setWidthAndSign(var, token);
					this->registerList.push_back(var);
					streamLine >> token2;		// get subsequent or last variable
					lastChar = token2.back();
				}
				// last variable
				for (int i = 0; i < token2.length(); i++) {
					if (token2.at(i) == ' ' || token2.at(i) == '\t') {
						token2.erase(i, 1);
						i--;
					}
				}
				var.setName(token2);
				setWidthAndSign(var, token);
				this->registerList.push_back(var);
			}
		}
	}
	this->checkDuplicatedVariables();
}

// Valid data types include:
//	# Signed integers: Int1, Int2, Int8, Int16, Int32, and Int64
//	# Unsigned integers: UInt1, UInt2, UInt8, UInt16, UInt32, and UInt64
void ReadInputFile::setWidthAndSign(Variables &var, string token) {
	
	// Datawidth 16 (Needs to check 16 bits first before checking 1 bit datawidth)
	if (token.find("UInt16") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(16);
	}
	else if (token.find("Int16") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(16);
	}
	// Datawidth 2
	else if (token.find("UInt2") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(2);
	}
	else if (token.find("Int2") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(2);
	}
	// Datawidth 8
	else if (token.find("UInt8") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(8);
	}
	else if (token.find("Int8") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(8);
	}
	// Datawidth 1
	else if (token.find("UInt1") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(1);
	}
	else if (token.find("Int1") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(1);
	}
	// Datawidth 32
	else if (token.find("UInt32") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(32);
	}
	else if (token.find("Int32") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(32);
	}
	// Datawidth 64
	else if (token.find("UInt64") != string::npos) {
		var.setIsSigned(false);
		var.setWidth(64);
	}
	else if (token.find("Int64") != string::npos) {
		var.setIsSigned(true);
		var.setWidth(64);
	}
	// Datawidth Unknown
	else {
		cout << "Error: Datawidth not specified." << endl;
	}
}

// Checks if variables in the operation line has been instantiated first
bool ReadInputFile::checksIfVariableInstantiated(string line) {
	bool flag = false;
	int find = -1;
	int exit = -1;
	istringstream streamLine(line);
	
	string firstVar;
	streamLine >> firstVar;
	while (exit == -1) {
		// checking first variable
		size_t found = firstVar.find_first_not_of("=+-*/><:?%");
		if (found != string::npos) {

			// 1st check: find 1st variable in output list
			for (Variables outp : this->outputList) {
				string temp = outp.getName();
				if (temp.compare(firstVar) == 0) {
					find = 1;
					exit = 1;
					break;
				}
				if (find == 1) {
					break;
				}
			}

			// 2nd check: if 1st variable not found in output list
			// check register list
			if (find == -1) {
				for (Variables reg : this->registerList) {
					string temp = reg.getName();
					if (temp.compare(firstVar) == 0) {
						find = 1;
						exit = 1;
						break;
					}
				}
				if (find == 1) {
					break;
				}
			}

			// Final check:  1st variable should not be input
			if (find == -1) {
				for (Variables inp : this->inputList) {
					string temp = inp.getName();
					if (temp.compare(firstVar) == 0) {
						find = 1;
						exit = 1;
						break;
					}
				}
				if (find == 1) {
					break;
				}
			}
		}
		
		// checking next variable(s)
		string nextVar;
		while (streamLine >> nextVar) {
			found = nextVar.find_first_not_of("=+-*/><:?%");
			if (found != string::npos) {

				for (Variables inp : this->inputList) {
					string temp = inp.getName();
					if (temp.compare(nextVar) == 0) {
						find = 1;
						exit = 1;
						break;
					}
					if (find == 1) {
						break;
					}
				}

				if (find == -1) {
					for (Variables outp : this->outputList) {
						string temp = outp.getName();
						if (temp.compare(nextVar) == 0) {
							find = 1;
							exit = 1;
							break;
						}
						if (find == 1) {
							break;
						}
					}
				}

				if (find == -1) {
					for (Variables reg : this->registerList) {
						string temp = reg.getName();
						if (temp.compare(nextVar) == 0) {
							find = 1;
							exit = 1;
							break;
						}
						if (find == 1) {
							break;
						}
					}
				}
			}
		}
	}
	if (find == 1) {
		flag = true;
	}
	return flag;
}

// fetch operations
void ReadInputFile::fetchOperations(ifstream &file, Operations &operation) {
	string line;

	// strings for finding operations:
	/*
	string output;
	string in1;
	string in2;
	string sel;
	string op;
	*/

	while (!file.eof()) {
		getline(file, line);
		string str;
		istringstream streamLine(line);

		//streamLine >> str;		// output variable
		//streamLine >> str;		// operation symbol
		//streamLine >> str;		// first variable after '='
		/* Commenting for now will want this, I'm thinking of making the statement have a vector of operations and saving if there is an open if/else.
		 * Going to use the if/else as a container for the operations to make the initial graph creation easier, otherwise we would want to save locations
		 * of {} for finding which operations (nodes) are linked.
		if (this->checkStatementLine(line) == true) {
			
			break;
		}*/
		if (checkOperationLine(line)) {
			
			/* Just in case. May want to save inputs and output for linking nodes later, for now keeping these out to make sure it actually reads the operation and can print it.
			streamLine >> output;
			streamLine >> in1;					// Skip the = sign.

			if (line.find_first_of(":") != string::npos) {
				streamLine >> sel;
				streamLine >> op;
				streamLine >> in1;
				streamLine >> in2;				// Skip the : sign.
				streamLine >> in2;
			}
			else {
				streamLine >> in1;
				streamLine >> op;
				streamLine >> in2;
			}
			*/

			// Checks if variables has been previously instantiated
			if (this->checksIfVariableInstantiated(line) == false) {
				break;
			}
			else {
				// Set Operation.
				operation.setOperation(line);
				this->operationList.push_back(operation);
			}
		}
		else {
			break;
		}
	}
}

/*
void ReadInputFile::fetchStatements(ifstream &file, Variables &var) {

}
*/

bool ReadInputFile::checkOperationLine(string line) {
	bool flag = false;
	size_t found = line.find_first_of("=+-*/><:?%");
	if (found != string::npos) {
		flag = true;	// flag high: found error!!
	}
	return flag;
}

bool ReadInputFile::checkStatementLine(string line) {
	bool flag = false;
	size_t found = line.find("if (");
	if (found != string::npos) {
		flag = true;	// flag high: found error!!
	}
	return flag;
}

void ReadInputFile::checkDuplicatedVariables(){
	int exit = -1;
	unsigned int size;
	unsigned int size2;
	vector<Variables> tempList; // temporary list for comparison
	string currName;	// current variable name assigned
	string compName;	// compare current variable name to this

	while (exit == -1) {
		// checking for duplicated variables in inputList
		tempList = inputList;
		size = inputList.size();
		for (int i = 0; i < size; i++) {
			currName = inputList.at(i).getName();
			tempList.erase(tempList.begin());
			size2 = tempList.size();
			for (int j = 0; j < size2; j++) {
				compName = tempList.at(j).getName();
				if (compName.compare(currName) == 0) {
					inputList.erase(inputList.begin() + i); // found duplicate, remove from list
					i = size;
					exit = 1;
					break;
				}
			}
		}

		// checking for duplicated variables in outputList
		tempList = outputList;
		size = outputList.size();
		for (int i = 0; i < size; i++) {
			currName = outputList.at(i).getName();
			tempList.erase(tempList.begin());
			size2 = tempList.size();
			for (int j = 0; j < size2; j++) {
				compName = tempList.at(j).getName();
				if (compName.compare(currName) == 0) {
					outputList.erase(outputList.begin() + i); // found duplicate, remove from list
					i = size;
					exit = 1;
					break;
				}
			}
		}

		// checking for duplicated variables in registerList
		tempList = registerList;
		size = registerList.size();
		for (int i = 0; i < size; i++) {
			currName = registerList.at(i).getName();
			tempList.erase(tempList.begin());
			size2 = tempList.size();
			for (int j = 0; j < size2; j++) {
				compName = tempList.at(j).getName();
				if (compName.compare(currName) == 0) {
					registerList.erase(registerList.begin() + i); // found duplicate, remove from list
					i = size;
					exit = 1;
					break;
				}
			}
		}
		exit = 1;
	}
}
	/*	Converts all operations into Node objects, then determines edges dependecies with
		other Nodes, updates those Node edges, and finally adds the node to the graph with 
		an ASAP schedule																	*/
int ReadInputFile::handleOperations(ifstream &file, Graph* graph){ 
	string inputLine;
	string token, token2;
	Nodes newNode;
	vector<string> allVariables;
	vector<string> braceOpener;				//Keeps track of current brace opener. When we find a '}' we know what it is closing
	vector<string> conditionVariables;		//Keeps track of nested conditions. EX: if(a) { if(b) { } } we will know a && b so can become if (a && b) { }
	string potentialElseVar;
	int insideIfStatements = 0;

	bool validVariable = false;
	bool doneWithLine = false;
	bool isIfElseStatement = false;
	bool skipLine = false;
	bool withinElse = false;
	int nodeNum = 0;

	while (!file.eof()) {
		skipLine = false;
		doneWithLine = false;
		isIfElseStatement = false;
		validVariable = false;

		if (!braceOpener.empty()) {
			if (braceOpener.back() == "else") {	//Check if operation is within an 'else' 
				withinElse = true;
			}
			else {
				withinElse = false;
			}
		}

		getline(file, inputLine);

		for (int i = 0; i < inputLine.length(); ++i) {
			if (inputLine.at(i) == ' ' || inputLine.at(i) == '\t') {
				inputLine.erase(i, 1);
				i--;
			}
			else {
				break;
			}
		}

		istringstream inputLineStream(inputLine);
		//verify output variable
		inputLineStream >> token;
		if (inputLine.empty())
		{
			doneWithLine = true;		//Valid line (empty, do nothing)
			skipLine = true;
		}
		else if (token.length() >= 2)
		{
			if (token[0] == '/' && token[1] == '/')
			{
				doneWithLine = true;	//entire line is a comment	//Valid Line (comment, do nothing)
				skipLine = true;
			}
			else if (token.compare("input") == 0 || token.compare("output") == 0 || token.compare("variable") == 0)
			{
				doneWithLine = true;		//Line is valid, but not an operation
				skipLine = true;
			}
		}
		if (!doneWithLine) {
			if (token[0] == '{')
			{
				doneWithLine = true;
				skipLine = true;
			}
			if (token[0] == '}')
			{
				if (braceOpener.empty()) {
					return -1;					//ERROR closing brace with no opening brace
				}
				if (braceOpener.back() == "if") { 
					insideIfStatements--;
					potentialElseVar = conditionVariables.back();
					potentialElseVar = "!" + potentialElseVar;
					conditionVariables.pop_back();
				}
				else if (braceOpener.back() == "else") {
					//Might not need to do anything unique?
					conditionVariables.pop_back();
				}
				else if (braceOpener.back() == "for") {
					//FIXME incomplete
				}
				else {
					//rogue } symbol?
					return -1;			//ERROR
				}
				braceOpener.pop_back();
				doneWithLine = true;
				skipLine = true;
			}
		}
		if (!doneWithLine && token.find("if") != string::npos)	
		{
			inputLineStream >> token;
			inputLineStream >> token;

			for (unsigned int i = 0; i < outputList.size(); ++i)
			{
				if (outputList[i].getName() == token)
				{
					validVariable = true;	//Valid Output
					conditionVariables.push_back(token);
					break;
				}
			}
			if (!validVariable)
			{
				for (unsigned int i = 0; i < registerList.size(); ++i)
				{
					if (registerList[i].getName() == token)
					{
						validVariable = true;	//Valid Output
						conditionVariables.push_back(token);
						break;
					}
				}
			}
			if (!validVariable)
			{
				for (unsigned int i = 0; i < inputList.size(); ++i)
				{
					if (inputList[i].getName() == token)
					{
						validVariable = true;	//Valid Output
						conditionVariables.push_back(token);
						break;
					}
				}
			}
			if (!validVariable) {
				cout << "If statement \"" << inputLine << "\" has invalid condition variable: " << token << endl;
				return -1;																			//ERROR
			}

			insideIfStatements++;		
			braceOpener.push_back("if");
			doneWithLine = true;
			isIfElseStatement = true;
		}
		else if (!doneWithLine && token.find("else") != string::npos) {
			if (!potentialElseVar.empty()) {
				conditionVariables.push_back(potentialElseVar);
			}
			else {
				cout << "Error getting else condition" << endl;
				return -1;
			}
			braceOpener.push_back("else");
			doneWithLine = true;
			skipLine = true;
		}
		else if (!doneWithLine && token.find("for") != string::npos) {	//FIXME 
			braceOpener.push_back("for");
			cout << "FIXME: Loops are not handled correctly. Exiting with error" << endl;
			return -1;
		}
		if (!doneWithLine) {
			for (unsigned int i = 0; i < outputList.size(); ++i)
			{
				if (outputList[i].getName() == token)
				{
					validVariable = true;	//Valid Output
					allVariables.push_back(token);
					break;
				}
			}
			if (!validVariable)
			{
				for (unsigned int i = 0; i < registerList.size(); ++i)
				{
					if (registerList[i].getName() == token)
					{
						validVariable = true;	//Valid Output
						allVariables.push_back(token);
						//cout << "output: " << token << endl;
						break;
					}
				}
			}
			if (!validVariable)
			{
				//cout << "cannot assign this variable: " << token << "\t (must be output or wire)" << '\n';	//ERROR
				return -1;																					//ERROR
			}

			inputLineStream >> token;
			if (token != "=")
			{
				//cout << "invalid operation - output must be set equal to operation" << "\n";	//ERROR
				return -1;																		//ERROR
			}

			//verify first variable
			validVariable = false;
			inputLineStream >> token;

			if (token.length() != 0)
			{
				for (unsigned int i = 0; i < registerList.size(); ++i)
				{
					if (registerList[i].getName() == token)
					{
						validVariable = true;	//Valid first Variable after operator
						allVariables.push_back(token);
						break;
					}
				}
			}
			if (!validVariable)
			{
				for (unsigned int i = 0; i < inputList.size(); ++i)
				{
					if (inputList[i].getName() == token)
					{
						validVariable = true;	//Valid first Variable after operator
						allVariables.push_back(token);
						break;
					}
				}
			}
			if (!validVariable)
			{
				for (unsigned int i = 0; i < outputList.size(); ++i)
				{
					if (outputList[i].getName() == token)
					{
						validVariable = true;	//Valid first Variable after operator
						allVariables.push_back(token);
						break;
					}
				}
			}
			if (!validVariable)
			{
				//cout << "Could not identity input/wire variable: " << token << " \n";	
				return -1;																//ERROR
			}

			//identify operator
			validVariable = false;
			if (inputLineStream.eof())
			{
				token = "";
			}
			else
			{
				inputLineStream >> token;
			}
			if (inputLineStream.eof())
			{
				token2 = "";
			}
			else
			{
				inputLineStream >> token2;
			}

			//verify second variable
			if (token2.length() != 0)
			{
				for (unsigned int i = 0; i < registerList.size(); ++i)
				{
					if (registerList[i].getName() == token2)
					{
						validVariable = true;	//Valid second Variable after operator
						allVariables.push_back(token2);
						break;
					}
				}

				if (!validVariable)
				{
					for (unsigned int i = 0; i < inputList.size(); ++i)
					{
						if (inputList[i].getName() == token2)
						{
							validVariable = true;	//Valid second Variable after operator
							allVariables.push_back(token2);
							break;
						}
					}
				}
				if (!validVariable)
				{
					for (unsigned int i = 0; i < outputList.size(); ++i)
					{
						if (outputList[i].getName() == token2)
						{
							validVariable = true;	//Valid second Variable after operator
							allVariables.push_back(token2);
							break;
						}
					}
				}
				if (!validVariable)
				{
					//cout << "Invalid variable: " << token2 << "\n";	//ERROR
					return -1;											//ERROR
				}
			}
				//identify operator
			if (token.empty())	//REG
			{
				newNode.setOperation(inputLine);
				newNode.setNumCycles(1);
				doneWithLine = true;			//Valid output
			}
			if (validVariable && !doneWithLine)	//Means there was a second variable, indicating an operation other than x = y
			{
				if (token == "+" || token == "-" || token == "*" || token == "<<" || token == ">>")		//ADD, SUB, MUL, SHL, SHR
				{
					newNode.setOperation(inputLine);
					if (token == "*") {
						newNode.setNumCycles(2);	//Multipliers take 2 cycles
					}
					else {
						newNode.setNumCycles(1);	//ALUs take 1 cycle
					}
					doneWithLine = true;
				}
				else if (token == "?")		//MUX
				{
					inputLineStream >> token;
					if (token == ":")	//Mux operation continues
					{
						validVariable = false;
						inputLineStream >> token;

						if (token.length() != 0)
						{
							for (unsigned int i = 0; i < registerList.size(); ++i)
							{
								if (registerList[i].getName() == token)
								{
									validVariable = true;	//Valid third variable after = operator (already verified 2nd before checking operation type
									allVariables.push_back(token);
									break;
								}
							}
						}
						if (!validVariable)
						{
							for (unsigned int i = 0; i < inputList.size(); ++i)
							{
								if (inputList[i].getName() == token)
								{
									validVariable = true;	//Valid third variable after = operator
									allVariables.push_back(token);
									break;
								}
							}
						}
						if (!validVariable)
						{
							for (unsigned int i = 0; i < outputList.size(); ++i)
							{
								if (outputList[i].getName() == token)
								{
									validVariable = true;	//Valid third variable after = operator
									allVariables.push_back(token);
									break;
								}
							}
						}
						if (!validVariable)
						{
							//cout << "Invalid variable: " << token << "\n";		//ERROR
							return -1;												//ERROR missing third variable for mux comparison
						}
						else {
							newNode.setOperation(inputLine);
							newNode.setNumCycles(1);
							doneWithLine = true;
						}
					}
					else
					{
						//cout << "Invalid operator: " << token << "\n";		//ERROR
						return -1;												//ERROR
					}

				}
				else		//must be comparator or invalid operator
				{
					//determine output to wire
					if (token == ">" || token == "==" || token == "<")
					{
						newNode.setNumCycles(1);
					}
					else
					{
						//cout << "Invalid operator: " << token << "\n";	//ERROR
						return -1;												//ERROR
					}

					//cout << translatedLine << "\n";
					newNode.setOperation(inputLine);
					doneWithLine = true;							//valid output
				}
			}
			else if (!doneWithLine)
			{
				//cout << "Incomplete operation \n";			//ERROR
				return -1;												//ERROR
			}
		} 
		//At this point, must be valid operation or edge condition ( i.e. if(blah) )

		if (!isIfElseStatement && !skipLine) {
			newNode.setWithinElse(withinElse);
			newNode.setNodeNum(nodeNum);
			newNode.setVariablesInvolved(allVariables);
			if (insideIfStatements == 0) {
				graph->addNode(newNode, 0, conditionVariables);
			}
			else {
				graph->addNode(newNode, insideIfStatements, conditionVariables);
			}
			allVariables.clear();
			nodeNum++;
		}
		
	}	//End of File line iteration
	

	return 1;
} //End of HandleOperations

void ReadInputFile::printVariables() {
	cout << "Inputs: " << endl;
	for (Variables vb : inputList) {
		cout << "\t" << vb.getName() << "..." << endl;
	}
	cout << endl << "Outputs: " << endl;
	for (Variables op : outputList) {
		cout << "\t" << op.getName() << "..." << endl;
	}
	cout << endl << "Registers: " << endl;
	for (Variables rg : registerList) {
		cout << "\t" << rg.getName() << "..." << endl;
	}
}