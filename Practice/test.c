#include <stdio.h>

void IncrementPtr(int **ptr) {
    ptr = ptr + 1; // Increment the pointer itself, not the value it points to
}

void IncrementPtr2(int **ptr) {
    *ptr = *ptr + 1; // Increment the value pointed to by the pointer
}
int main() {
    int A[3] = {1, 2, 3};
    int *p = A; // Pointer to the first element of the array
    IncrementPtr(&p); // Pass the address of the pointer
    // Now p still points to the first element of A, not the second
    // After IncrementPtr, p still points to the first element of A
    printf("first attemp = %d\n", *p); // Output: 1
    // Increment the pointer to point to the second element
    IncrementPtr2(&p); // Pass the address of the pointer
    // Now p points to the second element of A
    printf("second attemp = %d\n", *p); // Output: 2
    // Increment the pointer to point to the third element
    return 0;
}