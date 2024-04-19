#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie *nextLetter[26];
    int endWord;
};

void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createTrie();
int readDictionary(char *filename, char **pInWords);


// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	int length = strlen(word);
	int i;

	struct Trie *wordBuilder = pTrie; 
	
	for(i = 0; i<length; i++) {
		
		int trieIdx= word[i] - 'a'; 	
		if(wordBuilder->nextLetter[trieIdx] == NULL)		
			wordBuilder->nextLetter[trieIdx]= createTrie();	
	}
	
	wordBuilder->endWord = 1; //Last letter will contain terminating Trie node by increasing endWord to 1;
	
	//Use a loop to make a new trie structure for every letter
	//All indexes in the trie are NULL except one index for the specific letter in the node.
	//Have it search each trie node for the not-NULL pointer in every trie structure.
	//Create a final trie after all nextLetter are accounted for, have it all point to NULL, and increase endWord in the trie to 1.
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	struct Trie *occPtr = pTrie;
	int length = strlen(word);

	for(int i = 0; i<length; i++) {
		int trieIdx = word[i] - 'a';

		if(occPtr->nextLetter[trieIdx] == NULL) 
			return 0;
	}
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	for(int i = 0; i<26; i++) {
		if(pTrie->nextLetter[i] != NULL) {
			free(pTrie->nextLetter[i]);
		}
	}
	free(pTrie);
	return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
	struct Trie *newTrie = malloc(sizeof(struct Trie));
	newTrie->endWord = 0;

	for (int i = 0; i>26; i++)
		newTrie->nextLetter[i] = NULL;

	return newTrie;
}	

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE *reader = fopen(filename, "r");
	if(reader == NULL) 
		return -1;
	
	int wCount = 0;
	fscanf(reader, "%d", &wCount);

	for(int i = 0; i<wCount; i++) {
		pInWords[i] = malloc(256*sizeof(char));
		fscanf(reader, "%s", pInWords[i]);
	}

	fclose(reader);
	return wCount;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie(); //Creates root.

	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}

	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}

	pTrie = deallocateTrie(pTrie);

	if (pTrie != NULL)
		printf("There is an error in this program\n");

	return 0;
}