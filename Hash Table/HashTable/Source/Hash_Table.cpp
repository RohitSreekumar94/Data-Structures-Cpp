/****************************************************************
* File Name	: Hash_Table.c
* Contents	:
*
* Rev  Name			        Date				        Description
* ==============================================================
* 1.00 			Rohit		11/15/2017    					Created
****************************************************************/

#include "Hash_Table.h"

/*****************************************************************
* Global Variables
******************************************************************/

/***************************************************************************
* Class public Function Name : HashTable
* Description				 : Constructor
****************************************************************************/
HashTable :: HashTable()
{
	tableSize = 1;
	numElements = 0;

	//Allocate memory for hash node
	hashNode = (HashNode *)calloc(tableSize, sizeof(HashNode));

	/*for (int i = 0; i < tableSize; i++)
	{
		memset(hashNode[i].value, 0, 10);
	}*/
}

/*****************************************************************************************************
* Class public Function Name : CheckLoadFactor
* Description				 : Function to check wheather the load factor is greater than 0.5 or not
******************************************************************************************************/
float HashTable :: CheckLoadFactor()
{
	return ((float)numElements / tableSize);
}

/***************************************************************************
* Class public Function Name : InsertElement
* Description				 : Function to insert element into the table
****************************************************************************/
void HashTable::InsertElement(char *userString)
{
	unsigned long	hashIndex    = 0;
	int				collisions   = 0;
	HashNode		*temp		 = NULL;
	HashNode		*newHashNode = NULL;
	int				oldTableSize = 0;

	//Increment the number of elements
	++numElements;

	if (CheckLoadFactor() > 0.5)
	{
		cout << "\n";
		cout << "\nLoad Factor: " << CheckLoadFactor();
		cout << "\nPresent Table Size : " << tableSize;
		oldTableSize = tableSize;

		//Allocate memory for temp hash node
		temp = (HashNode *)calloc(tableSize, sizeof(HashNode));

		//Copy the hashNode into the temp variable
		memcpy(temp, hashNode, tableSize * sizeof(HashNode));

		//Resize the table to a size double the present size to its nearest prime number
		tableSize = FindNextPrimeNumber(tableSize * 2);
		cout << "\nNew Table Size : " << tableSize << "\n";

		//Reallocating the memory with the new size
		newHashNode = (HashNode *)realloc(hashNode, tableSize * sizeof(HashNode));
		if (newHashNode != NULL)
		{
			hashNode = newHashNode;
		}
		else
		{
			cout << "\n\nError... Realloc failed";
			return;
		}
		
		//Initializing the values for the new memory
		for (int i = 0; i < tableSize; i++)
		{
			hashNode[i].flag = 0;
			hashNode[i].numCollisions = 0;
			hashNode[i].value = NULL;
		}

		////Copying the temp to the hashNode with new memory
		//memcpy(hashNode, temp, oldTableSize * sizeof(HashNode));
	}

	//Rehashing
	for (int i = 0; i < oldTableSize; i++)
	{
		if (temp[i].value != NULL)
		{
			//Hash Function
			hashIndex = HashFunction((unsigned char *)temp[i].value) % tableSize;

			//Find the next available slot
			while (hashNode[hashIndex].flag != 1 && hashNode[hashIndex].value != NULL)
			{
				hashIndex++;
				collisions++;
				hashIndex = hashIndex % tableSize;
			}

			//Allocating memory
			hashNode[hashIndex].value = (char *)calloc(strlen(temp[i].value) + 1, sizeof(char));

			//Copying the string into the free slot in the hash table
			strcpy(hashNode[hashIndex].value, temp[i].value);

			//Updating the number of collisions for this string
			hashNode[hashIndex].numCollisions = collisions;
		}
	}

	//Hash Function
	hashIndex = HashFunction((unsigned char *)userString) % tableSize;

	//Find the next available slot
	while (hashNode[hashIndex].flag != 1 && hashNode[hashIndex].value != NULL)
	{
		hashIndex++;
		collisions++;
		hashIndex = hashIndex % tableSize;
	}

	//Allocating memory
	hashNode[hashIndex].value = (char *)calloc(strlen(userString) + 1, sizeof(char));

	//Copying the string into the free slot in the hash table
	strcpy(hashNode[hashIndex].value,userString);

	//Updating the number of collisions for this string
	hashNode[hashIndex].numCollisions = collisions;

	cout << "\nString name : " << userString << "\t Number of collisions: " << hashNode[hashIndex].numCollisions;
}

/***************************************************************************
* Class public Function Name : DeleteElement
* Description				 : Function to delete an element from the table
****************************************************************************/
void HashTable::DeleteElement(char *userString)
{
	unsigned long hashIndex = 0;
	int collisions = 0;

	//Hash Function
	hashIndex = HashFunction((unsigned char *)userString) % tableSize;

	while (hashIndex < (unsigned int)tableSize)
	{
		if (hashNode[hashIndex].value != NULL)
		{
			if (!strcmp(hashNode[hashIndex].value, userString) && hashNode[hashIndex].flag == 0)
			{
				//Flag is set to 1 to denote the element is deleted
				hashNode[hashIndex].flag = 1;
				free(hashNode[hashIndex].value);
				hashNode[hashIndex].value = NULL;
				cout << "\nString : " << userString << " deleted";
				return;
			}
			else
			{
				hashIndex++;
			}
		}
		else
		{
			cout << "\nError. Given element to be deleted is not found in the table";
			return;
		}
	}
}

