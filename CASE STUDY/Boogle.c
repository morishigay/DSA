#define _POSIX_C_SOURCE 200809L //ts for strdup. strdup() is POSIX, not standard C. Must be declared before #include. If not, complier will assume it returns int and can cause crashes on 64-bit systems
//or you can use this --> #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_SIZE 27 //26 letters + 1 for space
#define MAX_DEFINITION 500

/*MUST HAVE FOLLOWING FEATURES:
1. Release a new slang word with its definition
2. Search a slang word
3. View all slang words with a certain prefix word
4. View all slang words
5. Exit program*/

//node structure for trie (prefix tree)
typedef struct TrieNode{
    int endOfWord; //1 if end of a slang word, 0 otherwise
    char* definition; //definition of the slang word
    struct TrieNode* children[ALPHABET_SIZE]; //array of pointers to child nodes
} TrieNode;

//function to create a new trie node
TrieNode* createTrieNode(){
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    newNode->endOfWord = 0; //initialize as not end of word
    newNode->definition = NULL; //initialize definition as empty (NULL)
    for (int i = 0; i < ALPHABET_SIZE; i++) newNode->children[i] = NULL; //initialize all children as NULL
    return newNode;
}

//utility function to map character to index (for insertion and searching)
int charToIndex(char c){
    if (c >= 'a' && c <= 'z') return c - 'a'; //if lowercase
    else if (c >= 'A' && c <= 'Z') return c - 'A'; //if uppercase
    else if (c == ' ') return 26; //if space
    return -1; //for invalid characters
}

//utility function to map index to character (for displaying)
char indexToChar(int idx){
    if (idx >= 0 && idx < 26) return 'a' + idx;  //lowercase
    if (idx == 26) return ' ';
    return '?'; // invalid
}

