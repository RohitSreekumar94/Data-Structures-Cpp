/**********************************************************************************
* File Name	: Graphs_BFS.h
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0  Rohit				10/28/2017 					Created
***********************************************************************************/
#include "Graphs_BFS.h"


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
void GRAPH::ViewGraphAdjMatrix()
{

	cout << "\n";

	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			cout << adj_Matrix[i][j] << " ";
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
	int **matrix	 = NULL;
	bool *check		 = NULL;
	list <int> BFS_Queue;
	
	if (!strcmp(matrixType, "Normal"))
	{
		matrix = adj_Matrix;
	}
	else if (!strcmp(matrixType, "Transpose"))
	{
		matrix = transposeMatrix;
	}

	//Iterator used to traverse throught the list
	//list <int> ::iterator iter;

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

	delete[] check;
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

/***********************************************************************************
* Function Name : main
* Description   :
************************************************************************************/
int main()
{
	int		numNodes			= 0;
	int		option				= 0;
	char	userOption			= 0;
	int		sourceVertex		= 0;
	int		destVertex			= 0;
	int		startNode			= 0;
	GRAPH	*graph				= NULL;
	int		numElements_BFS		= 0;
	int		numElements_rev_BFS = 0;
	char	matrixType[256]		= { 0 };
	int		subOption			= 0;

	do
	{
		cout << "\n************* Graph Operations Menu ********************\n\n";
		cout << "1. Create Graph\n";
		cout << "2. View Adjacent Matrix\n";
		cout << "3. View Graph BFS traversal\n";
		cout << "4. Quit program\n";
		cout << "Enter your option(1 - 4) : ";
		cin  >> option;

		cout << "\n";
		switch (option)
		{
		case 1:

			
				cout << "\n************** Graph Creation Menu *************************\n\n";
				cout << "1. Use built in Graph\n";
				cout << "2. Manual Graph Creation\n";
				cout << "Enter your option(1 - 2) : ";
				cin >> subOption;
				cout << "\n";
				
				switch (subOption)
				{

				case 1:

					//Allocating memory for the object
					graph = new GRAPH(11);

					graph->insertEdge(0,1);
					graph->insertEdge(1,2);
					graph->insertEdge(2,0);
					graph->insertEdge(1,4);
					graph->insertEdge(2,4);
					graph->insertEdge(4,5);
					graph->insertEdge(2,3);
					graph->insertEdge(4,8);
					graph->insertEdge(3,8);
					graph->insertEdge(5,1);
					graph->insertEdge(8,9);
					graph->insertEdge(9,3);
					graph->insertEdge(9,10);
					graph->insertEdge(10,7);
					graph->insertEdge(8,7);
					graph->insertEdge(7,5);
					graph->insertEdge(5,7);
					graph->insertEdge(5,6);
					graph->insertEdge(6,7);
					
					//Function to update the tranpose matrix
					graph->UpdateTransposeMatrix();
					break;

				case 2:

					//Creating a graph object with numNodes number of instances.
					cout << "\nEnter number of nodes:";
					cin >> numNodes;

					//Allocating memory for the object
					graph = new GRAPH(numNodes);

					cout << "\nCreate graph connections";
					cout << "\n------------------------";

					do
					{
						cout << "\nEnter source Vertex(0 - " << numNodes - 1 << "): ";
						cin >> sourceVertex;
						if (sourceVertex < 0 || sourceVertex > numNodes - 1)
						{
							cout << "\nInvalid connection source vertex. Please enter a value between (0 - " << numNodes - 1 << ")";
							continue;
						}

						cout << "\nEnter destination Vertex(0 - " << numNodes - 1 << "): ";
						cin >> destVertex;
						if (destVertex < 0 || destVertex > numNodes - 1)
						{
							cout << "\nInvalid connection destination vertex. Please enter a value between (0 - " << numNodes - 1 << ")";
							continue;
						}

						graph->insertEdge(sourceVertex, destVertex);

						cout << "\n\nDo you want to add more connections(Y/N)";
						cin >> userOption;

					} while (userOption == 'Y' || userOption == 'y');

					//Function to update the tranpose matrix
					graph->UpdateTransposeMatrix();
					break;

				default : cout << "\nInvalid option.Please provide a value in the range (1-2)";

				}

				break;
		case 2:
			cout << "\nAdjacent Matrix";
			cout << "\n----------------";
			graph->ViewGraphAdjMatrix();
			
			break;

		case 3:

			cout << "\nEnter start node for BFS traversal:";
			cin >> startNode;

			strcpy(matrixType, "Normal");
			
			//Displaying the linked list
			cout << "\nThe Graph: ";
			numElements_BFS = graph->graph_BFS(startNode,matrixType);

			break;

		case 4:
			//Exit the program
			cout << "Exiting program. Goodbye :-)";
			R_Sleep(2);
			exit(0);
			break;

		default:
			cout << "\nInvalid option.Please provide a value in the range (1-3)";
		}
	} while (TRUE);
	

    return 0;
}

