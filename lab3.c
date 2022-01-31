/* table of encodings for given file */
#include <stdio.h>
#include <stdlib.h>

/* Linked List of Frequency and Character */
typedef struct Node
{
    int count;
    int character;
    int arr[50];
    struct Node* next;
    struct Node* left;
    struct Node* right;
}Node;

/* Function Prototypes */
int isLeaf(Node* root);
void printArray(int arr[], int top);
void printCodes(Node* root, int arr[], int top);
void fillArray(int arr[], FILE* file);
void printList(Node* head);
Node* newNode(int count, int character);
Node* sortedInsert(Node* head, int count, int character);
Node* treeInsert(Node* head, Node* newNode);
Node* merge(Node* first, Node* second);

int main (int argc, char* argv[])
{
    Node* head = NULL;
    FILE* fPointer = NULL; 
    int charArray[256] = {0};
    Node* first = NULL;
    Node* second = NULL;
    Node* addBack = NULL;
    int i = 0;
    int j = 0;
    int codes[50];
    
   
    if(argc > 1)
    {
        fPointer = fopen(argv[1], "r");
    }
    else
    {
        fPointer = stdin;
    }
        
    if(fPointer == NULL)
    {
        perror("No FILE\n");
        exit(EXIT_FAILURE);
    }

    fillArray(charArray, fPointer);
/*
    for(; i < 256; i++)
    {
        printf("Character:%d Count: %d\n", i, charArray[i]);
    }
*/
    for(; j < 256; j++)
    {
        if(charArray[j] != 0)
        {
            if(head == NULL)
            {
                head = newNode(charArray[j], j);
            }
            else
            {
                head = sortedInsert(head, charArray[j], j);
            }
        }
    }

    while(head != NULL && head->next != NULL)
    {
        first = head;
        second = head->next;
        head = head->next->next;
        addBack = merge(first, second);
        if(head == NULL)
        {
            head = addBack;
            break;
        }
        head = treeInsert(head, addBack);
    }

    printCodes(head, codes, 0);

    fclose(fPointer);

    return 0;
}

int isLeaf(Node* root)
{
    return !(root->left) && !(root->right);
}

void printArray(int arr[], int top)
{
    int i;
    i = 0;
    for( ; i < top; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void printCodes(Node* root, int arr[], int top)
{
    if(root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if(root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if(isLeaf(root))
    {
       printf("0x%02x: ", root->character);
        printArray(arr, top);
    }
}


void fillArray(int arr[], FILE* file)
{
    int c = 0;

    while((c = getc(file)) != EOF)
    {
        arr[c]++;
    }
}

/* void print Linked List */
void printList(Node* head)
{
    Node* start = head;
    while(start != NULL)
    {
        printf("Character: %d and Count: %d\n", start->character, start->count);
        start = start->next;
    }
}

/* create a new Node */
Node* newNode(int count, int character)
{
    Node* newNode = (Node*)malloc(sizeof(newNode));
    newNode->count = count;
    newNode->character = character;
    newNode->next = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* treeInsert(Node* head, Node* newNode)
{
    Node* current = NULL;
    
    current = head;
    
    if(head == NULL || newNode->count < head->count)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        current = head;
        while(current->next != NULL && current->next->count < newNode->count)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return head;
}

Node* sortedInsert(Node* head, int count, int character)
{
    Node* current = NULL;
    Node* newP = NULL;

    current = head;
    
    newP = newNode(count, character);
     
    if(head == NULL || count < head->count)
    {
        newP->next = head;
        head = newP;
    }
    else
    {
        current = head;
        while(current->next != NULL && current->next->count <= count)
        {
            current = current->next;
        }
        newP->next = current->next;
        current->next = newP;
    }
    return head;
}
       

Node* merge(Node* first, Node* second)
{
    Node* newP = NULL;

    if(first == NULL || second == NULL) return NULL;
    first->next = NULL;
    second->next = NULL;
    newP = (Node*)malloc(sizeof(Node));
    newP->left = first;
    newP->right = second;
    newP->count = first->count + second->count;
    return newP;
}
    
