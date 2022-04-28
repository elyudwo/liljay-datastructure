#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FALSE 0
#define TRUE 1

typedef struct IncidentEdge
{
    char aName;
    int weight;
    struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex
{
    char vName;
    int isVisit;
    IncidentEdge* iHead;
    struct Vertex* next;
}Vertex;

typedef struct
{
    Vertex* vHead;
}Graph;

void init(Graph* G)
{
    G->vHead = NULL;
}

void makeVertex(Graph* G, char vName)
{
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    v->vName = vName;
    v->isVisit = FALSE;
    v->iHead = NULL;
    v->next = NULL;

    Vertex* q = G->vHead;
    if (q == NULL)
        G->vHead = v;
    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = v;
    }
}

void makeIncidentEdge(Vertex* v, char aName, int w)
{
    IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
    p->aName = aName;
    p->weight = w;
    p->next = NULL;

    IncidentEdge* q = v->iHead;
    if (q == NULL)
        v->iHead = p;
    else
    {
        while (q->next != NULL)
            q = q->next; 
        q->next = p;
    }
}

Vertex* findVertex(Graph* G, char vName)
{
    Vertex* v = G->vHead;
    while (v->vName != vName)
        v = v->next;
    return v;
}

void insertEdge(Graph* G, char v1, char v2, int w)
{
    Vertex* v = findVertex(G, v1);
    makeIncidentEdge(v, v2, w);
}

void print(Graph* G)
{
    Vertex* p = G->vHead;
    IncidentEdge* q;
    for (; p != NULL; p = p->next)
    {
        printf("(%c) : ", p->vName);
        for (q = p->iHead; q != NULL; q = q->next)
            printf("(%c, %d) ", q->aName, q->weight);
        printf("\n");
    }
    printf("\n");
}

void dfs(Graph* G, char vName)
{
    Vertex* v = findVertex(G, vName);
    IncidentEdge* p;

    if (v->isVisit == FALSE)
    {
        v->isVisit = TRUE;
        printf("(%c) ", v->vName);
    }

    for (p = v->iHead; p != NULL; p = p->next)
    {
        v = findVertex(G, p->aName);
        if (v->isVisit == FALSE)
            dfs(G, v->vName);
    }

}

void bfs(Graph* G, char vName)
{
    Vertex* v = findVertex(G, vName);
    IncidentEdge* p;
    Vertex* q;

    if (v->isVisit == FALSE)
    {
        v->isVisit = TRUE;
        printf("(%c) ", v->vName);
    }

    while (v != NULL)
    {
        for (p = v->iHead; p != NULL; p = p->next)
        {
            q = findVertex(G, p->aName);
            if (q->isVisit == FALSE)
            {
                q->isVisit = TRUE;
                printf("(%c) ", q->vName);
            }
        }
        v = v->next;
    }

}

int main()
{
    Graph G;
    init(&G);

    makeVertex(&G, 'a');   makeVertex(&G, 'b');   makeVertex(&G, 'c');
    makeVertex(&G, 'd');   makeVertex(&G, 'e');

    insertEdge(&G, 'a', 'b', 1);   insertEdge(&G, 'a', 'c', 2);
    insertEdge(&G, 'a', 'e', 3);   insertEdge(&G, 'b', 'c', 1);
    insertEdge(&G, 'c', 'd', 1);   
    insertEdge(&G, 'c', 'e', 3);
    insertEdge(&G, 'd', 'e', 1);

    print(&G);
    //dfs(&G, 'a');   printf("\n");
    bfs(&G, 'a');

    return 0;
}
