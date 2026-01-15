#define BILIST_NO_MAIN
#include "bilist.c"

static void BubbleSort(List* list) {
    if (list == NULL || list->head == NULL) {
        return;
    }

    int swapped;
    do {
        swapped = 0;
        Node* current = list->head;
        while (current != NULL && current->next != NULL) {
            if (current->data > current->next->data) {
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

int main() {
    List* list = Create();
    if (list == NULL) {
        return 1;
    }

    Display(list);

    Add(list, 7);
    Add(list, 3);
    Add(list, 9);
    Add(list, 1);
    Add(list, 5);
    Add(list, 2);

    BubbleSort(list);
    Display(list);

    free(list);
    return 0;
}
