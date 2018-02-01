/**********************************************************************************
* File Name	: Hash_Table.h
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0  Rohit				11/15/2017 					Created
***********************************************************************************/
#ifndef HASH_TABLE
#define HASH_TABLE

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
* Structure Definition
******************************************************************/
typedef struct
{
	char  *value;
	int	  flag;
	int   numCollisions;
}HashNode;

/*****************************************************************
* Class Definition
******************************************************************/
class HashTable
{
	int tableSize;
	int	numElements;
	HashNode *hashNode;

public:

	//Constructor
	HashTable();

	//Function to check loadFactor
	float CheckLoadFactor();

	//Insert elements into the hash table
	void InsertElement(char *userString);

	//Delete element from table
	void DeleteElement(char *userString);

	//Display all the elements in the table
	void DisplayTable();

	//Search element
	long SearchElement(char *userString);


};


/*****************************************************************
* Function Declaration
******************************************************************/

/***************************************************************************
* Function Name : R_Sleep
****************************************************************************/
void R_Sleep(unsigned long seconds);

/***************************************************************************
* Function Name : HashFunction
****************************************************************************/
unsigned long HashFunction(unsigned char *str);

/***************************************************************************
* Function Name : FindNextPrimeNumber
****************************************************************************/
int FindNextPrimeNumber(int doubleTableSize);

#endif

