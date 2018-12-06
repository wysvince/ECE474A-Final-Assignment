#include "WriteOutputFile.h"
#include "ReadInputFile.h"
#include "Variables.h"

using namespace std;
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

// constructor
WriteOutputFile::WriteOutputFile() {} // default constructor

// methods

string WriteOutputFile::retrieveDatawidth(int width, string datatype) {
	string str;
	if (datatype.compare("input") == 0) {
		if (width == 1) {
			str = "\tinput ";
		}
		else {
			str += "\tinput [" + to_string(width) + ":0] ";
		}
	}
	else if (datatype.compare("output") == 0) {
		if (width == 1) {
			str = "\toutput ";
		}
		else {
			str += "\toutput [" + to_string(width) + ":0] ";
		}
	}
	else if (datatype.compare("register") == 0) {
		if (width == 1) {
			str = "\tregister ";
		}
		else {
			str += "\tregister [" + to_string(width) + ":0] ";
		}
	}
	else {
		cout << "Error retrieving data type information!!" << endl;
	}
	
	return str;
}

// Circuit inputs and outputs can be declared on a line using the formats:
//	# input dataType inputName1, inputName2
//	# output dataType outputName1, outputName2
//	# variable dataType regName1, regName2
void WriteOutputFile::writeDatatypeInstantiation(ofstream & file, ReadInputFile &read)
{
	unsigned int size;
	string str;
	string str2;
	int width = 0;
	unsigned int index = 0;

	// inputs instantiation
	width = read.inputList.at(0).getWidth(); // retrive datawidth
	str += this->retrieveDatawidth(width, "input");
	size = read.inputList.size();

	while (index != size) {
		while (index < size) {
			if (read.inputList.at(index).getWidth() == width) {
				string vars = read.inputList.at(index).getName();
				str += vars;
				index++;
			}
			if ((index != size) && (read.inputList.at(index).getWidth() == width)) {
				str += ", ";
			}
			else {
				str += ";\n";
				file << str;									// string is complete, write to file
				if (index != size) {
					width = read.inputList.at(index).getWidth();	// get new datawidth
					str = this->retrieveDatawidth(width, "input");
				}
				break;
			}
		}
	}

	index = 0;	  // reset index
	str = "";	  // reset string
	file << "\n"; // insert new line for next instantiation
	// outputs instantiation
	width = read.outputList.at(0).getWidth(); // retrive datawidth
	str += this->retrieveDatawidth(width, "output");
	size = read.outputList.size();

	while (index != size) {
		while (index < size) {
			if (read.outputList.at(index).getWidth() == width) {
				string vars = read.outputList.at(index).getName();
				str += vars;
				index++;
			}
			if ((index != size) && (read.outputList.at(index).getWidth() == width)) {
				str += ", ";
			}
			else {
				str += ";\n";
				file << str;									// string is complete, write to file
				if (index != size) {
					width = read.outputList.at(index).getWidth();	// get new datawidth
					str = this->retrieveDatawidth(width, "output");			// reset string
				}
				break;
			}
		}
	}

	index = 0;	  // reset index
	str = "";	  // reset string
	file << "\n"; // insert new line for next instantiation
	// registers instantiation
	width = read.registerList.at(0).getWidth(); // retrive datawidth
	str += this->retrieveDatawidth(width, "register");
	size = read.registerList.size();

	while (index != size) {
		while (index < size) {
			if (read.registerList.at(index).getWidth() == width) {
				string vars = read.registerList.at(index).getName();
				str += vars;
				index++;
			}
			if ((index != size) && (read.registerList.at(index).getWidth() == width)) {
				str += ", ";
			}
			else {
				str += ";\n";
				file << str;									// string is complete, write to file
				if (index != size) {
					width = read.registerList.at(index).getWidth();	// get new datawidth
					str = this->retrieveDatawidth(width, "register");			// reset string
				}
				break;
			}
		}
	}
	file << "\n\n";
}

/* Write Operations, pretty easy so far just pastes the operation contents into the file with some
 * added syntax and spacing.
 */
void WriteOutputFile::writeOperations(ofstream &file, ReadInputFile &read) {
	int index = 0;
	int size;

	size = read.operationList.size();

	while (index != size) {

		file << "\t" << read.operationList.at(index).getOperation() << ";\n";

		index++;
	}

	file << "\n\n";
}

