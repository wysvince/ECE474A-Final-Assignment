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
		/* Not working for mine so commented for now. */
		cout << "Opened File for read" << endl;								// DEBUGGING (Remove this)
		
		// fetching variables from input file
		cout << "Fetching variables" << endl;								// DEBUGGING (Remove this)
		read.fetchVariables(inputFilename, var);
		cout << "Fetching variables completed" << endl;						// DEBUGGING (Remove this)

		// fetching operations from input file
		cout << "Fetching operations" << endl;
		read.fetchOperations(inputFilename, op);
		cout << "Fetching operations completed" << endl;					// DEBUGGING (Remove this)
		
		// fetching statements from input file
		//cout << "Fetching statements" << endl;
		//read.fetchStatements(inputFilename, state);
		//cout << "Fetching statements completed" << endl;					// DEBUGGING (Remove this)
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

		// close input file
		inputFilename.close();
		cout << "File closed" << endl;										// DEBUGGING (Remove this)
	}
	else {	// Error!!
		cout << "Error: Input file doesn't exists." << endl;
		return -1;
	} // Done: Get data from input file

//////////// Generate graph ////////////////////////////////////////////////////////////////////////////////////////////////
	// Testing Graph Class ------------------------------- 
/*	cout << "Start Writing Graph" << endl;

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Test graph of "error1.c":

	// Node 1
	tempNode.setOperation("d = a + b");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	//tempNode.setListR(1);
	tempNode.setNodeNum(1);
	tempEdge.setPrevNode(1);
	tempEdge.setNextNode(3);
	tempEdge.setCondtionalOperation("if ( d ) {");
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode, 0, vector<string>());

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 2
	tempNode.setOperation("e = a + c");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	//tempNode.setListR(2);
	tempNode.setNodeNum(2);
	tempEdge.setPrevNode(-1);
	tempEdge.setNextNode(3);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode, 0, vector<string>());

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 3
	tempNode.setOperation("g = d > e");
	tempNode.setNumCycles(1);
	tempNode.setASAP(2);
	//tempNode.setListR(3);
	tempNode.setNodeNum(3);
	tempEdge.setPrevNode(1);
	tempEdge.setNextNode(4);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode, 0, vector<string>());

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 4
	tempNode.setOperation("z = g ? d : e");
	tempNode.setNumCycles(1);
	tempNode.setASAP(3);
	//tempNode.setListR(4);
	tempNode.setNodeNum(4);
	tempEdge.setPrevNode(3);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode, 0, vector<string>());

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 5
	tempNode.setOperation("f = a * c");
	tempNode.setNumCycles(2);
	tempNode.setASAP(1);
	//tempNode.setListR(1);
	tempNode.setNodeNum(5);
	tempEdge.setPrevNode(4);
	tempEdge.setNextNode(5);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode, 0, vector<string>());

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 6
	tempNode.setOperation("x = f - d");
	tempNode.setNumCycles(1);
	tempNode.setASAP(2);
	//tempNode.setListR(3);
	tempNode.setNodeNum(6);
	tempEdge.setPrevNode(5);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode, 0, vector<string>());

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Adding list of edges to Graph
	tempEdge.setPrevNode(-1);
	tempEdge.setNextNode(1);
	graph.addEdges(tempEdge);
	tempEdge.init();
	tempEdge.setPrevNode(-1);
	tempEdge.setNextNode(2);
	graph.addEdges(tempEdge);
	tempEdge.init();
	tempEdge.setPrevNode(-1);
	tempEdge.setNextNode(5);
	graph.addEdges(tempEdge);
	tempEdge.init();
	tempEdge.setPrevNode(1);
	tempEdge.setNextNode(6);
	graph.addEdges(tempEdge);
	tempEdge.init();
	tempEdge.setPrevNode(1);
	tempEdge.setNextNode(3);
	graph.addEdges(tempEdge);
	tempEdge.init();
	tempEdge.setPrevNode(2);
	tempEdge.setNextNode(3);
	graph.addEdges(tempEdge);
	tempEdge.init();
	tempEdge.setPrevNode(3);
	tempEdge.setNextNode(4);
	graph.addEdges(tempEdge);
	tempEdge.init();
	tempEdge.setPrevNode(5);
	tempEdge.setNextNode(6);
	graph.addEdges(tempEdge);
	tempEdge.init();
	tempEdge.setPrevNode(6);
	tempEdge.setNextNode(-1);
	graph.addEdges(tempEdge);
	tempEdge.init();
	tempEdge.setPrevNode(4);
	tempEdge.setNextNode(-1);
	tempEdge.init();

	cout << "Graph Written" << endl;
	// End of Test graph writting.

	cout << "Start ALAP" << endl;
	graph.createALAPSchedule(7);
	cout << "End ALAP" << endl;

	cout << "Start ListR" << endl;
	graph.createListRSchedule(7);
	cout << "End ListR" << endl;

	// ----------------------------------------------------
	// Done: Generate graph
	// Generate ALAP Schedule
	// Generate List_R Schedule
	//graph.createListRSchedule(latency);	*/
	int latency = std::stoi(argv[2]);
	graph.createUnscheduledList();
	graph.createALAPSchedule(latency);

