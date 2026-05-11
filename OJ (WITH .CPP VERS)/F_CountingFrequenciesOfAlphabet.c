#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 5

//struct for hash entry
typedef struct{
	char key;
	int value;
	int occupied;
} HashEntry;

//for the loops ig (I HAVE TO SUIT THE DEV C++ FORMAT)
int i, j;

//function to count frequency of letters in a string
void frequencyOfEach(const char* s){
	HashEntry table[TABLE_SIZE] = {0}; //initialize all to zero
	
	//process each character in the string
	for (i = 0; i < strlen(s); i++){
		char currChar = s[i];
		
		//calculate hash function with ASCII
		int idx = currChar % TABLE_SIZE;
		int startIdx = s[i];
		
		//linear probing to handle collision and find slot
		while (table[idx].occupied && table[idx].key != s[i]){
			idx = (idx + 1) % TABLE_SIZE; //try new slot
			if (idx == startIdx) break;	//full table (should not happen when max char is 5)
		}
		
		//if slot empty, insert new character
		if (!table[idx].occupied){
			table[idx].key = currChar;
			table[idx].occupied = 1;
			table[idx].value = 0;
		}
		
		//update freq
		table[idx].value++;
	}
	//print result, find and print the first occupied slot
	int first = 1; 
	for (j = 0; j < TABLE_SIZE; j++){
		if (table[j].occupied){
			if (first){
				printf("%c %d\n", table[j].key, table[j].value);
			} else{
				printf("%c %d\n", table[j].key, table[j].value);
			}
		}
	}
}

int main(){
	char s[1001];
	scanf("%[^\n]", s);
	frequencyOfEach(s);
	return 0;
}