void WriteOutputFile::createHLSMHeader(ofstream & file)
{
	file << "module HLSM (Clk, Rst, Start, Done);" << endl << endl;
	file << "\tinput Clk, Rst, Start;" << endl;
	file << "\toutput reg Done;" << endl << endl;
}

void WriteOutputFile::writeGraph(ofstream & file, Graph graph) {
	//edges = graph.getEdges();
	nodes = graph.getNodes();
	weight = graph.getWeight();

	int numBits;
	int numTimes = 0;

	for (vector<Nodes>::size_type k = 0; k < nodes.size(); k++) {
		if (nodes.at(k).getListR() > numTimes) {
			numTimes = nodes.at(k).getListR();
		}
	}

	// Find the number of bits.
	numBits = this->findNumBits(numTimes + 2); //  total number of states (based on how many different time sections we have) + 2 for wait and final.
	
	// Write State machine.
	// Write States:
	file << "\treg [" << numBits - 1 << ", 0] state;\n" << endl; // total number of states -1 because we're assigning it's binary value.
	file << "\treg [" << numBits - 1 << ", 0] Wait = " << numBits << "'d0;" << endl;
	for (int ind = 0; ind < numTimes; ind++) {
		file << "\treg [" << numBits - 1 << ", 0] s" << ind + 1  << " = " << numBits << "'d" << ind + 1  << ";"<< endl; // + 1 because we're starting at the second point in the binary number.
	}
	file << "\treg [" << numBits - 1 << ", 0] Final = " << numBits << "'d" << numTimes + 1 << ";\n" << endl;

	// Start always @ (posedge Clk):
	file << "\talways @ (posedge Clk) begin : FSM" << endl;
	
	// Start If
	file << "\t\tif(Rst == 1'b1)begin" << endl;
	file << "\t\t\tstate <= Wait;" << endl;
	file << "\t\tend else\n" << endl; // Start else

	// Start Case:
	file << "\t\tcase(state)" << endl;

	// Define Wait State:
	file << "\t\t\tWait : begin" << endl;											// Start the Wait State:
	file << "\t\t\t\tif (Start == 1'b1) begin" << endl;								// If statement for Wait State, if (start == 1) Begin... 
	file << "\t\t\t\t\tstate <= s1" << endl;										// Set next state to be first node.
	file << "\t\t\t\tend" << endl;													// End the if.
	file << "\t\t\tend" << endl;													// End the state:

	// Define Scheduled State Cases:
	file << "\n\n\t\t\t// Define scheduled state cases here....\n\n" << endl;

	// Define Final State:
	file << "\t\t\tFinal : begin" << endl;											// Begin Final State.
	file << "\t\t\t\tDone <= 1'b1;" << endl << "\t\t\t\tState <= Wait;" << endl;	// Contents of Final State. (Set Done <= 1 and go to wait)
	file << "\t\t\tend\n" << endl;													// End Final State.

	// Default State:
	file << "\t\t\tdefault : begin" << endl;										// Begin Default state.
	file << "\t\t\t\tstate <= Wait;" << endl;										// Contents of default state. (go to wait)
	file << "\t\t\tend\n" << endl;													// End Default.

	// End Case:
	file << "\t\tendcase" << endl;

	// End always @ (posedge Clk):
	file << "\tend" << endl;

	// End the module.
	file << "endmodule" << endl;

	// Testing --------------------------------------------
	file << "\n\n// Just For testing will remove later:" << endl;
	file << "Graph: \n" << "Weight: " << weight << "\n";
	for (vector<Nodes>::size_type i = 0; i < nodes.size(); i++) {
		file << "Operation: " << nodes.at(i).getOperation() << endl;
		file << "ALAP Time: " << nodes.at(i).getALAP() << endl;
		file << "ASAP Time: " << nodes.at(i).getASAP() << endl;
		file << "\n";
	}
	file << "\n\n";
	// ----------------------------------------------------
}


void WriteOutputFile::wirteStates(ofstream & file, Graph graph) {

}

// Determines the number of bits we need for our states.
int WriteOutputFile::findNumBits(int numNodes) {
	if (numNodes < 2) {
		return 1;
	}
	else if (numNodes < 4) {
		return 2;
	}
	else if (numNodes < 8) {
		return 3;
	}
	else if (numNodes < 16) { 
		return 4;
	}
	else { // Probably not going to have more that 20 nodes so max will be 32.
		return 5;
	}
}