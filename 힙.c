#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

typedef int element;

typedef struct
{
	element heap[SIZE];
	int n;
}HeapType;

void init(HeapType* HT)
{
	HT->n = 0;
}

void upHeap(HeapType* HT)
{
	int i = HT->n;
	int k = HT->heap[i];

	while ((i != 1) && (k < HT->heap[i / 2]))
	{
		HT->heap[i] = HT->heap[i / 2];
		i /= 2;
	}
	HT->heap[i] = k;
}

void insertItem(HeapType* HT,element k)
{
	HT->n++;
	HT->heap[HT->n] = k;
	upHeap(HT);
}

void printHeap(HeapType* HT)
{
	for (int i = 1; i <= HT->n; i++)
	{
		printf("[%d] ", HT->heap[i]);
	}
	printf("\n");
}

int main()
{
	HeapType HT;
	init(&HT);

	srand(time(NULL));

	for (int i = 0; i < 7; i++)
	{
		int k = rand() % 100 + 1;
		insertItem(&HT, k);
		printf("[%d] ", k);
	}
	printf("\n");	getchar();
	printHeap(&HT);

}
