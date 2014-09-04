/*
 * Dijkstra最短路径算法
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NotAVertex (-1)

typedef int Vertex; 
typedef int ElementType;
typedef int DistType;

typedef struct ListNode
{
    Vertex V;
    ElementType Value;
    struct ListNode * Next;
}ListNode, *List;

typedef struct TableEntry
{
    //相邻的结点(Adjacency:n.邻接)
    List Header;
    //是否以被访问
    int Visited;
    //与起始点的距离
    DistType Dist;
    //当前结点的前结点
    Vertex Path;
}*Table;

typedef struct HashTbl
{
    int TableSize;
    List * HashList;
}*HashTable;

typedef struct Gph
{
    //顶点个数
    Vertex N;
    //邻接表
    List * Heads;
    //名字-编号映射
    //ListNode没有弄好，不能既有名字又有编号。再弄一个list感觉太累赘。
    //暂时编号作名字吧。
}*Graph;

Graph InitializeGraph()
{
    FILE *in;
    in = fopen("graph.in", "r");
    if (in == NULL)
    {
        printf("Open file error\n");
        exit(1);
    }
    
    int v, w, len;
    Graph G = (Graph)malloc(sizeof(struct Gph));
    fscanf(in, "%d", &G->N);
    G->Heads = (List *)malloc(sizeof(List) * (G->N + 1));
    for (v = 1; v <= G->N; ++v)
    {
        G->Heads[v] = (ListNode*)malloc(sizeof(ListNode));
        G->Heads[v]->V = v;
        G->Heads[v]->Value = 0;
        G->Heads[v]->Next = NULL;
    }
    while (fscanf(in, "%d %d %d", &v, &w, &len) != EOF)
    {
        ListNode * tmp = (ListNode *) malloc(sizeof(ListNode));
        tmp->V = w;
        tmp->Value = len;
        tmp->Next = G->Heads[v]->Next;
        G->Heads[v]->Next = tmp;
    }

    return G;
}

List CopyList(List L)
{
    List Result = NULL;
    List Tmp = NULL;
    Result = (List)malloc(sizeof(ListNode));
    Result->Next = NULL;
    while (L != NULL)
    {
        Tmp = (List) malloc(sizeof(ListNode));
        Tmp->V = L->V;
        Tmp->Value = L->Value;
        Tmp->Next = Result->Next;
        Result->Next = Tmp;
        L = L->Next;
    }
    return L;
}

void GraphToTable(Graph G, Table T)
{
    int i;
    List L = NULL;
    for (i = 1; i <= G->N; ++i)
    {
        L = G->Heads[i]->Next;
        T[i].Header = CopyList(L);
    }
}

Table InitTable(Vertex start, Graph G)
{
    int i;
    Table T = (Table)malloc(sizeof(struct TableEntry) * (G->N + 1));
    if (T == NULL)
    {
        printf("No size for Table.");
        exit(2);
    }
    GraphToTable(G, T);
    for (i = 1; i <= G->N; ++i)
    {
        T[i].Visited = 0;
        T[i].Dist = INT_MAX;
        T[i].Path = NotAVertex;
    }
    T[start].Dist = 0;
}

void PrintList(List L)
{
    //L的第一个是头指针
    L = L->Next;
    while (L != NULL)
    {
        printf("%d (%d); ", L->V, L->Value);
        L = L->Next;
    }
    printf("\n");
}

void PrintGraph(Graph G)
{
    printf("Has %d vertex.\n", G->N);
    int i;
    for (i = 1; i <= G->N; ++i)
    {
        printf("v%d to ", i);
        PrintList(G->Heads[i]);
    }
}

void PrintTable(Table T)
{
    int i;
    for (i = 1; i <= sizeof(T); ++i)
    {
        printf("%d : dist=%d, preVertex=%d\n", i, T[i].Dist, T[i].Path);
    }
}

//寻找没被访问过的顶点中值最小的
Vertex GetVertex(Table T)
{
    int i;
    int result = NotAVertex;
    int min = INT_MAX;
    for (i = 1; i <= sizeof(T); ++i)
    {
        if (!T[i].Visited && min > T[i].Dist)
        {
            min = T[i].Dist;
            result = i;
        }
    }
    return result;
}

void Dijkstra(Table T)
{
    Vertex v, w;

    while (1)
    {
        v = GetVertex(T);
        if (v == NotAVertex)
            break;
        T[v].Visited = 1;
        
        List L = T[v].Header != NULL ? T[v].Header->Next : NULL;
        while (L != NULL)
        {
            w = L->V;
            if (!T[w].Visited && T[v].Dist + L->Value < T[w].Dist)
            {
                T[w].Dist = T[v].Dist + L->Value;
                T[w].Path = v;
            }
            L = L->Next;
        }
    }
}

int main(int argc, const char* argv)
{
    int i;
    Graph G = InitializeGraph();
    Table T = InitTable(1, G);
    PrintGraph(G);
    Dijkstra(T);
    PrintTable(T);
    return 0;
}
