#include <stdio.h>
// This code defines a function that mutates an array by applying a function to each element.
// The function to be applied is passed as a pointer, allowing for flexibility in the operation performed on each element.
int x10(int), x2(int);
void mutate_map(int[], int n, int (*)(int));
void print_array(int[], int n);

int main()
{
    int A[] = {1, 2, 3, 4, 5};
    int n = 5;
    
    // Apply x10 to each element of A
    mutate_map(A, n, &x10);
    print_array(A, n); // Output: 10 20 30 40 50
    
    // Apply x2 to each element of A
    mutate_map(A, n, &x2);
    print_array(A, n); // Output: 2 4 6 8 10
    
    return 0;
}


int x2(int n)
{
    return 2 * n;
}

int x10(int n)
{
    return 10 * n;
}

void mutate_map(int A[], int n, int (*fp)(int))
{
    for (int i = 0; i < n; i++)
        A[i] = (*fp)(A[i]);
}

void print_array(int A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}