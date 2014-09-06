/*
   最小生成树算法。

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

//从graph.in中输入无向图的数据
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
        ListNode * tmp1 = (ListNode *) malloc(sizeof(ListNode));
        ListNode * tmp2 = (ListNode *) malloc(sizeof(ListNode));

        tmp1->V = w;
        tmp1->Value = len;
        tmp1->Next = G->Heads[v]->Next;
        G->Heads[v]->Next = tmp1;

        tmp2->V = v;
        tmp2->Value = len;
        tmp2->Next = G->Heads[w]->Next;
        G->Heads[w]->Next = tmp2;
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
    return Result;
}

void GraphToTable(Graph G, Table T)
{
    int i;
    List L = NULL;
    for (i = 1; i <= G->N; ++i)
    {
        L = G->Heads[i]->Next;
        //可能不需要用到CopyList。直接记录起始位置就好。
        //这样可能GraphToTable都不需要了。
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
    return T;
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
    //sizeof(T) 为顶点总个数+1, 其中+1是有Head指针, 不需要<=。
    for (i = 1; i < sizeof(T); ++i)
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

//同Dijkstra差不多。差别在于更新Dist的不同。
//Dijkstra： dw = min(dw, dv + c(v,w)) .  dw:点w到起点距离; dv+c(v,w):w经v到起点的距离 .  作用：w到起点的最短距离
//Prim: dw = min(dw, c(v,w)) . dw:到邻接点的距离;  c(v,w):w到v的距离 .  作用：得到与w邻接的点的最短距离
void Prim(Table T)
{
    int v, w;
    List trace;
    while (1)
    {
        v = GetVertex(T);
        if (v == NotAVertex)
            break;
        T[v].Visited = 1;

        List trace = T[v].Header != NULL ? T[v].Header->Next : NULL;
        while (trace != NULL)
        {
            w = trace->V;
            if (!T[w].Visited && trace->Value < T[w].Dist)
            {
                T[w].Dist = trace->Value;
                T[w].Path = v;
            }
            trace = trace->Next;
        }
    }
}

int main(int argc, const char* argv)
{
    int i;
    Graph G = InitializeGraph();
    PrintGraph(G);
    Table T = InitTable(1, G);
    Prim(T);
    PrintTable(T);
    return 0;
}
