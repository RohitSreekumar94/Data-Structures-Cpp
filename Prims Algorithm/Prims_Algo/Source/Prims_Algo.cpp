/**********************************************************************************
* File Name	: Prims_Algo.cpp
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0  Rohit				11/10/2017 					Created
***********************************************************************************/
#include "Prims_algo.h"
#include "BinaryTreeBasicOp.h"


/******************************************************************************************
* Class Public Function Name : Constructor
* Description				 : Initializing the private variable
*******************************************************************************************/
GRAPH::GRAPH(int numNodes)
{
	this->numVertex = numNodes;

	//Allocating memory for the matrix

	adj_Vertex = new list <pair <int,int> >[numNodes];
}

/******************************************************************************************
* Class Public Function Name : Desstructor
* Description				 :
*******************************************************************************************/
//GRAPH::~GRAPH()
//{
//	delete[] adj_Vertex;
//}

/*******************************************************************************************
* Class Public Function Name : insertEdge
* Description				 : Function to insert an edge to the graph between two vertices
********************************************************************************************/
void GRAPH::insertEdge(int sourceVertex, int destVertex, int weight)
{
	//Creating an edge between source and destination and assigning a weight to the graph
	if (sourceVertex >= 65 && destVertex >= 65)
	{
		adj_Vertex[sourceVertex - 65].push_back(make_pair(destVertex - 65, weight));
		adj_Vertex[destVertex - 65].push_back(make_pair(sourceVertex - 65, weight));
	}
	else
	{
		if (sourceVertex < numVertex && destVertex < numVertex)
		{
			adj_Vertex[sourceVertex].push_back(make_pair(destVertex, weight));
			adj_Vertex[destVertex].push_back(make_pair(sourceVertex, weight));
		}
		else
		{
			cout << "\nError. Invalid source/destination vertex";
		}
	}
	
}

/**********************************************************************************************
* Class Public Function Name : MST_Prims
* Description				 : Function to create Minimum Spanning Tree using Prim's algorithm
***********************************************************************************************/
void GRAPH :: MST_Prims()
{
	int sourceVertex = 3;
	char table[26][2] = { 0 };

	//Creating a min heap
	priority_queue < pair <int, int>, vector < pair <int, int> >, greater < pair<int, int> > > minHeap;
	list < pair <int, int> > ::iterator i;

	int heap_Root = 0;

	int edge_Weight[100] = { 0 };

	//The parent represents the final Minimum spanning tree
	char *parent	= NULL;

	//List to check wheather a node has been visited or not
	bool check_Trav_MST[100] = { 0 };

	//Allocating memory for parent
	parent	= (char *)calloc(1, numVertex);

	//Initializing the variables with max and min values of int respectively
	for (int j = 0; j < numVertex; j++)
	{
		edge_Weight[j] = INT_MAX;
	}


	//Inserting souce vertex into min heap - here the edge weight is 0 and source vertex is 3
	minHeap.push(make_pair(0, sourceVertex));
	edge_Weight[sourceVertex] = 0;

	//Loop till heap is empty
	while (!minHeap.empty())
	{
		//Here we use second since first is representative of the edge weight and here we are extracting the node.
		heap_Root = minHeap.top().second;
		
		//Deleting the root from the heap
		minHeap.pop();

		//Updating the array of trav elements
		check_Trav_MST[heap_Root] = TRUE;

		for (i = adj_Vertex[heap_Root].begin(); i != adj_Vertex[heap_Root].end(); i++)
		{
			//Obtain the node
			int currentNode = (*i).first;

			//Obtain the current node edge weight
			int currentEdgeWeight = (*i).second;
			
			//If the current node hasnt been visited before and it has a weight less the edge_weight then go inside the if condition
			if (check_Trav_MST[currentNode] == FALSE && currentEdgeWeight < edge_Weight[currentNode])
			{
				edge_Weight[currentNode] = currentEdgeWeight;
				minHeap.push(make_pair(currentEdgeWeight, currentNode));

				//Updating the parent 
				*(parent + currentNode) = (char)heap_Root;
				
			}
		}
	}

	*(parent + sourceVertex) = -1;

	cout << "\n The Minimum Spanning Tree: ";

	//Displaying the Minimum spanning tree
	for (int i = 0; i < numVertex; i++)
	{
		table[i][0] = toAlpha_R(i + 65);
		if (parent[i] == -1)
		{
			table[i][1] = -1;
		}
		else
		{
			table[i][1] = toAlpha_R(parent[i] + 65);
		}
	}
	
	//Function to create tree from list obtained
	CreateTreeFromList(table,numVertex);

	free(parent);

}

/***************************************************************************
* Function Name : FindChildrenFromList
* Description   : Function to find child nodes for the given parent
****************************************************************************/
void FindChildrenFromList(char table[][2],int rows,char parent, char *children)
{
	int i = 0;
	int j = 0;

	for(i = 0, j = 0 ; i < rows ; i++)
	{
		if (table[i][1] == parent)
		{
			children[j] = table[i][0];
			j++;
		}
	}
}

