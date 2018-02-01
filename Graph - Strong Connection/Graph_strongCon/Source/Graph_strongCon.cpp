/**********************************************************************************
* File Name	: Graph_strongCon.cpp
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0  Rohit				10/28/2017 					Created
***********************************************************************************/
#include "Graphs_BFS_1.h"

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
	int		graphType			= 0;

	do
	{
		cout << "\n************* Graph Operations Menu ********************\n\n";
		cout << "1. Create Graph\n";
		cout << "2. View Adjacent Matrix\n";
		cout << "3. Check for strong connection\n";
		cout << "4. Quit program\n";
		cout << "Enter your option(1 - 4) : ";
		cin >> option;

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

				cout << "\n************** Select Graph Type *************************\n";
				cout << "\n1. Strongly Connected Graph";
				cout << "\n2. Weakly Connected graph";
				cout << "\nEnter your option(1 - 2): ";
				cin >> graphType;

				switch (graphType)
				{
				case 1:

					//Allocating memory for the object
					graph = new GRAPH(11);

					graph->insertEdge(0, 1);
					graph->insertEdge(1, 2);
					graph->insertEdge(2, 0);
					graph->insertEdge(1, 4);
					graph->insertEdge(2, 4);
					graph->insertEdge(4, 5);
					graph->insertEdge(2, 3);
					graph->insertEdge(4, 8);
					graph->insertEdge(3, 8);
					graph->insertEdge(5, 1);
					graph->insertEdge(8, 9);
					graph->insertEdge(9, 3);
					graph->insertEdge(9, 10);
					graph->insertEdge(10, 7);
					graph->insertEdge(8, 7);
					graph->insertEdge(7, 5);
					graph->insertEdge(5, 7);
					graph->insertEdge(5, 6);
					graph->insertEdge(6, 7);

					//Function to update the tranpose matrix
					graph->UpdateTransposeMatrix();


					cout << "\nAdjacency matrix";
					cout << "\n-----------------";
					graph->ViewGraphAdjMatrix("Normal");
					break;

				case 2:

					//Allocating memory for the object
					graph = new GRAPH(11);

					graph->insertEdge(0, 1);
					graph->insertEdge(1, 2);
					graph->insertEdge(2, 0);
					graph->insertEdge(1, 4);
					graph->insertEdge(2, 4);
					graph->insertEdge(4, 5);
					graph->insertEdge(2, 3);
					graph->insertEdge(4, 8);
					graph->insertEdge(3, 8);
					graph->insertEdge(5, 1);
					graph->insertEdge(8, 9);
					graph->insertEdge(9, 3);
					graph->insertEdge(9, 10);
					graph->insertEdge(10, 7);
					graph->insertEdge(8, 7);
					graph->insertEdge(5, 7);
					graph->insertEdge(5, 6);
					graph->insertEdge(6, 7);

					//Function to update the tranpose matrix
					graph->UpdateTransposeMatrix();

					cout << "\nAdjacency matrix";
					cout << "\n-----------------";
					graph->ViewGraphAdjMatrix("Normal");
					break;

				default: cout << "\nInvalid option.Please provide a value in the range (1-2)";
				}

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

			default: cout << "\nInvalid option.Please provide a value in the range (1-2)";

			}

			break;
		case 2:
			cout << "\nAdjacent Matrix";
			cout << "\n----------------";
			graph->ViewGraphAdjMatrix("Normal");

			break;

		case 3:

			cout << "\nEnter start node:";
			cin >> startNode;

			strcpy(matrixType, "Normal");

			//Displaying the linked list
			cout << "\nThe Graph: ";
			numElements_BFS = graph->graph_BFS(startNode, matrixType);

			//To check for strong connection we first take the transpose of the adjacent matrix
			strcpy(matrixType, "Transpose");

			numElements_rev_BFS = graph->graph_BFS(startNode, matrixType);
			cout << "\nTranpose of adjacency matrix";
			cout << "\n-----------------------------";
			graph->ViewGraphAdjMatrix("Transpose");

			if (numElements_BFS == numElements_rev_BFS)
			{
				cout << "\nTRUE => The graph is strongly connected";
			}
			else
			{
				cout << "\nFALSE => The graph is not strongly connected";
			}

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