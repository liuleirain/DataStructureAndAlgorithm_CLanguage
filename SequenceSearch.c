#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int *data;
    int length;
    int num;
} List;

int *initList(int length)
{
    List *list = (List *)malloc(sizeof(List));
    list->length = length;
    list->data = (int *)malloc(sizeof(int) * length);
    list->num = 0;
    return list;
}

void printList(List* list){
    for(int i = 0 ; i < list->num; i++){
        printf("%d ", list->data[i]);
    }
    putchar('\n');
}

void listAdd(List *list, int data)
{
    list->data[list->num] = data;
    list->num = (list->num) + 1;
}

int search(List *list, int key)
{
    for (int i = 0; i < list->num; i++)
    {
        if (list->data[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    List* list = initList(5);
    listAdd(list, 1);
    listAdd(list, 2);
    listAdd(list, 3);
    listAdd(list, 4);
    listAdd(list, 5);
    printf("%d\n", search(list, 1));
    system("pause");
    return 0;
}