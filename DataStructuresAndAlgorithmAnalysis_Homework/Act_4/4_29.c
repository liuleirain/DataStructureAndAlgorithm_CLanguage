#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LENGTH 10000
clock_t start, stop;

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef int ElementType;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
ElementType Retrieve(Position P);
void FatalError(char *S);
void PrintTree(SearchTree T);
void PrintElement(SearchTree T);
void PrintSequence(SearchTree T);
SearchTree MakeRandomTree1(int Lower, int Upper);
SearchTree MakeRandomTree(int N);
int RandInt(int Lower, int Upper);

struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

struct QueueRecord;
typedef struct QueueRecord *Queue;

int IsEmptyQueue(Queue Q);
int IsFullQueue(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmptyQueue(Queue Q);
void EnQueue(Position T, Queue Q);
Position FrontQueue(Queue Q);
void DeQueue(Queue Q);
Position FrontAndDeQueue(Queue Q);
static int SuccQueue(int Value, Queue Q);

struct QueueRecord
{
    int Capacity;
    int Size;
    int Front;
    int Rear;
    Position *Array;
};

int main()
{
    double duration;

    SearchTree tree = NULL;
    MakeEmpty(tree);
    start = clock();
    tree = MakeRandomTree(LENGTH);
    stop = clock();
    duration = (double)(stop - start) / CLK_TCK;
    printf("tick = %f\n", (double)(stop - start));
    printf("duration = %6.2e\n", duration);

    // PrintTree(tree);
    // putchar('\n');
    PrintSequence(tree);

    system("Pause");
    return 0;
}

SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, SearchTree T)
{
    if (T == NULL)
    {
        return NULL;
    }
    else if (X < T->Element)
    {
        T = Find(X, T->Left);
    }
    else if (X > T->Element)
    {
        T = Find(X, T->Right);
    }
    else
        return T;
}

Position FindMin(SearchTree T)
{
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

Position FindMax(SearchTree T)
{
    if (T == NULL)
        return NULL;
    while (T->Right)
        T = T->Right;
    return T;
}

SearchTree Insert(ElementType X, SearchTree T)
{
    if (T == NULL)
    {
        T = (SearchTree)malloc(sizeof(struct TreeNode));
        if (T == NULL)
            FatalError("Out of space!!");
        T->Element = X;
        T->Left = T->Right = NULL;
    }
    else if (X < T->Element)
    {
        T = Insert(X, T->Left);
    }
    else if (X > T->Element)
    {
        T = Insert(X, T->Right);
    }
    else
    {
        return T;
    }
}

SearchTree Delete(ElementType X, SearchTree T)
{
    Position TmpCell;
    if (T == NULL)
        return NULL;
    else if (X < T->Element)
        T->Left = Delete(X, T->Left);
    else if (X > T->Element)
        T->Right = Delete(X, T->Right);
    else if (T->Left && T->Right)
    {
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        free(TmpCell);
    }
    else
    {
        TmpCell = T;
        if (T->Left == NULL)
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(TmpCell);
    }
    return T;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}

void FatalError(char *S)
{
    fputs(S, stderr);
    exit(EXIT_FAILURE);
}

SearchTree MakeRandomTree1(int Lower, int Upper)
{
    SearchTree T;
    int RandomValue;

    T = NULL;
    if (Lower <= Upper)
    {
        T = malloc(sizeof(struct TreeNode));
        if (T != NULL)
        {
            T->Element = RandomValue = RandInt(Lower, Upper);
            T->Left = MakeRandomTree1(Lower, RandomValue - 1);
            T->Right = MakeRandomTree1(RandomValue + 1, Upper);
        }
        else
            FatalError("Out of space!!!");
    }
    return T;
}

SearchTree MakeRandomTree(int N)
{
    return MakeRandomTree1(1, N);
}

int RandInt(int Lower, int Upper)
{
    srand(time(NULL));
    return ((double)rand() / RAND_MAX) * (double)(Upper - Lower + 1) + Lower;
}

void PrintTree(SearchTree T)
{
    if (T != NULL)
    {
        PrintTree(T->Left);
        PrintElement(T);
        PrintTree(T->Right);
    }
}

void PrintElement(SearchTree T)
{
    printf("%d ", T->Element);
}

void PrintSequence(SearchTree T)
{
    Position TmpCell;
    Position Previous = NULL;
    int n = 1;
    Queue Q = CreateQueue(LENGTH);
    EnQueue(T, Q);
    while (!IsEmptyQueue(Q))
    {
        TmpCell = FrontAndDeQueue(Q);
        if (n == 1 ||  TmpCell->Element < Previous->Element)
        {
            printf("\n------------%d--------------\n", n);
            n++;
        }
        printf("%d ", Retrieve(TmpCell));
        if (TmpCell->Left != NULL)
            EnQueue(TmpCell->Left, Q);
        if (TmpCell->Right != NULL)
            EnQueue(TmpCell->Right, Q);
        Previous = TmpCell;
    }
    putchar('\n');
    DisposeQueue(Q);
}

int IsEmptyQueue(Queue Q)
{
    return Q->Size == 0;
}

int IsFullQueue(Queue Q)
{
    return Q->Capacity == Q->Size;
}

Queue CreateQueue(int MaxElements)
{
    Queue Q = (Queue)malloc(sizeof(struct QueueRecord));
    if (Q == NULL)
        FatalError("Out of space!!!");
    Q->Array = (Position *)malloc(sizeof(struct TreeNode) * MaxElements);
    if (Q->Array == NULL)
        FatalError("Out of space!!!");
    MakeEmptyQueue(Q);
    Q->Capacity = MaxElements;
    return Q;
}

void DisposeQueue(Queue Q)
{
    free(Q->Array);
    free(Q);
}

void MakeEmptyQueue(Queue Q)
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

void EnQueue(Position T, Queue Q)
{
    if (IsFullQueue(Q))
    {
        FatalError("Queue is full");
    }
    else
    {
        Q->Size++;
        Q->Rear = SuccQueue(Q->Rear, Q);
        Q->Array[Q->Rear] = T;
    }
}

Position FrontQueue(Queue Q)
{
    return Q->Array[Q->Front];
}

void DeQueue(Queue Q)
{
    if (IsEmptyQueue(Q))
        FatalError("Queue is empty!!!");
    else
    {
        Q->Size--;
        Q->Front = SuccQueue(Q->Front, Q);
    }
}

Position FrontAndDeQueue(Queue Q)
{
    Position TmpCell;
    TmpCell = FrontQueue(Q);
    DeQueue(Q);
    return TmpCell;
}

static int SuccQueue(int Value, Queue Q)
{
    if (++Value == Q->Capacity)
        Value == 0;
    return Value;
}
