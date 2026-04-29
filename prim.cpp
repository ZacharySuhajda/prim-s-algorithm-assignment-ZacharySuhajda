#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
using namespace std;


//CLASSES
//--------------------------------------------------------------------------------------------------------
// Edge Class that stores node A and B and a weight between them
class Edge {
	public:
  int nodeA;
	int nodeB;
	int weight;

	// Edge (First Node, Second Node, Weight)
	Edge(int nNodeA, int nNodeB, int nWeight) {
		nodeA = nNodeA;
		nodeB = nNodeB;
		weight = nWeight;
	}

	// Conversion from one edge to another
	Edge(Edge *nEdge) {
		nodeA = nEdge->nodeA;
		nodeB = nEdge->nodeB;
		weight = nEdge->weight;
	}

	// Comparing one edge to another
	int compare(Edge other) {
		bool test1 = nodeA == other.nodeA;
		bool test2 = nodeB == other.nodeB;
		bool test3 = weight == other.weight;
		if (test1 and test2) {
			if (test3) {
				return 0; // They are the same edge
			}
		}
		if (weight < other.weight) {
			return -1; // the other edge is bigger
		}
		return 1; // this edge is bigger
	}
	
	// Prints the edge out
	void printEdge() {
		cout << endl << "Weight: " << weight << endl << nodeA;
		for (int i = 0; i < weight; i++) {
			cout << "-";
		}
		cout << nodeB;
	}
};

//FUNCTIONS
//--------------------------------------------------------------------------------------------------------

//Checkes the visited list for if all nodes have been hit
bool run(bool temp[], int len) {
	for (int i = 0; i < len; i++) {
		if(temp[i]) {
			//cout << "Have visited: " << i <<endl; // Output testing
		}
		else {
			//cout << "Havent visited: " << i <<endl; // Output testing
			return 0;
		}
	}
	//cout << "All Nodes found" << endl;
	return 1;
}

//Prints out the entire graph
void printGraph(vector<vector<Edge>> graph) {
	cout << "Graph Size: " << graph.size() << endl;
	for (int i = 0; i < graph.size(); i++) {
		cout << "\nNode " << i << "\tSize: " << graph[i].size() << endl;
		for (int j = 0; j < graph[i].size(); j++) {
			graph[i][j].printEdge();
		}
		cout << endl;
	}
}

//Checks if edge is in list and returns true if it is in the list
bool inList(vector<Edge> list, Edge edge) {
	for (int i = 0; i < list.size(); i++) {
		bool test1 = list[i].nodeA == edge.nodeA;
		bool test2 = list[i].nodeB == edge.nodeB;
		bool test3 = list[i].weight == edge.weight;
		if (test1 and test2 and test3) {
			return 1;
		}
	}
	return 0;
}

//returns a vector of avalible edges
Edge getMinEdge(vector<Edge> avalibleEdges) {
	Edge temp = new Edge(avalibleEdges[0]);
	//cout << "\n\n///////////////////////////////////////////////////////////";
	for (int i = 0; i < avalibleEdges.size(); i++) {
		//cout << "\n\nMinEdgeInternal:";
		//temp.printEdge();
		if (temp.compare(avalibleEdges[i]) == 1) {
			temp = new Edge(avalibleEdges[i]);
		}
	}
	//cout << "\n\n///////////////////////////////////////////////////////////\n";	
	return temp;
}

//Returns a list of edges for a minimum spanning tree based on prims algorithm
vector<Edge> primmAlgorithm(vector<vector<Edge>> graph, int nodes, int edges) {
	vector<Edge> AvalibleEdges;
	vector<Edge> minTree;
	bool visited[nodes];
	for (int i = 0; i < nodes; i++) { visited[i] = 0;	}
	
	vector<Edge> tempList;
	int curNode = 0;

	for (int j = 0; j < nodes - 1; j++) {
		/*
		cout << "\n\n------------------------------------------------------------------------\nCurNode: " << curNode << endl;
		cout << "Visited = [";
		for (int i = 0; i < nodes; i++) {
			cout << visited[i] << ",";
		}
		cout << "]\n";
		*/

		if (run(visited, nodes)) {
			break;
		}

		visited[curNode] = true;
		
		//adds all edges from node to avalible
		for (int i = 0; i < graph[curNode].size(); i++) {
			if (!inList(AvalibleEdges, graph[curNode][i]) and !inList(minTree, graph[curNode][i])) {
				AvalibleEdges.push_back(graph[curNode][i]);
			}
		}

		/*
		cout << "\nEdges: \n";
		for (int i =  0; i < AvalibleEdges.size(); i++) {
			AvalibleEdges[i].printEdge();
		}
		*/
		
		//gets the minimum edge
		Edge minEdge = new Edge(getMinEdge(AvalibleEdges));
		
		//cout << "\n\nMinEdge:";
		//minEdge.printEdge();
		
		//adds min edge to mintree
		minTree.push_back(minEdge);
		
		//removes used edge from avalible
		for (int i = 0; i < AvalibleEdges.size(); i++) {
			if((AvalibleEdges[i].compare(minEdge) != 0)) {
				tempList.push_back(AvalibleEdges[i]);
			}
		}
		AvalibleEdges = tempList;
		
		/*
		cout << "\n\nEdges Again:";
		for (int i =  0; i < AvalibleEdges.size(); i++) {
			AvalibleEdges[i].printEdge();
		}
		
		cout << "\n\nMin Tree:";
		for (int i =  0; i < minTree.size(); i++) {
			minTree[i].printEdge();
		}
		*/
		
		//sets curNode to the node added by the edge
		if(curNode == minEdge.nodeA) {
			curNode = minEdge.nodeB;
		}
		else {
			curNode = minEdge.nodeA;
		}
	}

	return minTree;
}

