#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BinHeap.h"

#define MinPQSize (5)
#define MinData (0)

struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Elements;
};

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue H;

    if (MaxElements < MinPQSize)
        Error("Priority queue size is too small");

    H = malloc(sizeof(struct HeapStruct));
    if (H == NULL)
        FatalError("Out of space!!!");

    H->Elements = malloc(sizeof(ElementType) * (MaxElements + 1));
    if (H->Elements == NULL)
        FatalError("Out of space!!!");

    H->Capacity = MaxElements;
    MakeEmpty(H);
    return H;
}

void Destroy(PriorityQueue H)
{
    free(H->Elements);
    free(H);
}

void MakeEmpty(PriorityQueue H)
{
    H->Size = 0;
    H->Elements[0] = MinData;
}

void Insert(ElementType X, PriorityQueue H)
{
    int i;

    if (IsFull(H))
    {
        Error("Priority queue is full");
        return;
    }
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H)
{
    int i, Child;
    ElementType MinElement, LastElement;

    if (IsEmpty(H))
    {
        Error("Priority queue is empty");
        return H->Elements[0];
    }
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    for (i = 1; i * 2 <= H->Size; i = Child)
    {
        Child = i * 2;
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            Child++;

        if (LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

ElementType FindMin(PriorityQueue H)
{
    if (IsEmpty(H))
        Error("Heap is empty!!!");
    else
        return H->Elements[1];
}

int IsEmpty(PriorityQueue H)
{
    return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
    return H->Size == H->Capacity;
}

void Error(char *S)
{
    fputs(S, stderr);
}

void FatalError(char *S)
{
    fprintf(stderr, "%s\n", S);
    exit(EXIT_FAILURE);
}

void PrintPriorityQueue(PriorityQueue H){
    int LineNumber = 0;
    int LineFeed = pow(2, LineNumber);
    
    for( int i = 1; i <= H->Size; i++){
        printf("%d ", H->Elements[i]);
        if( i == LineFeed){
            putchar('\n');
            LineNumber++;
            LineFeed += pow(2,LineNumber);
        }
    }
    putchar('\n');
}