//function to get slang word from user
void getUserSlangWord(char** slangWord){
    int valid = 0;
    char buffer[MAX_DEFINITION];
    do{
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        //safe input with fgets instead of scanf
        if (fgets(buffer, sizeof(buffer), stdin) == NULL){
            printf("Error reading input.\n");
            continue;
        }

        //remove trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        //check if input was truncated (no newline found)
        size_t len = strcspn(buffer, "\n"); //find the position of newline or end of string
        int trunctated = (buffer[len] == '\0' && len == sizeof(buffer) - 1); //if we reached the end of buffer without finding a newline, it means input was trunctated
        buffer[len] = '\0'; //ensure null termination just in case
        if (trunctated){ //if input was trunctated, show error message and clear remaining input
            printf("Input too long. Please limit to %d characters.\n", MAX_DEFINITION - 1);
            //clear remaining input
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        //so thats why it was running to segmentation fault........ this damn code below me
        // if (strchr(buffer, '\n') == NULL && strlen(buffer) == sizeof(buffer) - 1){
        //     printf("Input too long. Please limit to %d characters.\n", MAX_DEFINITION - 1);
        //     //clear remaining input
        //     int c;
        //     while ((c = getchar()) != '\n' && c != EOF);
        //     continue;
        // }

        if (strlen(buffer) <= 1){
            printf("Slang word must be more than 1 characters.\n"); //added error message for length
        } else if (strchr(buffer, ' ') != NULL){
            printf("Slang word must not contain space.\n"); //added error message for space
        } else{
            //check if all letters
            int allLetters = 1;
            for (int i = 0; i < strlen(buffer); i++){
                if (!isalpha(buffer[i])){
                    allLetters = 0;
                    break;
                }
            }
            if (allLetters){
                if (*slangWord != NULL) free(*slangWord); //free old memory if it exists
                *slangWord = strdup(buffer);
                valid = 1; //valid input
            } else{
                printf("Slang word should only contain letters.\n");
            }
        }
    } while (!valid);
}

//function to get definition from user
void getUserDefinition(char** definition){
    int valid = 0;
    char buffer[MAX_DEFINITION];
    do{
        printf("Input a new slang word description [Must be more than 2 words]: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL){
            printf("Error reading input.\n");
            continue;
        }

        //remove trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        //check if input was truncated (no newline found)
        size_t len = strcspn(buffer, "\n"); //find the position of newline or end of string
        int trunctated = (buffer[len] == '\0' && len == sizeof(buffer) - 1); //if we reached the end of buffer without finding a newline, it means input was trunctated
        buffer[len] = '\0'; //ensure null termination just in case
        if (trunctated){ //if input was trunctated, show error message and clear remaining input
            printf("Input too long. Please limit to %d characters.\n", MAX_DEFINITION - 1);
            //clear remaining input
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        //count words in description (handle multiple spaces)
        int wordCount = 0; //flag for counting words
        char* temp = strdup(buffer);
        if (temp != NULL){
            char* token = strtok(temp, " ");
            while (token != NULL){
                wordCount++; //any non-NULL token is a valid word
                token = strtok(NULL, " ");
            }
            free(temp); //dont forget to free the temp buffer
        }

        //if the definition is less than 2 words, show an error message (ts my thing btw)
        if (wordCount <= 2){
            printf("Description must be more than 2 words.\n");
        } else{
            if (*definition != NULL) free(*definition);
            *definition = strdup(buffer);
            valid = 1; //valid input
        }
    } while (!valid);
}

//function to search a slang word
TrieNode* searchSlangWord(TrieNode* root, const char* slangWord){
    //if the trie is empty
    if (root == NULL) return NULL;

    TrieNode* curr = root;
    int len = strlen(slangWord);

    //traverse the trie according to the characters of the slang word
    for (int i = 0; i < len; i++){
        int index = charToIndex(slangWord[i]);
        if (index < 0 || index > 26) return NULL; //invalid character
        if (curr->children[index] == NULL) return NULL; //slang word not found
        curr = curr->children[index];
    }

    //check if it's end of a word
    if (curr != NULL && curr->endOfWord){
        return curr; //slang word found
    }
    return NULL; //slang word not found
}

//function to insert a slang word and its definition
TrieNode* insertSlangWord(TrieNode* root, const char* slangWord, const char* definition){
    //if trie is empty, create a new root node
    if (root == NULL) root = createTrieNode();

    TrieNode* curr = root;
    int len = strlen(slangWord);
    int isUpdate = 0;

    //traverse and insert the word
    for (int i = 0; i < len; i++){
        int index = charToIndex(slangWord[i]);
        char ch = slangWord[i];

        if (index == -1) continue; //invalid character, skip
        if (curr->children[index] == NULL){
            curr->children[index] = createTrieNode(); //create new node if not exists
        }
        curr = curr->children[index];
    }

    //after traversal, check if word already exists
    isUpdate = (curr->endOfWord == 1);

    //mark as end of word and store definition
    curr->endOfWord = 1;

    //free old definition if word already exists
    if (curr->definition != NULL){
        free(curr->definition);
    }

    //store new definition
    if (curr->definition) free(curr->definition);
    curr->definition = strdup(definition);

    /* ALTERNATIVE VERSION WITHOUT strdup()
     * curr->definition = (char*)malloc(strlen(definition) + 1);
     * strcpy(curr->definition, definition);*/

    //print appropriate message
    if (isUpdate){
        printf("Successfully updated slang word.\n");
    } else{
        printf("Successfully released slang word.\n");
    }
    return root;
}

//function to check if a prefix exists
bool isPrefix(TrieNode* root, const char* prefix){
    TrieNode* curr = root;
    int len = strlen(prefix);

    for (int i = 0; i < len; i++){
        int index = charToIndex(prefix[i]);
        if (index == -1) return false; //invalid character
        if (curr->children[index] == NULL) return false; //prefix not found
        curr = curr->children[index];
    }
    return true; //prefix found
}

//function to get prefix from user
void getUserPrefix(char* prefix, int maxLength){
    int valid = 0;
    do{
        printf("Input a prefix to be searched: ");
        scanf(" %[^\n]", prefix);  //note the space before % to skip whitespace

        //clear input buffer correctly
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        //check if input is empty
        if (strlen(prefix) == 0){
            printf("Prefix cannot be empty. Please try again.\n");
        } else{
            //if (*prefix != NULL) free(*prefix);
            //*prefix = strdup(prefix);
            valid = 1;
        }
    } while (!valid);
}

//utility function to get the node corresponding to the last character of the prefix
TrieNode* getPrefixNode(TrieNode* root, const char* prefix){
    TrieNode* curr = root;
    int len = strlen(prefix);

    //traverse the trie according to the character of the prefix
    for (int i = 0; i < len; i++){
        int index = charToIndex(prefix[i]);
        if (index == -1) return NULL;
        if (curr->children[index] == NULL) return NULL; //prefix not found
        curr = curr->children[index];
    }
    return curr; //return the node corresponding to the last character of the prefix
}

//utility function to collect all words from the given node
void collectWords(TrieNode* node, char* curr, int depth, char** result, int* count, int maxResults){
    if (node == NULL || *count >= maxResults) return;

    //if current node marks end of words, add to result
    if (node->endOfWord){
        curr[depth] = '\0';
        result[*count] = strdup(curr);
        /* ALTERNATIVE FOR STRDUP:
        result[*count] = malloc(strlen(curr) + 1);
        if (result[*count] != NULL){
            strcpy(result[*count], curr);
        } */
        (*count)++;
    }

    //traverse all children
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (node->children[i] != NULL){
            curr[depth] = indexToChar(i);
            collectWords(node->children[i], curr, depth + 1, result, count, maxResults);
        }
    }
}

//function to print and view all slang words with given prefix
TrieNode* printWordsWithPrefix(TrieNode* root, const char* prefix){
    TrieNode* prefixNode = getPrefixNode(root, prefix); //get the node at the end of the prefix
    if (prefixNode == NULL) return NULL; //prefix not found

    //array to store results
    char* result[5]; //store up to 5 words as required
    int count = 0;

    //prepare buffer for building words
    char* buffer = strdup(prefix); //start with the prefix

    /* ALTERNATIVE APPROACH WITH STRCPY():
    char buffer[100];
    strcpy(buffer, prefix);*/

    //collect words
    collectWords(prefixNode, buffer, strlen(prefix), result, &count, 5);

    //display results
    printf("Words start with \"%s\":\n", prefix);
    for (int i = 0; i < count; i++){
        printf("%d. %s\n", i + 1, result[i]);
        free(result[i]); //free each allocated string
    }
    return prefixNode;
}

//utility function to check if trie is empty
int isEmpty(TrieNode* root){
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (root->children[i] != NULL) return 0; //if any child is not NULL, return 0 (not empty)
    }
    return 1; //if all children are NULL, return 1 (empty)
}

