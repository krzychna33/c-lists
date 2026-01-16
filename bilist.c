#include <stdio.h>
#include <stdlib.h>

/*
    Autor: Krzysztof Surazynski
*/

/*
 * BIDIRECTIONAL LIST VISUALIZATION:
 *
 *     NULL <- [Node1] <-> [Node2] <-> [Node3] -> NULL
 *              ^                        ^
 *             head                     tail
 */

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
    int size;
} List;

List* Create() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    
    return list;
}


void Add(List* list, int new_element) {
    if (list == NULL) {
        fprintf(stderr, "List is NULL\n");
        return;
    }
    
    // Create new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    newNode->data = new_element;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        // Add to the end
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    
    list->size++;
}

void Push(List *list, int new_element) {
    if (list == NULL) {
        fprintf(stderr, "List is NULL\n");
        return;
    }
    
    // Create new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    newNode->data = new_element;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        // Add to the front
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    
    list->size++;
}

Node* Get(List* list) {
    if (list == NULL) {
        fprintf(stderr, "List is NULL\n");
        return NULL;
    }
    
    return list->tail;
}

Node *GetAt(List *list, int position) {
    if (list == NULL) {
        fprintf(stderr, "List is NULL\n");
        return NULL;
    }
    
    int cursor_position = 0;
    Node *current = list->head;

    while (cursor_position < position) {
        current = current->next;
        cursor_position++;
    }

    return current;
}

Node* Pop(List* list) {
    if (list == NULL) {
        fprintf(stderr, "List is NULL\n");
        return NULL;
    }
    
    if (list->head == NULL) {
        return NULL; 
    }
    
    return list->head;
}

void AddAt(List* list, int new_element, int position) {
    if (list == NULL) {
        fprintf(stderr, "List is NULL\n");
        return;
    }
    
    if (position < 0 || position > list->size) {
        fprintf(stderr, "Invalid position");
        return;
    }
    
    // Create new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed");
        return;
    }
    newNode->data = new_element;

    int cursor_position = 0;

    Node *node_before_new_node = GetAt(list, position - 1);
    if (node_before_new_node == NULL) {
        fprintf(stderr, "Invalid position");
        free(newNode); 
        return;
    }

    newNode->next = node_before_new_node->next;
    newNode->prev = node_before_new_node;
    if (node_before_new_node->next != NULL) {
        node_before_new_node->next->prev = newNode;
    }
    node_before_new_node->next = newNode;
    
    if (newNode->next == NULL) {
        list->tail = newNode;
    }

    list->size++;
}

void RemoveAt(List* list, int position) {
    if (list == NULL) {
        fprintf(stderr, "List is NULL\n");
        return;
    }
    
    Node *node_to_remove = GetAt(list, position);
    if (node_to_remove == NULL) {
        fprintf(stderr, "Invalid position\n");
        return;
    }

    if (node_to_remove->prev != NULL) {
        node_to_remove->prev->next = node_to_remove->next;
    } else {
        list->head = node_to_remove->next;
    }

    if (node_to_remove->next != NULL) {
        node_to_remove->next->prev = node_to_remove->prev;
    } else {
        list->tail = node_to_remove->prev;
    }

    free(node_to_remove);
    list->size--;
}

void Destroy(List* list) {
    if (list == NULL) {
        return;
    }
    
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void Display(List* list) {
    if (list == NULL) {
        fprintf(stderr, "List is NULL\n");
        return;
    }
    
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

#ifndef BILIST_NO_MAIN
int main() {
    List* myList = Create();
    
    if (myList != NULL) {
        printf("Bidirectional list created successfully!\n");
        
        Add(myList, 10);
        Add(myList, 20);
        Add(myList, 30);
        Push(myList, 5);
        
        printf("Size: %d\n", myList->size);

        Node  *currentHead = myList->head;
        printf("Head data: %d\n", currentHead->data);
        

        Node *currentTail = Get(myList);
        
        printf("Tail data: %d\n", currentTail->data);

        AddAt(myList, 14, 2);

        Node *nodeAtPosition = GetAt(myList, 2);

        printf("Data at position 2: %d\n", nodeAtPosition->data);

        Node *popped = Pop(myList);
        printf("Popped data: %d\n", popped->data);

        RemoveAt(myList, 3);

        Display(myList);
        
        Destroy(myList);
    }
    
    return 0;
}
#endif
