


#include <stdio.h>
#include <stdlib.h>

#define Draw (0)
#define CompWin (1)
#define CompLoss (-1)
#define Comp 1
#define Human 2

typedef int* BoardType;

void FindHumanMove(BoardType Board, int *BestMove, int *Value);

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
    int i = 1;
    if (B[1-i] == type)
    {
        if (B[1-i] == B[2-i] && B[1-i] == B[3-i])
            return 1;
        else if (B[1-i] == B[4-i] && B[1-i] == B[7-i])
            return 1;
        else if (B[1-i] == B[5-i] && B[1-i] == B[9-i])
            return 1;
    }
    else if (B[5-i] == type)
    {
        if (B[5-i] == B[2-i] && B[5-i] == B[8-i])
            return 1;
        else if (B[5-i] == B[4-i] && B[5-i] == B[6-i])
            return 1;
        else if (B[5-i] == B[3-i] && B[5-i] == B[7-i])
            return 1;
    }
    else if (B[9-i] == type)
    {
        if (B[9-i] == B[6-i] && B[9-i] == B[3-i])
            return 1;
        else if (B[9-i] == B[8-i] && B[9-i] == B[7-i])
            return 1;
    }
    return 0;
}

/*
   判断是否多行一步就能win。
   是，则BestMove记录位置并返回win。
*/
int ImmediateCompWin(BoardType B, int * const BestMove)
{
    int i = 1, flag;
    for ( ; i <= 9; ++i)
    {
        if (IsEmpty(B, i))
        {
            Place(B, i, Comp);
            flag = WinOrNot(B, Comp);
            Unplace(B, i);
            if (flag)
            {
                *BestMove = i;
                return flag;
            }
        }
    }
    return flag;
}

int ImmediateHumanWin(BoardType B, int * const BestMove)
{
    int i = 1, flag;
    for ( ; i <= 9; ++i)
    {
        if (IsEmpty(B, i))
        {
            Place(B, i, Human);
            flag = WinOrNot(B, Human);
            Unplace(B, i);
            if (flag)
            {
                *BestMove = i;
                return flag;
            }
        }
    }
    return flag;
}

int FullBoard(BoardType B)
{
    int i;
    for (i = 0; i < 9; ++i)
        if (B[i] == 0)
            return 0;
    return 1;
}

void FindCompMove(BoardType Board, int *BestMove, int *Value)
{
    int Dc, i, Response;
    Dc = Response = 0;

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
    Dc = Response = 0;
                                                      
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
    int i;
    for (i = 1; i <= 9; ++i)
    {
        if (Board[i - 1] == 1)
            printf("o ");
        else if (Board[i - 1] == 2)
            printf("x ");
        else
            printf("_ ");
        if (!(i % 3))
            printf("\n");
    }
}

void GameBegin(BoardType B)
{
    int BestMove, Value, HumanMove, first;
    printf("Who first? Computer:1 ; You:0\n");
    scanf("%d", &first);
    Value = 0;
    while (1)
    {
        if (Value == CompWin)
        {
            printf("Computer win!\n");
            break;
        }
        else if (Value == CompLoss)
        {
            printf("You win!\n");
            break;
        }
        else if (FullBoard(B))
        {
            printf("Draw.\n");
            break;
        }

        if (!first)
            goto here;
        FindCompMove(B, &BestMove, &Value);
        B[BestMove - 1] = Comp;
here:
        PrintBoard(B);
        first++;
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
