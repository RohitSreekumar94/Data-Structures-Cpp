/**********************************************************************************
* File Name	: Prims_Algo.h
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0  Rohit				11/10/2017 					Created
***********************************************************************************/
#ifndef PRIMS_ALGO
#define PRIMS_ALGO

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<list>
#include<string.h>
#include<limits.h>
#include<utility>
#include<queue>
#include<functional>
#include<algorithm>

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

	//Queue for adjacency list representing both the vertex name and the edge weight
	list < pair <int,int> > * adj_Vertex;

public:
	//Constructor
	GRAPH(int numVertex);
	
	//Function to insert an edge to the graph between two vertices
	void insertEdge(int sourceVertex, int destVertex, int weight);

	//Function to create Minimum Spanning Tree using Prim's algorithm
	void MST_Prims();


	//Destructor
	~GRAPH();
};

/*****************************************************************
* Function Declaration
******************************************************************/

/***************************************************************************
* Function Name : R_Sleep
****************************************************************************/
void R_Sleep(unsigned long seconds);

/***************************************************************************
* Function Name : toAlpha_R
****************************************************************************/
char toAlpha_R(int n);

/***************************************************************************
* Function Name : CreateTreeFromList
****************************************************************************/
void CreateTreeFromList(char table[][2], int rows);

/***************************************************************************
* Function Name : FindChildrenFromList
****************************************************************************/
void FindChildrenFromList(char table[][2], int rows, char parent, char *children);

#endif
