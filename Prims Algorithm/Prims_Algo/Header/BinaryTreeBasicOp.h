/**********************************************************************************
* File Name	: BinaryTreeBasicOp.h
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0 			Rohit		9/27/2017    					Created
***********************************************************************************/
#ifndef BINARY_TREE_BASIC_OP
#define BINARY_TREE_BASIC_OP

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
* Enumeration Definition
******************************************************************/
typedef enum
{
	INVALID =  -1,
	LEFT	=   0,
	RIGHT	=   1
}SIDE;

/*****************************************************************
* Structure Definition
******************************************************************/
typedef struct TREE
{
	int value;
	/*int height;
	int depth;*/
	struct TREE *L_Child;
	struct TREE *R_Child;
	struct TREE *Parent;

}TREE;

/*****************************************************************
* Function Declaration
******************************************************************/

/************************************************************************
* Function Name : InsertBinarySearchTreeElement
************************************************************************/
void InsertBinarySearchTreeElement(TREE **rootNode, TREE **searchNode, int elementToBeInserted, SIDE side);

/***********************************************************************************
* Function Name : CreateBinarySearchTree
************************************************************************************/
void CreateBinarySearchTree(TREE **rootNode, int numElements);

/***********************************************************************************
* Function Name : InitializeNodeDepth
************************************************************************************/
void InitializeNodeDepth(TREE **node);

/***********************************************************************************
* Function Name : SearchTree
************************************************************************************/
TREE *SearchTree(TREE *node, int searchVal);

/***********************************************************************************
* Function Name : DeleteNodeFromTree
************************************************************************************/
void DeleteNodeFromTree(TREE *node, TREE *foundNode);

/***********************************************************************************
* Function Name : LocatePredecessor
************************************************************************************/
TREE *LocatePredecessor(TREE *node);

/***********************************************************************************
* Function Name : LocateSuccessor
************************************************************************************/
TREE *LocateSuccessor(TREE *node);

/***************************************************************************
* Function Name : Swap
****************************************************************************/
void Swap(TREE *node1, TREE *node2);

/************************************************************************************
* Function Name : InOrderDisplayTree
************************************************************************************/
void InOrderDisplayTree(TREE *node);

#endif
