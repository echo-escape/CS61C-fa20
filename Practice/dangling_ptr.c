#include <stdio.h>

int *ptr()
{
    static int y;
    y = 3;
    return &y;
}

int main(void)
{
    int *stackAddr, content;
    stackAddr = ptr();
    content = *stackAddr;
    printf("%d", content); /* 3 */
    content = *stackAddr;
    printf("%d", content); /*13451514 */
    return 0;
};