//function to print all slang words (with preorder traversal)
void printAllSlangWords(TrieNode* root, char* buffer, int depth, int* count){
    //print the word at the beginning instead of the end
    if (root->endOfWord){
        buffer[depth] = '\0';
        printf("%d. %s\n", (*count)++, buffer);  //print with number
    }

    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (root->children[i] != NULL){
            //preorder returns immediately if its argument is NULL, so no need to check twice
            buffer[depth] = indexToChar(i); //convert index to char
            printAllSlangWords(root, buffer, depth + 1, count);
        }
    }
}

//wrapper function to display all slang words
void displayAllSlangWords(TrieNode* root){
    if (isEmpty(root)){
        printf("There is no slang word yet in the dictionary.\n");
        printf("Press enter to continue...\n"); getchar();
    }

    printf("List of all slang words in the dictionary:\n");
    char buffer[100];
    int count = 1; //start at 1
    printAllSlangWords(root, buffer, 0, &count);
}

//function to free the trie
void freeTrie(TrieNode* node){
    if (node == NULL) return;
    for (int i = 0; i < ALPHABET_SIZE; i++){
        freeTrie(node->children[i]); //for every child node that exists, free them
    }
    if (node->definition) free(node->definition); //if definition is not NULL/exists, free it
    free(node); //free the node itself
}

//function to show menu
void showMenu(){
    int choice;
    char* slangWord = NULL;
    char* definition = NULL;
    char prefix[100];
    TrieNode* root = createTrieNode();

    do{
        printf("Menu: \n");
        printf("1. Release a new slang word.\n");
        printf("2. Search a slang word.\n");
        printf("3. View all slang words with a certain prefix word.\n");
        printf("4. View all slang words.\n");
        printf("5. Exit.\n");
        scanf("%d", &choice); getchar();

        switch(choice){
            case 1: //release a new slang word
                getUserSlangWord(&slangWord);
                getUserDefinition(&definition);
                if (slangWord && definition){
                    root = insertSlangWord(root, slangWord, definition);
                }
                printf("Press enter to continue...\n"); getchar();
                break;
            case 2:{ //search a slang word
                getUserSlangWord(&slangWord);
                TrieNode* found = searchSlangWord(root, slangWord); //declaration variable inside switch needs a block
                if (!found){
                    printf("There is no \"%s\" in the dictionary.\n", slangWord);
                } else{
                    printf("Slang word: %s\n", slangWord);
                    printf("Definition: %s\n", found->definition ? found->definition : " ");
                }
                printf("Press enter to continue...\n"); getchar();
                break;
            }
            case 3: //view all slang words with a certain prefix
                getUserPrefix(prefix, 100);
                if (!isPrefix(root, prefix)){
                    printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
                } else{
                    printWordsWithPrefix(root, prefix);
                }
                printf("Press enter to continue...\n"); getchar();
                break;
            case 4: //view all slang words
                displayAllSlangWords(root);
                break;
            case 5: //exit program
                printf("Thank you... Have a nice day :)\n");
                break;
            default:
                break;
        }
    } while (choice != 5);
    if (slangWord) free(slangWord);
    if (definition) free(definition);
    freeTrie(root);
}

int main(){
    showMenu();
    return 0;
}