//////////// Generate states //////////////////////////////////////////////////////////////////////////////////////////

	// Done: Generate states

//////////// Generate output file ////////////////////////////////////////////////////////////////////////////////////
	outputFilename.open(argv[3]);
	if (outputFilename.is_open()) {
		/* Not working for mine so commented for now.
		cout << "Opened file for write" << endl;							// DEBUGGING (Remove this)
		// writing to output file
		write.createHLSMHeader(outputFilename);
		cout << "Wrote HLSM Header" << endl;								// DEBUGGING (Remove this)
		write.writeDatatypeInstantiation(outputFilename, read);
		cout << "Wrote Datatype Instantiations" << endl;					// DEBUGGING (Remove this)
		write.writeOperations(outputFilename, read);
		cout << "Wrote Operations" << endl;									// DEBUGGING (Remove this)
		*/

		// DEBUG ONLY ----------------------------------
		cout << "\n\n\n";
		write.createHLSMHeader(outputFilename);
		write.writeGraph(outputFilename, graph);
		// DEBUG ONLY ----------------------------------


		// close output file
		outputFilename.close();
		cout << "File closed" << endl;										// DEBUGGING (Remove this)
	}
	else {	// Error!!
		cout << "Error: Output file doesn't exists." << endl;				// DEBUGGING (Remove this)
		return -1;
	}// Done: Generate output file 

	cout << "Reached the end of main" << endl;								// DEBUGGING (Remove this)
	return 0;
}// end of main function

// JUST FOR TESTING 

