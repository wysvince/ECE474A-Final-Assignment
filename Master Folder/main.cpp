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
	cout << "argv0:\t" << argv[0] << endl;									// DEBUGGING (Remove this)
	cout << "argv1:\t" << argv[1] << endl;									// DEBUGGING (Remove this)
	cout << "argv2:\t" << argv[2] << endl;									// DEBUGGING (Remove this)
	cout << "argv3:\t" << argv[3] << endl;									// DEBUGGING (Remove this)

	// Get data from input file
	if (inputFilename.is_open()) {
		read.fetchVariables(inputFilename, var);
		read.fetchOperations(inputFilename, op);
		
		inputFilename.close();
		inputFilename.open(argv[1]);
		read.handleOperations(inputFilename, &graph);
		
		cout << endl;
		for (Nodes node : graph.getNodes()) {
			node.printNode();	//PRINT NODES
		}
		cout << "****************************************" << endl;
		cout << endl << endl;

		cout << endl << "Graph's wait state edges:" << endl;
		for (Edges edge : graph.getEdges()) {
			edge.printEdge();
		}
		cout << "****************************************" << endl;

		//ALAP
		graph.createUnscheduledList();
		cout << endl << "After ALAP scheduling" << endl;
		int latency = std::stoi(argv[2]);
		graph.createALAPSchedule(latency);
		for (Nodes node : graph.getNodes()) {
			node.printNode();	//PRINT NODES
		}
		cout << "****************************************" << endl;
		cout << endl;	//END ALAP

		cout << "Creating ListR Start:" << endl;
		if (graph.createListRSchedule(latency) == false) {
			return -1;
		}
		cout << "Ending ListR" << endl;

		for (Nodes node : graph.getNodes()) {
			cout << "Node" << node.getNodeNum() << " list_R time: " << node.getListR() << endl;
		}

		// close input file
		inputFilename.close();
		cout << "File closed" << endl;										// DEBUGGING (Remove this)
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
		write.writeGraph(outputFilename, graph);
		// DEBUG ONLY ----------------------------------


		// close output file
		outputFilename.close();
	}
	else {	// Error!!
		cout << "Error: Output file doesn't exists." << endl;				
		return -1;
	}// Done: Generate output file 

	return 0;
}// end of main function

