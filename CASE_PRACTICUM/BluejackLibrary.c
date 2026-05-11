//ABOUT HASHING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define TABLE_SIZE 1007
#define MAX_TITLE 51
#define MAX_AUTHOR 26
#define MAX_ISBN 13
#define MAX_ID 50

//structure for hash (book) entry
typedef struct HashEntry{
    //the key (pointed to book ID) is what you'll search by
    char* key;

    //book data
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char isbn[MAX_ISBN];
    int pgNum;

    //hash entry mechanics
    struct HashEntry* next; //for chaining
} HashEntry;

//initialize hash table (all data to 0)
HashEntry* hashTable[TABLE_SIZE] = {0};

//initialize hash entry
HashEntry* createHashEntry(const char* id, const char* title, const char* author, const char* isbn, int pages){
    HashEntry* newEntry = (HashEntry*)malloc(sizeof(HashEntry));
    if (!newEntry) return NULL;

    //key (book id) as seperate allocated string
    newEntry->key = (char*)malloc(strlen(id) + 1);
    strcpy(newEntry->key, id);

    //rest of book data here
    strcpy(newEntry->title, title);
    strcpy(newEntry->author, author);
    strcpy(newEntry->isbn, isbn);
    newEntry->pgNum = pages;

    newEntry->next = NULL;
    return newEntry;
}

//hash function (simple sum of ASCII values mod table size)
int hashFunction(const char* key){
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++){
        sum += (int)key[i];
    }
    return sum % TABLE_SIZE;
}

//validate functions for utility purpose

//validate title (unique, between 5 and 50 characters)
bool isValidTitle(const char* title){
    int len = strlen(title);
    if (len < 5 || len > 50){
        return false;
    }

    //loop through the hash table to detect if title is unique
    for (int i = 0; i < TABLE_SIZE; i++){
        for (HashEntry* curr = hashTable[i]; curr != NULL; curr = curr->next){
            if (strcmp(curr->title, title)){    //compare titles
                printf("The book already exists !\n");
                return false;   //found duplicate title
            }
        }
    }
    return true;
}

/*OPTIONAL:
bool isTitleUnique(const char* title){
    //loop through entire hash table
    for (int i = 0; i < TABLE_SIZE; i++){
        HashEntry* curr = hashTable[i];
        while (curr != NULL){
            //compare titles
            if (strcmp(curr->bookTitle, title) == 0){
                return false;  //found duplicate
            }
                current = current->next;
            }
        }
    return true;  //title is unique
}*/

//validate author (start with "Mr." or "Mrs.", between 3 and 25 characters)
bool isValidAuthor(const char* author){
    int len = strlen(author);
    if (len < 3 || len > 25){
        return false;
    }

    if (strncmp(author, "Mr.", 3) == 0){
        if (len == 3){
            return false;
        }
        return true;
    } else if (strncmp(author, "Mrs.", 4) == 0){
        if (len == 4){
            return false;
        }
        return true;
    } else{
        return false;
    }
    return true;
}

//validate isbn (numeric, between 10 and 13 digits)
bool isValidIsbn(const char* isbn){
    int len = strlen(isbn);
    if (len < 10 || len > 13){
        return false;
    }

    for (int i = 0; i < len; i++){
        if (!isdigit(isbn[i])){
            return false;
        }
    }
    return true;
}

//validate page numbers (at least 16 pages)
bool isValidPageNum(int pageNum){
    if (pageNum < 16){
        return false;
    }
    return true;
}

//input functions

void getBookTitle(char* title){
    do{
        printf("Input book title[5-50]: ");
        if (fgets(title, MAX_TITLE, stdin) == 0) continue;
        title[strcspn(title, "\n")] = '\0';
    } while (!isValidTitle(title));
}

void getBookAuthor(char* author){
    do{
        printf("Input author name[5-50][numeric]: ");
        if (fgets(author, MAX_AUTHOR, stdin) == 0) continue;
        author[strcspn(author, "\n")] = '\0';
    } while (!isValidAuthor(author));
}

void getBookISBN(char* isbn){
    do{
        printf("Input ISBN[10-13][numeric]: ");
        if (fgets(isbn, MAX_ISBN, stdin) == 0) continue;
        isbn[strcspn(isbn, "\n")] = '\0';
    } while (!isValidIsbn(isbn));
}

void getBookPageNum(int* pages){
    char input[20];
    do{
        printf("Input page number[>= 16]: ");
        if (fgets(input, 20, stdin) == 0) continue;
        input[strcspn(input, "\n")] = '\0';
        *pages = atoi(input);
    } while (!isValidPageNum(*pages));
}