// Adding some test functions to make testing a little easier...
/*
void setError(Nodes tempNode, Edges tempEdge, Graph & graph) {

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Test graph of "error1.c":

	// Node 1
	tempNode.setOperation("d = a + b");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(1);
	tempEdge.setPrevNode(0);
	tempEdge.setNextNode(2);
	tempEdge.setCondtionalOperation("if ( d ) {");
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 2
	tempNode.setOperation("e = a + c");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(2);
	tempEdge.setPrevNode(1);				// Edge 1
	tempEdge.setNextNode(2);
	tempNode.addEdge(tempEdge);

	tempEdge.init();
	tempEdge.setPrevNode(1);				// Edge 2
	tempEdge.setNextNode(5);
	tempNode.addEdge(tempEdge);

	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 3
	tempNode.setOperation("g = d > e");
	tempNode.setNumCycles(1);
	tempNode.setASAP(2);
	tempNode.setListR(3);
	tempEdge.setPrevNode(2);
	tempEdge.setNextNode(3);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 4
	tempNode.setOperation("z = g ? d : e");
	tempNode.setNumCycles(1);
	tempNode.setASAP(3);
	tempNode.setListR(4);
	tempEdge.setPrevNode(3);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 5
	tempNode.setOperation("f = a * c");
	tempNode.setNumCycles(2);
	tempNode.setASAP(1);
	tempNode.setListR(1);
	tempEdge.setPrevNode(4);
	tempEdge.setNextNode(5);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 6
	tempNode.setOperation("x = f - d");
	tempNode.setNumCycles(1);
	tempNode.setASAP(2);
	tempNode.setListR(3);
	tempEdge.setPrevNode(5);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();
}

void setHLS8(Nodes tempNode, Edges tempEdge, Graph & graph) {
	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Test graph of "error1.c":

	// Node 1
	tempNode.setOperation("t1 = x0 + x1");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(3);
	tempEdge.setPrevNode(0);				// Edge 1
	tempEdge.setNextNode(2);
	tempNode.addEdge(tempEdge);

	tempEdge.init();
	tempEdge.setPrevNode(1);				// Edge 2
	tempEdge.setNextNode(5);
	tempNode.addEdge(tempEdge);

	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 2
	tempNode.setOperation("d1 = t1 + c0");
	tempNode.setNumCycles(1);
	tempNode.setASAP(2);
	tempNode.setListR(6);
	tempEdge.setPrevNode(1);
	tempEdge.setNextNode(-1);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 3
	tempNode.setOperation("vd1 = t1 * c0");
	tempNode.setNumCycles(2);
	tempNode.setASAP(2);
	tempNode.setListR(4);
	tempEdge.setPrevNode(2);
	tempEdge.setNextNode(3);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 4
	tempNode.setOperation("d2 = vd1 * five");
	tempNode.setNumCycles(2);
	tempNode.setASAP(3);
	tempNode.setListR(6);
	tempEdge.setPrevNode(3);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 5
	tempNode.setOperation("t2 = x1 + x2");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(1);
	tempEdge.setPrevNode(4);				// Edge 1
	tempEdge.setNextNode(7);
	tempNode.addEdge(tempEdge);

	tempEdge.init();
	tempEdge.setPrevNode(4);				// Edge 2
	tempEdge.setNextNode(6);
	tempNode.addEdge(tempEdge);

	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 6
	tempNode.setOperation("t3 = x3 + c0");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(2);
	tempEdge.setPrevNode(5);				// Edge 1
	tempEdge.setNextNode(7);
	tempNode.addEdge(tempEdge);

	tempEdge.init();
	tempEdge.setPrevNode(5);				// Edge 2
	tempEdge.setNextNode(6);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 7
	tempNode.setOperation("e = t2 * t3");
	tempNode.setNumCycles(2);
	tempNode.setASAP(2);
	tempNode.setListR(6);
	tempEdge.setPrevNode(6);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 8
	tempNode.setOperation("ve = t2 * t3");
	tempNode.setNumCycles(2);
	tempNode.setASAP(2);
	tempNode.setListR(3);

	tempEdge.setPrevNode(7);				// Edge 1
	tempEdge.setNextNode(9);
	tempNode.addEdge(tempEdge);

	tempEdge.init();
	tempEdge.setPrevNode(7);				// Edge 2
	tempEdge.setNextNode(8);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 9
	tempNode.setOperation("f = ve * y0");
	tempNode.setNumCycles(2);
	tempNode.setASAP(3);
	tempNode.setListR(6);
	tempEdge.setPrevNode(8);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 10
	tempNode.setOperation("vf = v3 * y0");
	tempNode.setNumCycles(2);
	tempNode.setASAP(3);
	tempNode.setListR(5);
	tempEdge.setPrevNode(9);
	tempEdge.setNextNode(12);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 11
	tempNode.setOperation("g = x0 - ten");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(5);
	tempEdge.setPrevNode(10);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 12
	tempNode.setOperation("vg = x0 - ten");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(4);
	tempEdge.setPrevNode(11);
	tempEdge.setNextNode(12);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 13
	tempNode.setOperation("h = vf + vg");
	tempNode.setNumCycles(1);
	tempNode.setASAP(4);
	tempNode.setListR(7);
	tempEdge.setPrevNode(12);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();
}

void setIf3(Nodes tempNode, Edges tempEdge, Graph & graph) {
	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Test graph of "error1.c":

	// Node 1
	tempNode.setOperation("d = a + b");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(1);
	tempEdge.setPrevNode(0);
	tempEdge.setNextNode(4);
	tempNode.addEdge(tempEdge);				// Edge 1

	tempEdge.init();
	tempEdge.setPrevNode(0);
	tempEdge.setNextNode(8);
	tempNode.addEdge(tempEdge);				// Edge 2

	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 2
	tempNode.setOperation("e = a + c");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(2);
	tempEdge.setPrevNode(1);
	tempEdge.setNextNode(3);
	tempNode.addEdge(tempEdge);				// Edge 1

	tempEdge.init();
	tempEdge.setPrevNode(1);
	tempEdge.setNextNode(4);
	tempNode.addEdge(tempEdge);				// Edge 2

	tempEdge.init();
	tempEdge.setPrevNode(1);
	tempEdge.setNextNode(6);
	tempNode.addEdge(tempEdge);				// Edge 3

	tempEdge.init();
	tempEdge.setPrevNode(1);
	tempEdge.setNextNode(9);
	tempNode.addEdge(tempEdge);				// Edge 4

	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 3
	tempNode.setOperation("f = a - b");
	tempNode.setNumCycles(1);
	tempNode.setASAP(1);
	tempNode.setListR(3);
	tempEdge.setPrevNode(2);
	tempEdge.setNextNode(7);
	tempNode.addEdge(tempEdge);				// Edge 1

	tempEdge.init();
	tempEdge.setPrevNode(2);
	tempEdge.setNextNode(9);
	tempNode.addEdge(tempEdge);				// Edge 2

	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 4
	tempNode.setOperation("dEQe = d == e");
	tempNode.setNumCycles(1);
	tempNode.setASAP(2);
	tempNode.setListR(3);
	tempEdge.setPrevNode(3);
	tempEdge.setNextNode(5);
	tempNode.addEdge(tempEdge);				// Edge 1
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 5
	tempNode.setOperation("dLTe = d > e");
	tempNode.setNumCycles(1);
	tempNode.setASAP(2);
	tempNode.setListR(4);
	tempEdge.setPrevNode(4);
	tempEdge.setNextNode(5);
	tempNode.addEdge(tempEdge);				// Edge 1
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 6
	tempNode.setOperation("dLTEe = dEQe + dLTe");
	tempNode.setNumCycles(1);
	tempNode.setASAP(3);
	tempNode.setListR(5);
	tempEdge.setPrevNode(5);
	tempEdge.setNextNode(6);
	tempEdge.setCondtionalOperation("if ( dLTEe && dLTe ) {");
	tempNode.addEdge(tempEdge);				// Edge 1

	tempEdge.init();
	tempEdge.setPrevNode(5);
	tempEdge.setNextNode(7);
	tempEdge.setCondtionalOperation("if ( dLTEe && dLTe ) {");
	tempNode.addEdge(tempEdge);				// Edge 2

	tempEdge.init();
	tempEdge.setPrevNode(5);
	tempEdge.setNextNode(8);
	tempEdge.setCondtionalOperation("if ( dLTEe ) {");
	tempNode.addEdge(tempEdge);				// Edge 3

	tempEdge.init();
	tempEdge.setPrevNode(5);
	tempEdge.setNextNode(9);
	tempEdge.setCondtionalOperation("if ( dLTEe ) {");
	tempNode.addEdge(tempEdge);				// Edge 4
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 7
	tempNode.setOperation("g = e + one");
	tempNode.setNumCycles(1);
	tempNode.setASAP(4);
	tempNode.setListR(7);
	tempEdge.setPrevNode(6);
	tempNode.addEdge(tempEdge);				// Edge 1
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 8
	tempNode.setOperation("h = f + one");
	tempNode.setNumCycles(1);
	tempNode.setASAP(4);
	tempNode.setListR(6);
	tempEdge.setPrevNode(7);				// Edge 1
	tempEdge.setNextNode(10);
	tempNode.addEdge(tempEdge);

	tempEdge.init();
	tempEdge.setPrevNode(7);				// Edge 2
	tempEdge.setNextNode(11);
	tempNode.addEdge(tempEdge);
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 9
	tempNode.setOperation("g = d + e");
	tempNode.setNumCycles(1);
	tempNode.setASAP(5);
	tempNode.setListR(7);
	tempEdge.setPrevNode(8);
	tempNode.addEdge(tempEdge);				// Edge 1
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 10
	tempNode.setOperation("h = f + e");
	tempNode.setNumCycles(1);
	tempNode.setASAP(5);
	tempNode.setListR(6);
	tempEdge.setPrevNode(9);
	tempEdge.setNextNode(10);
	tempNode.addEdge(tempEdge);				// Edge 1

	tempEdge.init();
	tempEdge.setPrevNode(9);
	tempEdge.setNextNode(11);
	tempNode.addEdge(tempEdge);				// Edge 1

	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 11
	tempNode.setOperation("x = h << one");
	tempNode.setNumCycles(1);
	tempNode.setASAP(6);
	tempNode.setListR(7);
	tempEdge.setPrevNode(10);
	tempNode.addEdge(tempEdge);				// Edge 1
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();

	// Node 12
	tempNode.setOperation("z = h >> one");
	tempNode.setNumCycles(1);
	tempNode.setASAP(6);
	tempNode.setListR(7);
	tempEdge.setPrevNode(11);
	tempNode.addEdge(tempEdge);				// Edge 1
	graph.addNode(tempNode);

	// Init nodes.
	tempNode.init();
	tempEdge.init();
}

void setLatHLS4(Nodes tempNode, Edges tempEdge, Graph & graph) {

}
*/