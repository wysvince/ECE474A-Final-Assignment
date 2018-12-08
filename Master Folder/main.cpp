//#include "Edges.h"
//#include "Nodes.h"
//#include "Graph.h"

#include "Variables.h"
#include "ReadInputFile.h"
#include "WriteOutputFile.h"
#include "Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;


//////// F U N C T I O N   M A I N ////////////////////////////
int main(int argc, char* argv[]) {
	
	// check command line arguments
	if (argc != 4) {
		cout << "ERROR: Incorrect arguments." << endl;
		cout << "Correct argumets:\thlsyn cFile latency verilogFile" << endl;
		return -1;
	}

	ifstream inputFilename;
	ofstream outputFilename;
	
	// Class objects
	Variables var;
	Operations op;
	//Statements state; 
	ReadInputFile read;
	WriteOutputFile write;
	
	// Testing Graph Class ------------------------
	Graph graph;
	Nodes tempNode;
	Edges tempEdge;
	int tempWeight = 0;
	// --------------------------------------------


	inputFilename.open(argv[1]);

	// Get data from input file
	if (inputFilename.is_open()) {
		read.fetchVariables(inputFilename, var);
		read.fetchOperations(inputFilename, op);
		
		inputFilename.close();
		inputFilename.open(argv[1]);
		if (read.handleOperations(inputFilename, &graph) == -2) {
			cout << "Invalid variable" << endl;
			return -1;
		}

		if (graph.getNodes().size() == 0) {
			cout << "Could not create graph" << endl;
			return -1;
		}

		//ALAP
		graph.createUnscheduledList();

		int latency = std::stoi(argv[2]);
		graph.createALAPSchedule(latency);

		if (graph.createListRSchedule(latency) == false) {
			return -1;
		}

		// close input file
		inputFilename.close();
	}
	else {	// Error!!
		cout << "Error: Input file doesn't exists." << endl;
		return -1;
	} // Done: Get data from input file


//////////// Generate output file ////////////////////////////////////////////////////////////////////////////////////
	outputFilename.open(argv[3]);
	if (outputFilename.is_open()) {

		// DEBUG ONLY ----------------------------------
		write.createHLSMHeader(outputFilename);
		write.writeDatatypeInstantiation(outputFilename, read);
		write.writeGraph(outputFilename, graph);
		// DEBUG ONLY ----------------------------------


		// close output file
		outputFilename.close();
	}
	else {	// Error!!
		cout << "Error: Output file doesn't exists." << endl;				
		return -1;
	}// Done: Generate output file 

	return 1;
}// end of main function