//book ID generation (FORMAT: BXXXXX-ISBN-AT) 
//X = last inserted book ID increased by 1, A = first character of book author in uppercase, T = first character of book title in uppercase

//get next book number for book id generation
int getNextBookNumber(){
    int maxNum = 0;

    for (int i = 0; i < TABLE_SIZE; i++){
        HashEntry* curr = hashTable[i];
        while (curr != NULL){
            //extract number from BXXXXX format
            int num;
            if (sscanf(curr->key, "B%05d", &num) == 1){
                if (num > maxNum){
                    maxNum = num;
                }
            }
            curr = curr->next;
        }
    }
    return maxNum + 1;
}

void generateBookID(char* id, const char* title, int nextNum, const char* isbn, const char* author){
    //find first character after prefix
    int authorIndex = 0;

    if (strncmp(author, "Mr.", 3) == 0) authorIndex = 3;
    else if (strncmp(author, "Mrs.", 4) == 0) authorIndex = 4;
    while (author[authorIndex] == ' ') continue;
    /* equivalent to this but made better:
    if (strncmp(author, "Mr.", 3) == 0 || strncmp(author, "Mrs.", 4) == 0){
        authorIndex = (author[1] == 'r' && author[2] == '.') ? 3 : 4;
    }*/

    //convert author and title to uppercase
    char firstAuthor = toupper(author[authorIndex]); //if (firstAuthor >= 'a' && firstAuthor <= 'z') firstAuthor -= 32;
    char firstTitle = toupper(title[0]); //if (firstTitle >= 'a' && firstTitle <= 'z') firstTitle -= 32;
    sprintf(id, "B%05d-%s-%c%c", nextNum, isbn, firstAuthor, firstTitle);
}

//hash table operations

//display all books
void viewAllBooks(){
    int bookCount = 0;

    //check if any book exists
    for (int i = 0; i < TABLE_SIZE; i++){
        if (hashTable[i] != NULL){
            bookCount++;
            break;
        }
    }

    if (bookCount == 0){
        printf("There is no book(s)\n");
        printf("Press Enter to continue ...\n"); getchar();
    }

    //print header
    printf("---------------------|--------------------------------|----------------------|-----------------|----------\n");
    printf("\n%-20s | %-30s | %-20s | %-15s | %s\n", "Book ID", "Title", "Author", "ISBN", "Pages");

    //print all books
    bookCount = 0;
    for (int i = 0; i < TABLE_SIZE; i++){
        HashEntry* curr = hashTable[i];
        while (curr != NULL){ //or just curr
            printf("%-20s | %-30s | %-20s | %-15s | %d\n",curr->key, curr->title, curr->author, curr->isbn, curr->pgNum);
            bookCount++;
            curr = curr->next;
        }
    }
    printf("---------------------|--------------------------------|----------------------|-----------------|----------\n");
    printf("Press Enter to continue ...\n"); getchar();
}

//insert a book
bool insertBook(const char* title, const char* author, const char* isbn, int pageNum){
    //validate title first then the rest of the book data
    if (!isValidTitle(title)){
        return false;
    }
    if (!isValidAuthor(author)){
        return false;
    }
    if (!isValidIsbn(isbn)){
        return false;
    }
    if (!isValidPageNum(pageNum)){
        return false;
    }

    //generate book id
    int nextNum = getNextBookNumber();
    char bookID[MAX_ID];
    generateBookID(bookID, title, author, isbn, nextNum);

    //create new book entry
    HashEntry* newBook = createHashEntry(bookID, title, author, isbn, pageNum);

    //calculate hash index
    int index = hashFunction(bookID);

    //insert at beginning of chain
    newBook->next = hashTable[index];
    hashTable[index] = newBook;
}

//search a book
typedef struct SearchResult{
    HashEntry* book; //found book
    HashEntry* prev; //previous book in chain
    int index; //index of the book in the hash table
} SearchResult;

SearchResult searchPrevBook(const char* bookID){
    SearchResult result = {NULL, NULL, -1};

    int index = hashFunction(bookID);
    result.index = index;

    HashEntry* curr = hashTable[index];
    HashEntry* prev = NULL;

    while (curr != NULL){
        if (strcmp(curr->key, bookID) == 0){
            result.book = curr;
            result.prev = prev;
            return result;
        }
    }
    return result; //book will be NULL/not found
}

