#include <stdio.h>
#include <stdlib.h>

// Define a structure for linked list nodes
typedef struct node_t{
    int data;
    struct node_t *next;
}Node;

// print the linked list
void printList(Node *node) {
    while (node != NULL) {
        printf(" %d ->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// append a node to the linked list
void append(Node **head_ref, int new_data) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;
    Node *last = *head_ref;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while(last->next != NULL) {
        last = last->next;
    }
    
    last->next = new_node;
}

// Find the first node which data is equal to find_data
Node* find_node(Node *node, int find_data) {
    while (node != NULL) {
        if (node->data == find_data) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

// insert to reference node's next node
void insert(Node **ref_node, int new_data){
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = (*ref_node)->next;
    (*ref_node)->next = new_node;
}

int main(){
    Node* head = NULL;
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    Node *temp = find_node(head, 3);
    printf("%d %p\n", temp->data, temp->next);
    insert(&temp, 6);
    printList(head);
}