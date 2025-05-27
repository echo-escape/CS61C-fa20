#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    if (head == NULL) {
        return 0; // An empty list cannot have a cycle
    }
    node *slow = head;
    node *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // Move slow pointer by 1 step
        fast = fast->next->next;   // Move fast pointer by 2 steps

        if (slow == fast) {         // If they meet, there is a cycle
            return 1; // Cycle detected
        }
    }
    return 0; // No cycle detected
}