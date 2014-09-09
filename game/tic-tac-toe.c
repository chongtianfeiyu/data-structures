


#include <stdio.h>
#include <stdlib.h>

#define Draw (0)
#define CompWin (1)
#define CompLoss (-1)
#define Comp 1
#define Human 2

typedef int* BoardType;

void FindHumanMove(BoardType Board, int *BestMove, int *Value);
int time = 0;

BoardType InitalizeBoard()
{
    BoardType B;
    B = (BoardType)malloc(sizeof(int) * 15);
    if (B == 0x0)
        exit(1);
    memset(B, 0, sizeof(int) * 10);
    return B;
}

void Place(BoardType B, int i, int type)
{
    B[i - 1] = type;
}

void Unplace(BoardType B, int i)
{
    B[i - 1] = 0;
}

int IsEmpty(BoardType B, int i)
{
    return B[i - 1] == 0 ? 1 : 0;
}

int WinOrNot(BoardType B, int type)
{
    if (B[1] == type)
    {
        if (B[1] == B[2] && B[1] == B[3])
            return 1;
        else if (B[1] == B[4] && B[1] == B[7])
            return 1;
        else if (B[1] == B[5] && B[1] == B[9])
            return 1;
    }
    else if (B[5] == type)
    {
        if (B[5] == B[2] && B[5] == B[8])
            return 1;
        else if (B[5] == B[4] && B[5] == B[6])
            return 1;
    }
    else if (B[9] == type)
    {
        if (B[9] == B[6] && B[9] == B[3])
            return 1;
        else if (B[9] == B[8] && B[9] == B[7])
            return 1;
    }
    return 0;
}

int ImmediateCompWin(BoardType B, int *BestMove)
{
    Place(B, *BestMove, Comp);
    int win = WinOrNot(B, Comp);
    Unplace(B, *BestMove);
    return win;
}

int ImmediateHumanWin(BoardType B, int *BestMove)
{
    Place(B, *BestMove, Human);
    int win = WinOrNot(B, Human);
    Unplace(B, *BestMove);
    return win;
}

int FullBoard(BoardType B)
{
    int i;
    for (i = 0; i < 9; ++i)
        if (B[i] == 0)
            return 0;
    printf("%d\n", ++time);
    return 1;
}

void FindCompMove(BoardType Board, int *BestMove, int *Value)
{
     int Dc, i, Response;

     if (FullBoard(Board))
         *Value = Draw;
     else if (ImmediateCompWin(Board, BestMove))
         *Value = CompWin;
     else
     {
         *Value = CompLoss;
         for (i = 1; i <= 9; i++)
         {
             if (IsEmpty(Board, i))
             {
                 Place(Board, i, Comp);
                 FindHumanMove(Board, &Dc, &Response);
                 Unplace(Board, i);

                 if (Response > *Value)
                 {
                     *Value = Response;
                     *BestMove = i;
                 }
             }
         }
     }
}

void FindHumanMove(BoardType Board, int *BestMove, int *Value)
{
    int Dc, i, Response;
                                                      
    if (FullBoard(Board))
        *Value = Draw;
    else if (ImmediateHumanWin(Board, BestMove))
        *Value = CompLoss;
    else
    {
        *Value = CompWin;
        for (i = 1; i <= 9; i++)
        {
            if (IsEmpty(Board, i))
            {
                Place(Board, i, Human);
                FindCompMove(Board, &Dc, &Response);
                Unplace(Board, i);
                                                      
                if (Response < *Value)
                {
                    *Value = Response;
                    *BestMove = i;
                }
            }
        }
    }
}

void PrintBoard(BoardType Board)
{
    int i, j;
    for (i = 1; i <= 3; ++i)
    {
        for (j = 1; j <= 3; ++j)
        {
            if (Board[j - 1] == 1)
                printf("o ");
            else if (Board[j - 1] == 2)
                printf("x ");
            else
                printf("_ ");
        }
        printf("\n");
    }
}

void GameBegin(BoardType B)
{
    int BestMove, Value, HumanMove;
    //开局放在左上角
    BestMove = 1;
    Value = 0;
    while (1)
    {
        FindCompMove(B, &BestMove, &Value);
        B[BestMove - 1] = Comp;
        PrintBoard(B);
        while (scanf("%d", &HumanMove) != EOF)
        {
            if (!B[HumanMove - 1])
                break;
        }
        B[HumanMove - 1] = Human;
        PrintBoard(B);
    }
}

int main(int argc, const char* argv[])
{
    BoardType B;
    B = InitalizeBoard();
    GameBegin(B);
    return 0;
}