/***************************************************************************
* Function Name : CreateTreeFromList
* Description   : Function to create tree from the given table
****************************************************************************/
void CreateTreeFromList(char table[][2],int rows)
{
	TREE	*rootNode			= NULL;
	TREE	*parentNode			= NULL;
	char	children[26]		= { 0 };
	int		temp				= 0;
	int		num_Children		= 0;
	int		lastInsertedNode	= 0;
	list <char>	lastInsertedQueue;

	

	while (temp < rows)
	{
		if (table[temp][1] == -1)
		{
			//Insertion of root
			InsertBinarySearchTreeElement(&rootNode,NULL,table[temp][0],INVALID);
			lastInsertedQueue.push_back(table[temp][0]);
			break;
		}

		++temp;
	}
	
	while (!lastInsertedQueue.empty())
	{
		//Taking the first element in the queue and stroing it in the variable
		lastInsertedNode = lastInsertedQueue.front();

		//Popping the first element out of the queue.
		lastInsertedQueue.pop_front();

		//Function to find children 
		FindChildrenFromList(table,rows,lastInsertedNode,children);
		num_Children = strlen(children);

		//Searching for the node corresponding to the given value
		parentNode = SearchTree(rootNode, lastInsertedNode);

		while (num_Children > 0)
		{
			//Here we make use of this % 2 if condition to make a very simplified form of balanced tree approximation.
			if (num_Children % 2 == 0)
			{
				//Inserting element to the right side of the node
				InsertBinarySearchTreeElement(&rootNode,&parentNode,children[num_Children - 1], RIGHT);

				//Enqueing the lastinserted element into the queue
				lastInsertedQueue.push_back(children[num_Children - 1]);
			}
			else
			{
				//Inserting element to the left side of the node
				InsertBinarySearchTreeElement(&rootNode,&parentNode,children[num_Children - 1], LEFT);

				//Enqueing the lastinserted element into the queue
				lastInsertedQueue.push_back(children[num_Children - 1]);
			}

			--num_Children;
		}

		//Clearing the string 'children' and filling it with all zeroes.
		memset(children, 0, strlen(children));
	}

	//Displaying the tree
	cout << " ";
	InOrderDisplayTree(rootNode);
}

/***************************************************************************
* Function Name : toAlpha_R
* Description   : Function to get alphabet from ascii number
****************************************************************************/
char toAlpha_R(int n)
{
	n = n - 64;
	if(n >= 1 && n <= 26)
	{
		return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[n - 1];
	}
	else
	{
		return -1;
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

/***********************************************************************************
* Function Name : CreateNewGraph
* Description   : Function to create new graph
************************************************************************************/
void CreateNewGraph(GRAPH **graph)
{
	int		numNodes			= 10;
	int		option				= 0;
	char	userOption			= 0;
	int		sourceVertex		= 0;
	int		destVertex			= 0;
	int		startNode			= 0;
	int		numElements_BFS		= 0;
	int		numElements_rev_BFS = 0;
	char	matrixType[256]		= { 0 };
	int		subOption			= 0;
	int		user_edgeWt			= 0;
	bool	exit				= FALSE;

	do
	{
		cout << "\n************* Operations Menu ********************\n\n";
		cout << "1. Create Graph\n";
		cout << "2. View Minimum spanning Tree\n";
		cout << "3. Exit Program....\n";
		cout << "Enter your option(1 - 3) : ";
		cin >> option;

		cout << "\n";
		switch (option)
		{
		case 1:

			//Allocating memory for the object
			(*graph) = new GRAPH(numNodes);
			((*graph))->insertEdge('A', 'H', 4);
			((*graph))->insertEdge('A', 'F', 10);
			((*graph))->insertEdge('A', 'B', 8);
			((*graph))->insertEdge('A', 'I', 11);

			((*graph))->insertEdge('B', 'F', 7);
			((*graph))->insertEdge('B', 'H', 9);
			((*graph))->insertEdge('B', 'A', 8);
			((*graph))->insertEdge('B', 'C', 4);

			((*graph))->insertEdge('C', 'B', 4);
			((*graph))->insertEdge('C', 'D', 3);
			((*graph))->insertEdge('C', 'F', 3);

			((*graph))->insertEdge('D', 'C', 3);
			((*graph))->insertEdge('D', 'F', 18);
			((*graph))->insertEdge('D', 'G', 2);
			((*graph))->insertEdge('D', 'E', 25);

			((*graph))->insertEdge('E', 'D', 25);
			((*graph))->insertEdge('E', 'B', 10);
			((*graph))->insertEdge('E', 'G', 7);
			((*graph))->insertEdge('E', 'F', 2);

			((*graph))->insertEdge('F', 'E', 2);
			((*graph))->insertEdge('F', 'C', 3);
			((*graph))->insertEdge('F', 'B', 7);
			((*graph))->insertEdge('F', 'A', 10);

			((*graph))->insertEdge('G', 'D', 2);
			((*graph))->insertEdge('G', 'E', 7);
			((*graph))->insertEdge('G', 'H', 3);

			((*graph))->insertEdge('H', 'A', 4);
			((*graph))->insertEdge('H', 'G', 3);
			((*graph))->insertEdge('H', 'B', 9);
			((*graph))->insertEdge('H', 'J', 15);

			((*graph))->insertEdge('I', 'J', 12);
			((*graph))->insertEdge('I', 'A', 11);

			((*graph))->insertEdge('J', 'H', 15);
			((*graph))->insertEdge('J', 'I', 12);
				
			break;

		case 2:

			//Function to use prim's algorithhm to get minimum spanning tree
			(*graph)->MST_Prims();
			cout << "\n";
			break;

		case 3:
			//Exit the program
			cout << "Exit Graph Creation..";
			exit = TRUE;
			break;

		default:
			cout << "\nInvalid option.Please provide a value in the range (1-3)";
		}
	} while (exit == FALSE);
}

/***********************************************************************************
* Function Name : main
* Description   : 
************************************************************************************/
int main()
{
	GRAPH *graph = NULL;

	CreateNewGraph(&graph);

	return 0;
}