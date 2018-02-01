/**********************************************************************************
* File Name	: Graphs_BFS_1.h
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0  Rohit				10/28/2017 					Created
***********************************************************************************/
#ifndef GRAPHS_BFS
#define GRAPHS_BFS

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<list>
#include<string.h>

#ifdef WIN32
#include<Windows.h>

#else
#include<unistd.h>
#endif

using namespace std;

#ifndef WIN32
#define TRUE 1
#define FALSE 0
#endif


/*****************************************************************
* Class Definition
******************************************************************/
class GRAPH
{
private:

	//numVertex represents the number of vertices
	int numVertex;

	//Queue for adjacency list
	//list <int> * adj_Vertex;
	int **adj_Matrix;
	int **transposeMatrix;
public:
	//Constructor
	GRAPH(int numVertex);

	//Function to insert an edge to the graph between two vertices
	void insertEdge(int sourceVertex, int destVertex);

	//Function to view graph adjacency matrix
	void ViewGraphAdjMatrix(char* matrixType);

	//Function to print the graphs values by traversing via BFS
	int graph_BFS(int startVertex, char *matrixType);

	//Function to update the tranposeMatrix with tranpose of the adjacent matrix
	void UpdateTransposeMatrix();

	//Destructor
	~GRAPH();
};

/*****************************************************************
* Function Declaration
******************************************************************/
void R_Sleep(unsigned long seconds);
#endif
