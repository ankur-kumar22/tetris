#include <stdio.h>
#define ROW 20
#define COL 10

struct Tetromino //shape
{
    int shape[4][4];
    int row;
    int col;
};
int board[ROW][COL] = {0};

void drawboard() //empty board
{
    for (int i = 0; i < ROW; i++)
    {
        printf("|");
        for (int j = 0; j < COL; j++)
        {
            if (board[i][j] == 1)
                printf("[]");
            else
                //printf("░░");
                printf("::");

        }
        printf("|\n");
    }
    printf("+");
    for (int j = 0; j < COL; j++)
        printf("__");
    printf("+\n");
}
void draw_tetromino(struct Tetromino t) //printing shape
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (t.shape[i][j] == 1)
            {
                board[i + t.row][j + t.col] =1;
            }
        }
    }
}



int main()
{
    struct Tetromino current = {
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        0, // row
        3  // col
    };

 draw_tetromino(current);
 drawboard();
    return 0;
}