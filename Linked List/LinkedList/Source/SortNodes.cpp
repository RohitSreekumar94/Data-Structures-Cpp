/**********************************************************************************
* File Name	: SortNodes.c
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0 			Rohit		9/5/2017    					Created
* 1.1			Rohit		9/10/2017						Ascend Sort Successful
* 1.2			Rohit		9/11/2017						Descend Sort Successful
***********************************************************************************/
#include "SortNodes.h"

/*****************************************************************
* Global Variables
******************************************************************/
int g_flag = 0;

/*************************************************************************
* Function Name : TraverseLinkedList
* Description   : Function to traverse the linked list and return the node
				  previous to argument 'node'.
**************************************************************************/
NODE* TraverseLinkedList(NODE *head,NODE *node)
{
	if (NULL == head || NULL == node)
	{
		return NULL;
	}
	if (head->next == node)
	{
		return head;
	}
	else
	{
		return TraverseLinkedList(head->next, node);
	}
}

/*************************************************************************
* Function Name : AscendSortNodes
* Description   : Function which creates a linked list and sorts the nodes
				  in ascending order.
**************************************************************************/
void AscendSortNodes(NODE **head)
{
	NODE *node1		= NULL;
	NODE  *tmpHead	= NULL;

	cout << "\nSorting the linked list in ascending order ......\n";

	node1 = *head;

	GetMinNode(node1, &tmpHead);

	*head = tmpHead;
}


/*************************************************************************
* Function Name : DescendSortNodes
* Description   : Function which creates a linked list and sorts the nodes
				  in descending order.
**************************************************************************/
void DescendSortNodes(NODE **head)
{
	NODE *node1		= NULL;
	NODE  *tmpHead	= NULL;

	cout << "\nSorting the linked list in descending order......\n";

	node1 = *head;

	GetMaxNode(node1, &tmpHead);

	*head = tmpHead;
}

/*************************************************************************
* Function Name : Main
* Description   :
**************************************************************************/
//int main()
//{
//	NODE			*head			= NULL;
//	unsigned short  option			= 0;
//	char			userContinue	= 0;
//
//	do
//	{
//		cout << "\n\n***************************************";
//		cout << "\n************* Menu ********************\n";
//		cout << "***************************************\n\n";
//		cout << "1. Generate Linked list\n";
//		cout << "2. Sort Ascending\n";
//		cout << "3. Sort Descending\n";
//		cout << "4. View Linked List\n";
//		cout << "5. Quit program\n";
//		cout << "Enter your option(1 - 5) : ";
//		cin >> option;
//
//		switch (option)
//		{
//		case 1:
//			//Creating the linked list
//			LinkedListBasicOp(&head);
//			break;
//
//		case 2:
//			if (NULL == head)
//			{
//				cout << "\nPlease create Linked List prior to sorting.....\n";
//				break;
//			}
//
//			//Function to sort nodes in ascending order
//			g_flag = 0;
//			AscendSortNodes(&head);
//			cout << "\nSort Successful";
//			break;
//
//		case 3:
//
//			if (NULL == head)
//			{
//				cout << "\nPlease create Linked List prior to sorting.....\n";
//				break;
//			}
//			//Function to sort nodes in descending order
//			g_flag = 0;
//			DescendSortNodes(&head);
//			cout << "\nSort Successful";
//			break;
//
//		case 4:
//			//Function to display the linked list
//			cout << "\nLinked List: ";
//			Display(head);
//			break;
//
//		case 5:
//			cout << "\nAre you sure you want to quit (Y/n) : ";
//			cin >> userContinue;
//
//			if (userContinue == 'Y')
//			{
//				cout << "Exiting Program . Goodbye :-)";
//				R_Sleep(2);
//				exit(0);
//			}
//			break;
//
//		default:
//			cout << "Invalid option.Please provide a value in the range (1-5)";
//		}
//	} while (TRUE);
//
//	return 1;
//}

/*************************************************************************
* Function Name : GetLocalMin
* Description   :
**************************************************************************/
void GetLocalMin(NODE *node2,NODE **min)
{
	if (node2 == NULL)
	{
		return;
	}
	else
	{
		if ((*min)->value > node2->value)
		{
			*min = node2;
		}
		GetLocalMin(node2->next, min);
	}
}

/*************************************************************************
* Function Name : GetLocalMax
* Description   :
**************************************************************************/
void GetLocalMax(NODE *node2, NODE **max)
{
	if (node2 == NULL)
	{
		return;
	}
	else
	{
		if ((*max)->value < node2->value)
		{
			*max = node2;
		}
		GetLocalMax(node2->next, max);
	}
}

