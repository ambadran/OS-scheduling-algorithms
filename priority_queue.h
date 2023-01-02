
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
 
 
typedef struct node {
    // implementation of a singly linked list with a priority attribute to make a priority queue :)

    // the current node
    Process* data;
 
    // Lower values indicate higher priority
    int priority; // depends on wanted algorithm, could be arrival time, burst time, etc..
 
    // Pointer to the next node named next
    struct node* next;


} Node;
 
// creates a new singly linked list
// Function to Create A New Node
Node* newNode(Process* process, int priority);

// Return the value at head
Process* peek(Node** head);

// Removes the element with the
// highest priority from the list
void pop(Node** head);

// Function to push according to priority
void push(Node** head, Process* d, int p);

// Function to check is list is empty
int isEmpty(Node** head);


#endif