/*******************************************************************************
* Class public Function Name : SearchElement
* Description				 : Function to search for an element in the table
********************************************************************************/
long HashTable::SearchElement(char *userString)
{
	unsigned long hashIndex = 0;
	int collisions = 0;

	//Hash Function
	hashIndex = HashFunction((unsigned char *)userString) % tableSize;

	while (hashIndex < (unsigned int)tableSize)
	{
		if (hashNode[hashIndex].value != NULL)
		{
			if (!strcmp(hashNode[hashIndex].value, userString) && hashNode[hashIndex].flag == 0)
			{
				//Flag is set to 1 to denote the element is deleted
				cout << "\nThe given string is found at index : " << hashIndex;
				return hashIndex;
			}
			else
			{
				hashIndex++;
			}
		}
		else
		{
			cout << "\nError.... Search for string : " << userString << " failed.";
			return -1;
		}
	}

	cout << "\nError.... Search for string : " << userString << " failed.";
	return -1;
}

/****************************************************************************
* Class public Function Name : DisplayTable
* Description				 : Function to display all elements in the table
*****************************************************************************/
void HashTable::DisplayTable()
{
	unsigned long hashIndex = 0;
	int collisions = 0;

	while (hashIndex != tableSize)
	{
		if (hashNode[hashIndex].flag != 1 && hashNode[hashIndex].value != NULL)
		{
			cout << "\n" << hashNode[hashIndex].value;
		}

		hashIndex++;
	}
}

/***************************************************************************
* Function Name : FindNextPrimeNumber
* Description   : Function to get the next prime number
****************************************************************************/
int FindNextPrimeNumber(int doubleTableSize)
{
	int flag = 1;

	while (flag == 1)
	{
		for (int i = 2; i <= doubleTableSize/2 ; i++)
		{
			if (doubleTableSize % i == 0)
			{
				flag = 0;
				break;
			}
		}

		if (flag == 0)
		{
			doubleTableSize++;
			flag = 1;
		}
		else
		{
			break;
		}
	}

	return doubleTableSize;
}

/***************************************************************************
* Function Name : HashFunction
* Description   : Hash function for strings
****************************************************************************/
unsigned long HashFunction(unsigned char *str)
{
	unsigned long hash  = 5381;
	int			  c		= 0;

	while (c = *str++)
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
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

/***************************************************************************
* Function Name : main
* Description   : 
****************************************************************************/
int main()
{
	HashTable *hashTable = NULL;
	int searchElementIndex = 0;

	hashTable = new HashTable();

	cout << "\n\nInsert Operation";
	cout << "\n-------------------";

	//Inserting the elements
	hashTable->InsertElement("Apple");
	hashTable->InsertElement("Oranges");
	hashTable->InsertElement("Pineapples");
	hashTable->InsertElement("Jackfruit");
	hashTable->InsertElement("Kiwis");
	hashTable->InsertElement("Watermelon");
	hashTable->InsertElement("Apricot");
	hashTable->InsertElement("Cherries");
	hashTable->InsertElement("Papaya");
	hashTable->InsertElement("Lemon");
	hashTable->InsertElement("Pomelos");
	hashTable->InsertElement("Mangoes");
	hashTable->InsertElement("Grapes");
	hashTable->InsertElement("Peach");
	hashTable->InsertElement("Berries");

	cout << "\n\nDisplay Operation";
	cout << "\n-------------------";
	
	//Display the hash table
	hashTable->DisplayTable();

	cout << "\n\nSearch Operation";
	cout << "\n-------------------";

	cout << "\n\nSearch for string: Grapes";

	//Search Element in hash Table
	searchElementIndex = hashTable->SearchElement("Grapes");

	cout << "\n\nSearch Operation";
	cout << "\n-------------------";

	cout << "\n\nSearch for string: NotThereInHash";
	
	//Search Element in hash Table
	searchElementIndex = hashTable->SearchElement("NotThereInHash");

	cout << "\n\nDisplay Operation";
	cout << "\n-------------------";
	
	//Display the hash table
	hashTable->DisplayTable();

	cout << "\n\nDelete Operation";
	cout << "\n-------------------";
	
	//Deleting the elements
	hashTable->DeleteElement("Grapes");
    
	cout << "\n\nSearch Operation";
	cout << "\n-------------------";

	cout << "\n\nSearch for string: Grapes";

	//Search Element in hash Table
	searchElementIndex = hashTable->SearchElement("Grapes");

	cout << "\n\nDisplay Operation";
	cout << "\n-------------------";
	
	//Display the hash table
	hashTable->DisplayTable();

	

	while (1)
	{
		R_Sleep(1);
	}

	return 0;
}