//Converts Graph to string
vector<Edge> Graphtotext(vector<vector<Edge>> graph) {
	vector<Edge> newGraph;
	string rtnString = "";
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			//graph[i][j].printEdge();
			if (!inList(newGraph, graph[i][j])) {
				newGraph.push_back(graph[i][j]);
			}
		}
	}
	return newGraph;
}

//MAIN
//--------------------------------------------------------------------------------------------------------

int main() {

	//Variables
	//--------------------------------------------------------------------------------------------------------
  ifstream MyReadFile("C:/Users/suhajdaz3219/Desktop/Algorithms/Prims Algorithm/prim-s-algorithm-assignment-ZacharySuhajda/testdata1.txt");
  string line; // temp string to store lines read from the file
	vector<Edge> edgesList; // List of all the edges in the graph
	int nodes; // Number of nodes
	int edges; // Number of edges

	// Reads in the file and makes it into a list of nodes and list of edges (13-58)
  if (MyReadFile.is_open()) {

		getline(MyReadFile, line); // Gets first line
		nodes = stoi(line); 
		getline(MyReadFile, line); // Skips blank line
		getline(MyReadFile, line);
		edges = stoi(line);

		for (int i = 0; i < edges; i++) {
			getline(MyReadFile, line); // Blank
			getline(MyReadFile, line); // Edge Data
			edgesList.push_back(new Edge(line[0] - 48, line[2] - 48, line[4] - 48)); // - 48 for char to int
		}

    MyReadFile.close();
  }
	else {
    cerr << "Error: Unable to open the file." << endl;
  }

	//Make Graph
	//--------------------------------------------------------------------------------------------------------

	vector<vector<Edge>> Graph;
	for (int i = 0; i < nodes; i++) {
		vector<Edge> temp;
		Graph.push_back(temp);
	}
	for (int i = 0; i < edges; i++) {
		Graph[edgesList[i].nodeA].push_back(edgesList[i]);
		Graph[edgesList[i].nodeB].push_back(edgesList[i]);
	}

	vector<Edge> minTreeList = primmAlgorithm(Graph, nodes, edges);
	
	vector<vector<Edge>> minTree;
	for (int i = 0; i < nodes; i++) {
		vector<Edge> temp;
		minTree.push_back(temp);
	}
	for (int i = 0; i < minTreeList.size(); i++) {
		minTree[minTreeList[i].nodeA].push_back(minTreeList[i]);
		minTree[minTreeList[i].nodeB].push_back(minTreeList[i]);
	}

	//cout << "\n\n//////////////////////////////////////////////////////////////////////\n\n";
	//printGraph(Graph);
	//cout << "\n\n//////////////////////////////////////////////////////////////////////\n\n";
	//printGraph(minTree);

	

	//Testing
	//--------------------------------------------------------------------------------------------------------
	
	Edge test1(0, 4, 5);
	Edge test2(0, 2, 7);
	Edge test3(3, 4, 2);
	Edge test4(1, 2, 8);
	Edge test5(2, 4, 1);
	Edge test6(2, 3, 3);

	vector<Edge> testList = {test1, test2, test3, test4, test5, test6};

  ofstream OutputFile("C:/Users/suhajdaz3219/Desktop/Algorithms/Prims Algorithm/prim-s-algorithm-assignment-ZacharySuhajda/OutPut.txt");
	if (OutputFile.is_open()) {

		vector<Edge> finalGraph = Graphtotext(minTree);
		OutputFile << to_string(nodes) << endl << endl;
		OutputFile << to_string(finalGraph.size());

		for (int i = 0; i < finalGraph.size(); i++) {
			OutputFile << "\n\n" + to_string(finalGraph[i].nodeA) + " " + to_string(finalGraph[i].nodeB) + " " + to_string(finalGraph[i].weight);
		}

		getline(MyReadFile, line); // Skips blank line
		getline(MyReadFile, line);
		edges = stoi(line);

		for (int i = 0; i < edges; i++) {
			getline(MyReadFile, line); // Blank
			getline(MyReadFile, line); // Edge Data
			edgesList.push_back(new Edge(line[0] - 48, line[2] - 48, line[4] - 48)); // - 48 for char to int
		}

    MyReadFile.close();
  }
	else {
    cerr << "Error: Unable to open the file." << endl;
  }

	//End
	//--------------------------------------------------------------------------------------------------------
  
	return 0;
}

/*
Steps
1. Read in data
2. Make into Graph
3. Primms Algorithm
	1. Node = 0
	repeat n - 1 times for min span tree
	2. add nodes edges to avalible
	3. find edge with smallest weight
		from avalible go through and find the one with the smallest weight, then pop
	4. add new edge to minTree
	5. add new node to visited
	6. add new nodes edges to avalible

4. Make Min Tree
5. Print to txt File


*/

/*
Data Format

Node #: n

Edge #: e

Edges:
(Node, Node, Weight)
......
......
......
*/
//Nodes are labeld 0 to n-1