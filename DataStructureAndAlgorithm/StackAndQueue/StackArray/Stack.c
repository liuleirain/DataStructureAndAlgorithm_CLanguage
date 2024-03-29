#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S)
{
    return S->TopOfStack == S->Capacity;
}

Stack CreateStack(int MaxElements)
{
    Stack S;

    if (MaxElements < MinStackSize)
        Error("Stack size is too small");

    S = malloc(sizeof(struct StackRecord));
    if (S == NULL)
        FatalError("Out of space!!!");
    S->Array = malloc(sizeof(ElementType) * MaxElements);
    if (S->Array == NULL)
        FatalError("Out of space!!!");
    S->Capacity = MaxElements;
    MakeEmpty(S);
    return S;
}

void DisposeStack(Stack S)
{
    if (S != NULL)
    {
        free(S->Array);
        free(S);
    }
}

void MakeEmpty(Stack S)
{
    S->TopOfStack = EmptyTOS;
}

void Push(ElementType X, Stack S)
{
    if (IsFull(S))
        Error("Full stack");
    else
        S->Array[++S->TopOfStack] = X;
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack];
    Error("Empty stack");
    return 0;
}

void Pop(Stack S)
{
    if (!IsEmpty(S))
        S->TopOfStack--;
    else
        Error("Empty stack");
}

ElementType TopAndPop(Stack S)
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack--];
    Error("Empty stack");
    return 0;
}

void FatalError(char *S)
{
    fprintf(stderr, "%s\n", S);
    exit(EXIT_FAILURE);
}

void Error(char *S)
{
    fputs(S, stderr);
}

void PrintStack(Stack S)
{
    int i = S->TopOfStack;
    for (; i > EmptyTOS; i--)
    {
        printf("%d ", S->Array[i]);
    }
    putchar('\n');
}