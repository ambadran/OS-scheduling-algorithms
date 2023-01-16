#include "scheduling_algorithms.h"

// creates a new singly linked list
// Function to Create A New Node
Node* newNode(Process* d, int p)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
 
    return temp;
}
 
// Return the value at head
Process* peek(Node** head)
{
    return (*head)->data;
}
 
// Removes the element with the
// highest priority from the list
void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
 
// Function to push according to priority
void push(Node** head, Process* d, int p, int mode)
{
    Node* start = (*head);
 
    // Create new Node
    Node* temp = newNode(d, p);
 
    if (mode == MINIMUM_VALUE_FIRST) {

      if ((*head)->priority > p) {
   
          // Insert New Node before head
          temp->next = *head;
          (*head) = temp;
      }
      else {
   
          // Traverse the list and find a
          // position to insert new node
          while (start->next != NULL && start->next->priority < p) {
              start = start->next;
          }
   
          // Either at the ends of the list
          // or at required position
          temp->next = start->next;
          start->next = temp;
      }

    } else if (mode == MAXIMUM_VALUE_FIRST) {

      if ((*head)->priority <= p) {
   
          // Insert New Node before head
          temp->next = *head;
          (*head) = temp;
      }
      else {
   
          // Traverse the list and find a
          // position to insert new node
          while (start->next != NULL && start->next->priority >= p) {
              start = start->next;
          }
   
          // Either at the ends of the list
          // or at required position
          temp->next = start->next;
          start->next = temp;
      }
    }
}
 
// Function to check is list is empty
int isEmpty(Node** head)
{
    return (*head) == NULL;
}

bool priority_queue_contains(Node** head, Process process) {

  Node* start = *head;
  bool in_there = false;

  while( start->next !=NULL ) {

    if( (*start->data).id == process.id ) {
      in_there = true;
      break;
    }
    start = start->next;

  }

  if( (*start->data).id == process.id ) {
    in_there = true;
  }

  return in_there;

}


void print_priority_queue(Node** head) {

  Node* start = *head;

  while( start->next !=NULL ) {

    print_process(*start->data);
    start = start->next;

  }
  print_process(*start->data);

}

