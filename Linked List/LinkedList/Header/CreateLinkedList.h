/****************************************************************
* File Name	: CreateLinkedList.h
* Contents	:
*
* Rev  Name			        Date				        Description
* ==============================================================
* 1.00 			Rohit		8/31/2017    					Created
****************************************************************/
#ifndef CREATE_LINKED_LIST
#define CREATE_LINKED_LIST

#include<iostream>
#include<stdlib.h>

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
* Structure Definition
******************************************************************/
typedef struct NODE
{
	int value;
	struct NODE *next;

}NODE;


/*****************************************************************
* Function Declaration
******************************************************************/

/***************************************************************************
* Function Name : CreateLinkedList
****************************************************************************/
void CreateLinkedList(NODE **node,int numNodes);

/***************************************************************************
* Function Name : Display
****************************************************************************/
void Display(NODE *node);

/***************************************************************************
* Function Name : DeleteLinkedList
****************************************************************************/
void DeleteLinkedList(NODE *head, NODE *nodeToBeDeleted);

/***************************************************************************
* Function Name : AddNode
****************************************************************************/
int AddNode(NODE *head, int valueToBeAdded);

/***************************************************************************
* Function Name : LinkedListBasicOp
****************************************************************************/
void LinkedListBasicOp(NODE  **headNode);

/***************************************************************************
* Function Name : R_Sleep
****************************************************************************/
void R_Sleep(unsigned long seconds);


#endif

