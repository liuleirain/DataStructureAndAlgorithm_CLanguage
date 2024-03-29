/*
 * Josephus问题是下面的游戏：N个人从1到N编号，围坐成一个圆圈。从1号开始传递一个热土豆。经过M次传递后拿着热土豆的人被清除离座，围坐的圆圈缩紧，由坐在被清除的人后面的人拿起热土豆继续进行游戏。最后剩下的人取胜。
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;

#define ElementType int

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node
{
    ElementType Element;
    struct Node *Next;
};

List MakeEmpty()
{
    List list = (List)malloc(sizeof(struct Node));
    if (list == NULL)
    {
        printf("out of space!\n");
        exit(-1);
    }
    list->Next = NULL;
    return list;
}

void TailInsert(ElementType Element, Position *pRear)
{
    Position TmpCell = (Position)malloc(sizeof(struct Node));
    if (TmpCell == NULL)
    {
        printf("out of space!\n");
        exit(-1);
    }
    TmpCell->Element = Element;
    TmpCell->Next = NULL;
    (*pRear)->Next = TmpCell;
    *pRear = TmpCell;
}

void DeleteElement(Position *pCurrent, Position rear)
{
    ElementType element = (*pCurrent)->Element;
    Position TmpCell = *pCurrent;
    *pCurrent = TmpCell->Next;
    rear->Next = *pCurrent;
    free(TmpCell);
    printf("%d ", element);
}

void Josephus(int M, int N, List head)
{
    Position pRear, current;
    pRear = head;
    for (int i = 1; i <= N; i++)
    {
        TailInsert(i, &pRear);
    }
    pRear->Next = head->Next;

    current = head->Next;
    while (current->Element != pRear->Element)
    {
        for (int i = 0; i < M; i++)
        {
            current = current->Next;
            pRear = pRear->Next;
        }
        DeleteElement(&current, pRear);
    }
}

int main()
{
    double duration;
    List head = MakeEmpty();
    start = clock();
    Josephus(11, 100000, head);
    putchar('\n');
    end = clock();
    duration = ((double)(end-start))/CLK_TCK;
    printf("tick = %f\n", (double)(end-start));
    printf("duration = %6.2e\n",duration);
    system("Pause");
    return 0;
}