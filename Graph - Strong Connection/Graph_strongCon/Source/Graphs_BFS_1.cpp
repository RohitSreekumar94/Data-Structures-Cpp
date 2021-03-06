/**********************************************************************************
* File Name	: Graphs_BFS_1.h
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0  Rohit				10/28/2017 					Created
***********************************************************************************/
#include "Graphs_BFS_1.h"


/******************************************************************************************
* Class Public Function Name : Constructor
* Description				 : Initializing the private variable
*******************************************************************************************/
GRAPH::GRAPH(int numNodes)
{
	this->numVertex = numNodes;

	//Allocating memory for the queue
	//adj_Vertex = new list <int>[numVertex];

	//Allocating memory for the matrix

	adj_Matrix = (int **)calloc(numNodes, sizeof(int));

	for (int i = 0; i < numNodes; i++)
	{
		adj_Matrix[i] = (int *)calloc(numNodes, sizeof(int));
	}
}

/******************************************************************************************
* Class Public Function Name : Desstructor
* Description				 : 
*******************************************************************************************/
GRAPH::~GRAPH()
{
	for (int i = 0 ; i < numVertex; i++)
	{
		free(adj_Matrix[i]);
	}

	free(adj_Matrix);
}

/*******************************************************************************************
* Class Public Function Name : insertEdge
* Description				 : Function to insert an edge to the graph between two vertices
********************************************************************************************/
void GRAPH :: insertEdge(int sourceVertex, int destVertex)
{
	//Adding element to the end of queue
	//Here the dest vertex is added to the list of sourceVertex
	//adj_Vertex[sourceVertex].push_back(destVertex);
	adj_Matrix[sourceVertex][destVertex] = 1;
}

/*******************************************************************************************
* Class Public Function Name : ViewGraphAdjMatrix
* Description				 : Function to view the graph adjacency matrix
********************************************************************************************/
void GRAPH::ViewGraphAdjMatrix(char* matrixType)
{
	int ** matrix = NULL;

	if (!strcmp(matrixType, "Normal"))
	{
		matrix = adj_Matrix;
	}
	else
	{
		matrix = transposeMatrix;
	}

	cout << "\n";

	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			cout << matrix[i][j] << " ";
		}

		cout << "\n";
	}
}

/*******************************************************************************************
* Class Public Function Name : graph_BFS
* Description				 : Function to print the graphs values by traversing via BFS
********************************************************************************************/
int GRAPH::graph_BFS(int startVertex,char *matrixType)
{
	int	 temp		 = 0;
	int  value		 = 0;
	int  numElements = 0;
	bool *check		 = NULL;
	int **matrix	 = NULL;
	list <int> BFS_Queue;
	
	if (!strcmp(matrixType, "Normal"))
	{
		matrix = adj_Matrix;
	}
	else if (!strcmp(matrixType, "Transpose"))
	{
		matrix = transposeMatrix;
	}

	//Creating a queue to check wheather the nodes have been visited or not
	check = new bool[numVertex];

	//Updating the check queue's to FALSE indicating the node has not been visited
	for (int i = 0; i < numVertex; i++)
	{
		check[i] = FALSE;
	}

	//Setting the startVertex has visited and enqueing it to the BFS_Queue
	check[startVertex] = TRUE;

	//Enqueing the startVertex to the end of the list in this case the list is empty so the first element
	BFS_Queue.push_back(startVertex);

	while (!BFS_Queue.empty())
	{
		//Get element in front of the queue
		temp = BFS_Queue.front();
		
		if (strcmp(matrixType, "Transpose"))
		{
			cout << temp << " ";
		}
		++numElements;

		//Pop the front element from the queue
		BFS_Queue.pop_front();

		for (int i = 0 ; i < numVertex ; i++)
		{
			if (1 == matrix[temp][i])
			{
				if (FALSE == check[i])
				{
					check[i] = TRUE;
					BFS_Queue.push_back(i);
				}
			}
		}
	}

	delete [] check;
	return numElements;
}

/***********************************************************************************************************
* Class Public Function Name : UpdateTransposeMatrix
* Description				 : Function to update the tranposeMatrix with tranpose of the adjacent matrix
************************************************************************************************************/
void GRAPH :: UpdateTransposeMatrix()
{
	//Allocating memory for the transpose matrix
	transposeMatrix = (int **)calloc(numVertex, sizeof(int));

	for (int i = 0; i < numVertex; i++)
	{
		transposeMatrix[i] = (int *)calloc(numVertex, sizeof(int));
	}


	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			transposeMatrix[j][i] = adj_Matrix[i][j];
		}
	}
}

/***************************************************************************
* Function Name : R_Sleep
* Description   : Function to pause execution for specified amount of time
****************************************************************************/
void R_Sleep(unsigned long seconds)
{
#ifdef WIN32
	Sleep(seconds * 1000);
#else
	sleep(seconds);
#endif

}