/* SIMPLEST WAY:
HashEntry* searchBook(const char* bookID){
    int index = hashFunction(bookID);

    HashEntry* curr = hashTable[index];
    while (curr != NULL){
        if (strcmp(curr->key, bookID) == 0){
            return curr; //found the book
        }
        curr = curr->next;
    }
    return NULL; //book not found
}*/

void displayBookDetails(HashEntry* book){
    if (!book) return;
    printf("Book ID: %s\n", book->key);
    printf("Book title: %s\n", book->title);
    printf("Book author: %s\n", book->author);
    printf("Book ISBN: %s\n", book->isbn);
    printf("Page Number: %d\n", book->pgNum);
}

//remove a book
bool removeBook(){
    char inputID[MAX_ID];
    char confirm;

    //get user input for a book to delete
    printf("Input book id to delete: ");
    if (!fgets(inputID, MAX_ID, stdin)) return false;
    inputID[strcspn(inputID, "\0")] = '\0';

    //search for the book (using enhanced search that returns prev)
    SearchResult result = searchPrevBook(inputID);

    //check if book exists
    if (result.book == NULL){
        printf("Book not found !\n");
        return false;
    }

    //display book details
    displayBookDetails(result.book);

    //ask for confirmation
    do{
        printf("\nAre you sure[y/n]? ");
        scanf("%c", confirm); getchar();
        confirm = tolower(confirm);

        if (confirm != 'y' && confirm != 'n'){
            printf("Enter 'y' or 'n' only\n");
        }
    } while (confirm != 'y' && confirm != 'n');

    //if user says no
    if (confirm == 'n'){
        return false;
    }

    //if user says yes
    if (result.prev == NULL){
        //book is at the head of the chain
        hashTable[result.index] = result.book->next;
    } else{
        //book is at the middle or the end
        result.prev->next = result.book->next;
    }

    //free memory
    free(result.book);
    printf("Deletion success !\n");
    return true;
}

/* SIMPLEST WAY:
bool removeBookS(){
    char inputID[MAX_ID];
    char confirm;

    //get user input for a book to delete
    printf("Input book id to delete: ");
    if (fgets(inputID, MAX_ID, stdin)) return false;
    inputID[strcspn(inputID, "\0")] = '\0';

    //find the book and its location
    int index = hashFunction(inputID);
    HashEntry* curr = hashTable[index];
    HashEntry* prev = NULL;

    //search for the book
    while (curr != NULL){
        if (strcmp(curr->key, inputID) == 0){
            break; //found
        }
        prev = curr;
        curr = curr->next;
    }

    //check if found
    if (curr == NULL){
        printf("Book not found !\n");
        return false;
    }

    //display book details
    displayBookDetails(curr);

    //ask for confirmation
    do{
        printf("Are you sure[y/n]? ");
        scanf("%c", &confirm); getchar();
        confirm = tolower(confirm);

        if (confirm != 'y' && confirm != 'n'){
            printf("Enter only 'y' or 'n'\n");
        }
    } while (confirm != 'y' && confirm != 'n');

    //if user says no
    if (confirm == 'n'){
        printf("Deletion cancelled\n");
        return false;
    }

    //perform deletion
    if (prev == NULL){
        //first node in the chain
        hashTable[index] = curr->next;
    } else{
        //not first node (probably at mid or end)
        prev->next = curr->next;
    }

    //free memory
    free(curr);
    printf("Deletion success !\n");
    return true;
}*/

//free hash/book entries
void freeEntry(HashEntry* entry){
    for (int i = 0; i < TABLE_SIZE; i++){
        HashEntry* curr = hashTable[i];
        while (curr != NULL){
            HashEntry* temp = curr;
            curr = curr->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

void menu(){
    int choice, pgNum;
    char title[MAX_TITLE], author[MAX_AUTHOR], isbn[MAX_ISBN], bookID[MAX_ID];
    do{
        printf("Bluejack Library\n");
        printf("==================\n");
        printf("1. View Book\n");
        printf("2. Insert Book\n");
        printf("3. Remove Book\n");
        printf("4. Exit\n");
        printf(">> "); scanf("%d", &choice);

        switch(choice){
            case 1: //view book
                viewAllBooks();
                break;
            case 2: //insert book
                getBookTitle(title);
                getBookAuthor(author);
                getBookISBN(isbn);
                getBookPageNum(pgNum);
                printf("Insert success !\n");
                break;
            case 3: //remove book
                removeBook();
                break;
            case 4: //exit
                break;
            default:
                printf("Invalid input\n");
                break;
        }
    } while (choice != 4);
}

int main(){
    menu();
    return 0;
}