/*************************************************************************
* Function Name : GetMinNode
* Description   :
**************************************************************************/
void GetMinNode(NODE *node1, NODE **tmpHead)
{
	NODE *node2		= NULL;
	NODE *min		= NULL;
	NODE *minPrev	= NULL;
	NODE *minAftr	= NULL;
	NODE *temp		= NULL;

	if (NULL == node1)
	{
		return;
	}

	min = node1;
	node2 = node1->next;

	//Function to get local minimum
	GetLocalMin(node2,&min);


	if (NULL != *tmpHead)
	{
		temp = TraverseLinkedList(*tmpHead, node1);
	}

	minPrev = TraverseLinkedList(node1, min); // Function to get prev node of min
	minAftr = min->next; // The node after min
	if (node1->next != NULL)
	{
		// This if condition will fail when there exists only 2 nodes in the sub linked list
		if (min->next != node1->next->next)
		{
			min->next = node1->next; // Linking min to the beginning of the linked list
		}
		else
		{
			/*This is a special case since in the last two nodes with the case where the last node is less than
			the prev node; then min->next will then point to min itself since node1->next points to the last
			node causing an infintie loop. The requirement is to link the min node ( the last node here) to
			the beginning of the sub linked list. In the last sub linked list it is only required to swap the
			last two nodes.*/
			min->next = node1;
		}
	}

	//Swapping node 1 with min; so now the next node of node1 is now the node after min
	node1->next = minAftr;

	if (NULL != minPrev)
	{
		if (minPrev != node1)
		{
			//Making the next node after previous node of min point to node1
			minPrev->next = node1;
		}
	}

	if (0 == g_flag)
	{
		/*This condition is set so as to get the head pointer of the sorted linked list.
		The first min obtained using the selection sort will be smallest in the entire node.
		Hence it will be the head pointer of the sorted linked list*/
		*tmpHead = min;
		g_flag = 1;
	}
	else
	{
		//From the second outer iteration on it is required to link prev nodes to local min
		if (NULL != temp)
		{
			temp->next = min;
		}
	}

#ifdef SL_DEBUG	//Used for debugging the program
	if (NULL != *tmpHead)
	{
		Display(*tmpHead);
		cout << "\n";
	}
#endif
	//Setting the local min as node1 for the sub linked lists
	node1 = min;
	GetMinNode(node1->next, tmpHead);
}

/*************************************************************************
* Function Name : GetMaxNode
* Description   :
**************************************************************************/
void GetMaxNode(NODE *node1, NODE **tmpHead)
{
	NODE *node2		= NULL;
	NODE *max		= NULL;
	NODE *maxPrev	= NULL;
	NODE *maxAftr	= NULL;
	NODE *temp		= NULL;

	if (NULL == node1)
	{
		return;
	}

	max = node1;
	node2 = node1->next;

	//Function to get local maximum
	GetLocalMax(node2, &max);


	if (NULL != *tmpHead)
	{
		temp = TraverseLinkedList(*tmpHead, node1);
	}

	maxPrev = TraverseLinkedList(node1, max); // Function to get prev node of max
	maxAftr = max->next; // The node after max
	if (node1->next != NULL)
	{
		// This if condition will fail when there exists only 2 nodes in the sub linked list
		if (max->next != node1->next->next)
		{
			max->next = node1->next; // Linking max to the beginning of the linked list
		}
		else
		{
			/*This is a special case since in the last two nodes with the case where the last node is less than
			the prev node; then max->next will then point to max itself since node1->next points to the last
			node causing an infintie loop. The requirement is to link the max node ( the last node here) to
			the beginning of the sub linked list. In the last sub linked list it is only required to swap the
			last two nodes.*/
			max->next = node1;
		}
	}

	//Swapping node 1 with max; so now the next node of node1 is now the node after max
	node1->next = maxAftr;

	if (NULL != maxPrev)
	{
		if (maxPrev != node1)
		{
			//Making the next node after previous node of max point to node1
			maxPrev->next = node1;
		}
	}

	if (0 == g_flag)
	{
		/*This condition is set so as to get the head pointer of the sorted linked list.
		The first max obtained using the selection sort will be smallest in the entire node.
		Hence it will be the head pointer of the sorted linked list*/
		*tmpHead = max;
		g_flag = 1;
	}
	else
	{
		//From the second outer iteration on it is required to link prev nodes to local max
		if (NULL != temp)
		{
			temp->next = max;
		}
	}

#ifdef SL_DEBUG	//Used for debugging the program
	if (NULL != *tmpHead)
	{
		Display(*tmpHead);
		cout << "\n";
	}
#endif
	//Setting the local max as node1 for the sub linked lists
	node1 = max;
	GetMaxNode(node1->next, tmpHead);
}
