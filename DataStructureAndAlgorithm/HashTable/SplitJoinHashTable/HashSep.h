#ifndef _HashSep_H

typedef int ElementType;

typedef unsigned int Index;

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);
void Error(char *S);
void FatalError(char *S);
int NextPrime(int num);
Index Hash(const int Key, int TableSize);
void PrintHashTable(HashTable H);

#endif